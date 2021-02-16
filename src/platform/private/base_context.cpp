// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include "base_context.h"

namespace aeon::platform
{

base_context::base_context() noexcept
    : key_states_{}
    , input_listeners_{}
{
}

base_context::~base_context() = default;

void base_context::attach_input_listener(input_events &events)
{
    input_listeners_.attach(events);
}

void base_context::detach_input_listener(input_events &events)
{
    input_listeners_.detach(events);
}

void base_context::detach_all_input_listeners()
{
    input_listeners_.detach_all();
}

auto base_context::modifier_keys_state() const noexcept -> platform::modifier_keys_state
{
    return platform::modifier_keys_state{key_states_};
}

} // namespace aeon::platform
