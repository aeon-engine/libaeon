// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <stdexcept>

namespace aeon::unicode
{

class unicode_exception : public std::exception
{
};

class unicode_conversion_exception final : public unicode_exception
{
};

} // namespace aeon::unicode
