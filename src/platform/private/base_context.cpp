// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include "base_context.h"

namespace aeon::platform
{

base_context::base_context() noexcept
    : input_listeners_{}
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

} // namespace aeon::platform
