// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <exception>

namespace aeon::imaging
{

/*!
 * An imaging exception is raised whenever there is an error.
 * There are no no different types of imaging exceptions,
 * as the failed operation can be determined from the context
 * of what was being called.
 */
class imaging_exception : public std::exception
{
};

} // namespace aeon::imaging
