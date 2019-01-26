// Copyright (c) 2012-2019 Robin Degen

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
