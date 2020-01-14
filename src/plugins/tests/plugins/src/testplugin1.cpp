// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <itestplugin1.h>

class testplugin1 final : public itestplugin1
{
public:
    explicit testplugin1()
        : was_loaded_(false)
        , unload_callback_()
    {
    }

    testplugin1(testplugin1 &&) noexcept = delete;
    auto operator=(testplugin1 &&) noexcept -> testplugin1 & = delete;

    testplugin1(const testplugin1 &) = delete;
    auto operator=(const testplugin1 &) -> testplugin1 & = delete;

    ~testplugin1() final = default;

    [[nodiscard]] auto plugin_name() const noexcept -> const char * final
    {
        return "Test Plugin 1";
    }

    [[nodiscard]] auto plugin_version_string() const noexcept -> const char * final
    {
        return "1.3.3.7";
    }

    void plugin_on_load() final
    {
        was_loaded_ = true;
    }

    void plugin_on_unload() final
    {
        if (unload_callback_)
            unload_callback_();
    }

    [[nodiscard]] auto was_loaded() const noexcept -> bool final
    {
        return was_loaded_;
    }

    [[nodiscard]] auto test_func1() const noexcept -> int final
    {
        return 1337;
    }

    [[nodiscard]] auto test_func2(const int var) const noexcept -> int final
    {
        return var + 42;
    }

    void set_unload_callback(const std::function<void()> callback) final
    {
        unload_callback_ = callback;
    }

    [[nodiscard]] auto test_dll_heap() const -> std::unique_ptr<test_data> final
    {
        return std::make_unique<test_data>("Test", std::vector<int>{1, 3, 3, 7});
    }

private:
    bool was_loaded_;
    std::function<void()> unload_callback_;
};

aeon_register_plugin(testplugin1)
