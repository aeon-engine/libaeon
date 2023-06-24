// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

namespace aeon::streams
{

struct input_tag
{
};

struct input_seekable_tag
{
};

struct output_tag
{
};

struct output_seekable_tag
{
};

struct has_eof_tag
{
};

struct has_status_tag
{
};

struct has_size_tag
{
};

struct flushable_tag
{
};

} // namespace aeon::streams
