// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/platform/context.h>
#include <aeon/platform/input_events.h>
#include <aeon/common/listener_subject.h>

namespace aeon::platform
{

class base_context : public context
{
public:
    base_context() noexcept;
    ~base_context() override;

    base_context(const base_context &) noexcept = delete;
    auto operator=(const base_context &) noexcept -> base_context & = delete;

    base_context(base_context &&) noexcept = delete;
    auto operator=(base_context &&) noexcept -> base_context & = delete;

    void attach_input_listener(input_events &events) override;
    void detach_input_listener(input_events &events) override;
    void detach_all_input_listeners() override;
    [[nodiscard]] auto modifier_keys_state() const noexcept -> platform::modifier_keys_state override;

protected:
    [[nodiscard]] auto &input_listeners() noexcept
    {
        return input_listeners_;
    }

    [[nodiscard]] const auto &input_listeners() const noexcept
    {
        return input_listeners_;
    }

    internal::modifier_keys_state_data key_states_;

private:
    common::listener_subject<input_events> input_listeners_;
};

} // namespace aeon::platform
