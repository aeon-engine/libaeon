// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

// TODO

#include <aeon/common/platform.h>

#if (AEON_PLATFORM_OS_WINDOWS)
#define VK_USE_PLATFORM_WIN32_KHR
#elif (AEON_PLATFORM_OS_LINUX)
#define VK_USE_PLATFORM_XLIB_KHR
#endif

#include <aeon/vulkan/application_info.h>
#include <aeon/vulkan/instance.h>
#include <aeon/vulkan/debug.h>
#include <aeon/vulkan/physical_device.h>
#include <aeon/vulkan/surface.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/swap_chain.h>
#include <aeon/vulkan/buffer.h>
#include <aeon/vulkan/fence.h>
#include <aeon/vulkan/command_pool.h>
#include <aeon/vulkan/command_buffer.h>
#include <aeon/vulkan/queue.h>
#include <aeon/vulkan/checked_result.h>
#include <aeon/vulkan/shader_module.h>
#include <aeon/vulkan/image.h>
#include <aeon/vulkan/sampler.h>
#include <aeon/vulkan/render_pass.h>
#include <aeon/vulkan/framebuffer.h>
#include <aeon/vulkan/viewport.h>
#include <aeon/vulkan/semaphore.h>
#include <aeon/vulkan/render_pass_description.h>
#include <aeon/vulkan/descriptor_set_layout.h>
#include <aeon/vulkan/descriptor_set_layout_description.h>
#include <aeon/vulkan/pipeline_layout.h>
#include <aeon/vulkan/pipeline_layout_description.h>
#include <aeon/vulkan/graphics_pipeline_description.h>
#include <aeon/vulkan/descriptor_pool.h>
#include <aeon/vulkan/pipeline.h>
#include <aeon/vulkan/descriptor_buffer_info.h>
#include <aeon/vulkan/descriptor_image_info.h>
#include <aeon/vulkan/descriptor_set.h>
#include <aeon/vulkan/render_pass_begin_info.h>
#include <aeon/platform/context.h>
#include <aeon/platform/window.h>
#include <aeon/platform/window_create_info.h>
#include <aeon/imaging/file/png_file.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/math/mat4.h>
#include <iostream>
#include <stdexcept>

#include <vulkan/vulkan.h>

namespace aeon
{

static constexpr auto window_size = math::size2d{800, 600};
static constexpr auto window_title = u8"Aeon Vulkan - Triangle Example";
static constexpr auto enable_validation_layers = true;

[[nodiscard]] auto create_window(platform::context &context)
{
    platform::window_create_info info;
    info.title = window_title;
    info.size = window_size;
    info.resizable = true;
    return context.create_window(info);
}

struct vertex
{
    float position[3];
    float uv[2];
    float normal[3];
};

struct shader_uniform_buffers
{
    math::mat4 projectionMatrix;
    math::mat4 modelViewMatrix;
    math::mat4 viewMatrix;
    math::vector4<float> viewPos;
    float lodBias = 0.0f;
};

class vulkan_triangle_example
{
public:
    vulkan_triangle_example()
        : logfile_{"debug_log.txt", streams::file_mode::text, streams::file_flag::truncate}
        , platform_context_{platform::create_context()}
        , window_{create_window(*platform_context_)}
        , app_info_{window_title, common::version3<std::uint32_t>{1, 0}, u8"libaeon",
                    common::version3<std::uint32_t>{1, 0}}
    {
        std::vector<std::string> layers;

        if (enable_validation_layers)
            vulkan::debug::append_required_layers(layers);

        std::vector<std::string> extensions;
        extensions.emplace_back(VK_KHR_SURFACE_EXTENSION_NAME);

#if (AEON_PLATFORM_OS_WINDOWS)
        extensions.emplace_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif (AEON_PLATFORM_OS_LINUX)
        extensions.emplace_back(VK_KHR_XLIB_SURFACE_EXTENSION_NAME);
#endif

        if (enable_validation_layers)
            vulkan::debug::append_required_extensions(extensions);

        using namespace std::placeholders;
        instance_ = vulkan::instance{app_info_, layers, extensions};

        if (enable_validation_layers)
        {
            debug_ = std::make_unique<vulkan::debug>(
                instance_,
                [this](auto &&message_severity, auto &&message_type, auto &&callback_data) {
                    debug_callback(message_severity, message_type, callback_data);
                },
                vulkan::message_severity::important, vulkan::message_type::all);
        }

        surface_ = vulkan::surface{instance_, *window_};

        physical_device_ = vulkan::find_best_device_for_gfx(instance_, surface_);

        device_ = vulkan::device{physical_device_, surface_, layers, {VK_KHR_SWAPCHAIN_EXTENSION_NAME}, {}};

        VkSurfaceFormatKHR preferred_format{};
        preferred_format.format = VK_FORMAT_B8G8R8A8_UNORM; // VK_FORMAT_B8G8R8A8_SRGB;
        preferred_format.colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;

        const math::size2d<std::uint32_t> preferred_extend{window_size};

        swapchain_ = vulkan::swap_chain{device_, surface_, preferred_format, preferred_extend};

        // TODO: Create with create_transient flag?
        command_pool_ = vulkan::command_pool{device_, vulkan::command_pool_create_flag::reset_command_buffer};

        draw_command_buffers_ = command_pool_.create_command_buffers(swapchain_.image_count());

        prepare_synchronization_primitives();
        load_texture();
        create_depth_stencil();
        setup_render_pass();
        setup_frame_buffer();
        prepare_uniform_buffers();

        vert_shader_ = vulkan::shader_module{device_, "vert.spv"};
        frag_shader_ = vulkan::shader_module{device_, "frag.spv"};

        upload_buffers();

        setup_descriptor_set_layout();
        prepare_pipelines();
        setup_descriptor_pool();
        setup_descriptor_set();

        build_command_buffers();
    }

