// Copyright (c) 2012-2019 Robin Degen

#include <itestplugin1.h>

class testplugin1 : public itestplugin1
{
public:
    explicit testplugin1()
        : was_loaded_(false)
        , unload_callback_()
    {
    }

    virtual ~testplugin1() = default;

    auto plugin_name() const noexcept -> const char * override
    {
        return "Test Plugin 1";
    }

    auto plugin_version_string() const noexcept -> const char * override
    {
        return "1.3.3.7";
    }

    void plugin_on_load() override
    {
        was_loaded_ = true;
    }

    void plugin_on_unload() override
    {
        if (unload_callback_)
            unload_callback_();
    }

    auto was_loaded() const noexcept -> bool override
    {
        return was_loaded_;
    }

    auto test_func1() const noexcept -> int override
    {
        return 1337;
    }

    auto test_func2(const int var) const noexcept -> int override
    {
        return var + 42;
    }

    void set_unload_callback(const std::function<void()> callback) override
    {
        unload_callback_ = callback;
    }

    auto test_dll_heap() const -> std::unique_ptr<test_data> override
    {
        return std::make_unique<test_data>("Test", std::vector<int>{1, 3, 3, 7});
    }

private:
    bool was_loaded_;
    std::function<void()> unload_callback_;
};

aeon_register_plugin(testplugin1)