    ~vulkan_triangle_example() = default;

    void run()
    {
        main_loop();
    }

private:
    void debug_callback([[maybe_unused]] VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                        [[maybe_unused]] VkDebugUtilsMessageTypeFlagsEXT message_type,
                        const VkDebugUtilsMessengerCallbackDataEXT *callback_data)
    {
        streams::stream_writer writer{logfile_};

        switch (message_severity)
        {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                writer << "[VERBOSE]: ";
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                writer << "[INFO]:    ";
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                writer << "[WARNING]: ";
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                writer << "[ERROR]:   ";
                break;
        }

        writer << callback_data->pMessage << '\n';
        logfile_.flush();
    }

    void main_loop()
    {
        while (!window_->closed())
        {
            platform_context_->poll_events();

            const auto index = swapchain_.acquire_next_image(present_complete_semaphore_);

            draw_wait_fences_[index].wait();
            draw_wait_fences_[index].reset();

            device_.graphics_queue().submit(draw_command_buffers_[index], present_complete_semaphore_,
                                            vulkan::pipeline_stage_flag::color_attachment_output,
                                            render_complete_semaphore_, draw_wait_fences_[index]);

            swapchain_.queue_present(device_.graphics_queue(), render_complete_semaphore_);

            device_.wait_idle();
        }
    }

    void upload_buffers()
    {
        const std::vector<vertex> vertex_buffer = {{{1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
                                                   {{-1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
                                                   {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
                                                   {{1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}

        };
        const auto vertex_buffer_size = static_cast<std::uint32_t>(vertex_buffer.size()) * sizeof(vertex);

        const std::vector<std::uint32_t> index_buffer = {0, 1, 2, 2, 3, 0};
        const auto index_buffer_size = std::size(index_buffer) * sizeof(uint32_t);

        // Stage vertex buffer
        const auto staging_vertex_buffer =
            vulkan::buffer{device_, vertex_buffer_size, vulkan::buffer_usage_flag::transfer_src,
                           vulkan::memory_allocation_usage::cpu_only};
        vulkan::copy(staging_vertex_buffer, vertex_buffer);

        // Create real vertex buffer
        vertex_buffer_ =
            vulkan::buffer{device_, vertex_buffer_size,
                           vulkan::buffer_usage_flag::vertex_buffer | vulkan::buffer_usage_flag::transfer_dst,
                           vulkan::memory_allocation_usage::gpu_only};

        // Stage index buffer
        const auto staging_index_buffer =
            vulkan::buffer{device_, index_buffer_size, vulkan::buffer_usage_flag::transfer_src,
                           vulkan::memory_allocation_usage::cpu_only};
        vulkan::copy(staging_index_buffer, index_buffer);

        // Create real index buffer
        index_buffer_ =
            vulkan::buffer{device_, index_buffer_size,
                           vulkan::buffer_usage_flag::index_buffer | vulkan::buffer_usage_flag::transfer_dst,
                           vulkan::memory_allocation_usage::gpu_only};

        // Copy data from staging buffers to the real buffers
        const auto command_buffer = command_pool_.create_command_buffer(vulkan::command_buffer_auto_begin::enabled);

        command_buffer.copy_buffer(staging_vertex_buffer, 0, vertex_buffer_, 0, vertex_buffer_size);
        command_buffer.copy_buffer(staging_index_buffer, 0, index_buffer_, 0, index_buffer_size);

        command_buffer.end();
        command_buffer.flush(device_.transfer_queue());
    }

    void load_texture()
    {
        auto img = imaging::file::png::load("texture.png");

        const auto image_staging_buffer = vulkan::buffer{device_, img.size(), vulkan::buffer_usage_flag::transfer_src,
                                                         vulkan::memory_allocation_usage::cpu_only};
        vulkan::copy(image_staging_buffer, img);

        texture_image_ = vulkan::image{device_,
                                       vulkan::image_type::image_2d,
                                       math::size2d<std::uint32_t>{math::dimensions(img)},
                                       vulkan::format::r8g8b8a8_srgb,
                                       vulkan::image_usage_flag::sampled | vulkan::image_usage_flag::transfer_dst,
                                       vulkan::memory_allocation_usage::gpu_only};

        // Copy data from staging buffers to the real buffers
        const auto command_buffer = command_pool_.create_command_buffer(vulkan::command_buffer_auto_begin::enabled);
        command_buffer.copy_staging_buffer_to_image(image_staging_buffer, texture_image_,
                                                    math::size2d<std::uint32_t>{math::dimensions(img)});
        command_buffer.end();
        command_buffer.flush(device_.transfer_queue());

        VkImageSubresourceRange layout{};
        layout.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        layout.baseMipLevel = 0;
        layout.levelCount = 1;
        layout.baseArrayLayer = 0;
        layout.layerCount = 1;

        texture_image_view_ = vulkan::image_view{device_, texture_image_, vulkan::image_view_type::image_view_2d,
                                                 vulkan::format::r8g8b8a8_srgb, layout};

        texture_sampler_ = vulkan::sampler{device_};
    }

    void create_depth_stencil()
    {
        depth_stencil_format_ = vulkan::find_depth_stencil_format(physical_device_);
        depth_stencil_image_ = vulkan::image{device_,
                                             vulkan::image_type::image_2d,
                                             math::size2d<std::uint32_t>{window_size},
                                             depth_stencil_format_,
                                             vulkan::image_usage_flag::depth_stencil_attachment,
                                             vulkan::memory_allocation_usage::gpu_only};

        VkImageSubresourceRange subresource_range{};
        subresource_range.baseMipLevel = 0;
        subresource_range.levelCount = 1;
        subresource_range.baseArrayLayer = 0;
        subresource_range.layerCount = 1;
        subresource_range.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

        if (depth_stencil_format_ >= vulkan::format::d16_unorm_s8_uint)
            subresource_range.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;

        depth_stencil_image_view_ =
            vulkan::image_view{device_, depth_stencil_image_, vulkan::image_view_type::image_view_2d,
                               depth_stencil_format_, subresource_range};
    }

    void prepare_synchronization_primitives()
    {
        present_complete_semaphore_ = vulkan::semaphore{device_};
        render_complete_semaphore_ = vulkan::semaphore{device_};

        draw_wait_fences_.resize(swapchain_.image_count());
        for (auto &wait_fence : draw_wait_fences_)
            wait_fence = vulkan::fence{device_, vulkan::fence_create_state::signaled};
    }

    void setup_render_pass()
    {
        vulkan::render_pass_description description;
        description.add_attachment(swapchain_.format(), vulkan::image_layout::present_src_khr)
            .store_op(vulkan::attachment_store_op::store);

        description.add_attachment(depth_stencil_format_, vulkan::image_layout::depth_stencil_attachment_optimal);

        description.add_subpass()
            .add_color_attachment(0, vulkan::image_layout::color_attachment_optimal)
            .set_depth_stencil_attachment(1, vulkan::image_layout::depth_stencil_attachment_optimal);

        description.add_subpass_dependency()
            .source_subpass(vulkan::external_subpass)
            .source_stage_mask(vulkan::pipeline_stage_flag::color_attachment_output)
            .destination_stage_mask(vulkan::pipeline_stage_flag::color_attachment_output);

        description.add_subpass_dependency()
            .destination_subpass(vulkan::external_subpass)
            .source_stage_mask(vulkan::pipeline_stage_flag::color_attachment_output)
            .destination_stage_mask(vulkan::pipeline_stage_flag::bottom_of_pipe)
            .source_access_mask(vulkan::access_flag::color_attachment_write);

        render_pass_ = vulkan::render_pass{device_, description};
    }

    void prepare_uniform_buffers()
    {
        uniform_buffer_ =
            vulkan::buffer{device_, sizeof(shader_uniform_buffers), vulkan::buffer_usage_flag::uniform_buffer,
                           vulkan::memory_allocation_usage::cpu_to_gpu};

        update_uniform_buffers();
    }

    void update_uniform_buffers()
    {
        shader_uniform_buffers_.projectionMatrix =
            math::mat4::perspective_fov(math::unitf<math::degree>{60.0f}, window_size, 1.0f, 256.0f);
        shader_uniform_buffers_.modelViewMatrix = math::mat4::translate(0.0f, 0.0f, -2.5f);
        shader_uniform_buffers_.viewPos = math::vector4<float>{0.0f, 0.0f, 0.0f};

        vulkan::copy(uniform_buffer_, reinterpret_cast<const std::byte *>(&shader_uniform_buffers_),
                     sizeof(shader_uniform_buffers));
    }

    void setup_descriptor_set_layout()
    {
        vulkan::descriptor_set_layout_description set_layout_description;

        // Binding 0: Uniform buffer (Vertex shader)
        set_layout_description.add_binding(vulkan::descriptor_type::uniform_buffer, vulkan::shader_stage_flag::vertex,
                                           0);
        set_layout_description.add_binding(vulkan::descriptor_type::combined_image_sampler,
                                           vulkan::shader_stage_flag::fragment, 1);
        descriptor_set_layout_ = vulkan::descriptor_set_layout{device_, set_layout_description};

        vulkan::pipeline_layout_description pipeline_layout_description;
        pipeline_layout_description.add_set_layout(descriptor_set_layout_);

        pipeline_layout_ = vulkan::pipeline_layout{device_, pipeline_layout_description};
    }

    void prepare_pipelines()
    {
        vulkan::graphics_pipeline_description description{pipeline_layout_, render_pass_};

        description.rasterization_state()
            .cull_mode(vulkan::cull_mode::none)
            .front_face(vulkan::front_face::counter_clockwise);

        description.color_blend_state()
            .add_attachment()
            .color_write_mask(vulkan::color_component_flag::all)
            .enable_blend(false);

        description.dynamic_state()
            .add_dynamic_state(vulkan::dynamic_state::viewport)
            .add_dynamic_state(vulkan::dynamic_state::scissor);

        description.depth_stencil_state()
            .enable_depth_test()
            .enable_depth_write()
            .compare_op(vulkan::compare_op::less_of_equal)
            .enable_depth_bounds_test(false)
            .back(vulkan::stencil_op::keep, vulkan::stencil_op::keep, vulkan::stencil_op::keep,
                  vulkan::compare_op::always)
            .front(vulkan::stencil_op::keep, vulkan::stencil_op::keep, vulkan::stencil_op::keep,
                   vulkan::compare_op::always)
            .enable_stencil_test(false);

        description.vertex_input_state()
            .add_binding(0, sizeof(vertex))
            .add_attribute(0, 0, vulkan::format::r32g32b32_sfloat, offsetof(vertex, position))
            .add_attribute(1, 0, vulkan::format::r32g32_sfloat, offsetof(vertex, uv))
            .add_attribute(2, 0, vulkan::format::r32g32b32_sfloat, offsetof(vertex, normal));

        description.add_shader_stage(vulkan::shader_stage::vertex, vert_shader_);
        description.add_shader_stage(vulkan::shader_stage::fragment, frag_shader_);

        pipeline_ = vulkan::pipeline{device_, description};
    }

    void setup_frame_buffer()
    {
        framebuffers_ = vulkan::create_swap_chain_framebuffers(swapchain_, render_pass_, depth_stencil_image_view_);
    }

    void setup_descriptor_pool()
    {
        vulkan::descriptor_pool_description description;
        description.add_pool_size(vulkan::descriptor_type::uniform_buffer, 1);

        descriptor_pool_ = vulkan::descriptor_pool{device_, description};
    }

    void setup_descriptor_set()
    {
        descriptor_set_ = vulkan::descriptor_set(descriptor_pool_, descriptor_set_layout_);

        const auto buffer_info = vulkan::descriptor_buffer_info{uniform_buffer_, sizeof(shader_uniform_buffers)};
        descriptor_set_.update(buffer_info, vulkan::descriptor_type::uniform_buffer, 0);

        const auto image_info = vulkan::descriptor_image_info{texture_sampler_, texture_image_view_};
        descriptor_set_.update(image_info, 1);
    }

    void build_command_buffers()
    {
        std::cout << "buildCommandBuffers\n";

        vulkan::render_pass_begin_info render_pass_info{render_pass_, framebuffers_[0], vulkan::rectangle{window_size}};
        render_pass_info.add_clear_color(0.0f, 0.0f, 0.2f, 1.0f).add_clear_depth_stencil(1.0f, 0);

        for (auto i = 0u; i < draw_command_buffers_.size(); ++i)
        {
            render_pass_info.framebuffer(framebuffers_[i]);

            draw_command_buffers_[i].begin();

            draw_command_buffers_[i].begin_render_pass(render_pass_info);

            draw_command_buffers_[i].set_viewport(vulkan::viewport{window_size, 0.0f, 1.0f});
            draw_command_buffers_[i].set_scissor(window_size);

            draw_command_buffers_[i].bind_descriptor_set(vulkan::pipeline_bind_point::graphics, pipeline_layout_,
                                                         descriptor_set_);

            draw_command_buffers_[i].bind_graphics_pipeline(pipeline_);

            draw_command_buffers_[i].bind_vertex_buffer(vertex_buffer_);

            draw_command_buffers_[i].bind_index_buffer(index_buffer_);

            const auto index_count = 6; // TODO
            draw_command_buffers_[i].draw_indexed(index_count);

            draw_command_buffers_[i].end_render_pass();

            draw_command_buffers_[i].end();
        }
    }

    streams::file_sink_device logfile_;

    std::unique_ptr<platform::context> platform_context_;
    std::unique_ptr<platform::window> window_;

    vulkan::application_info app_info_;
    vulkan::instance instance_;
    std::unique_ptr<vulkan::debug> debug_;
    vulkan::surface surface_;
    vulkan::physical_device physical_device_;
    vulkan::device device_;
    vulkan::swap_chain swapchain_;

    std::vector<vulkan::framebuffer> framebuffers_;

    vulkan::command_pool command_pool_;
    std::vector<vulkan::command_buffer> draw_command_buffers_;
    std::vector<vulkan::fence> draw_wait_fences_;

    vulkan::image texture_image_;
    vulkan::image_view texture_image_view_;
    vulkan::sampler texture_sampler_;

    vulkan::format depth_stencil_format_;
    vulkan::image depth_stencil_image_;
    vulkan::image_view depth_stencil_image_view_;

    vulkan::semaphore present_complete_semaphore_;
    vulkan::semaphore render_complete_semaphore_;

    shader_uniform_buffers shader_uniform_buffers_;

    vulkan::render_pass render_pass_;
    vulkan::descriptor_set_layout descriptor_set_layout_;
    vulkan::descriptor_pool descriptor_pool_;

    vulkan::descriptor_set descriptor_set_;

    vulkan::pipeline_layout pipeline_layout_;
    vulkan::pipeline pipeline_;

    vulkan::buffer uniform_buffer_;

    vulkan::buffer vertex_buffer_;
    vulkan::buffer index_buffer_;

    vulkan::shader_module vert_shader_;
    vulkan::shader_module frag_shader_;
};

} // namespace aeon

int main()
{
    aeon::vulkan_triangle_example app;

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
