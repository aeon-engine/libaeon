/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

/******************************************************************************/
/* Standard headers                                                           */
/******************************************************************************/
#include <string>
#include <vector>
#include <cstdint>

/******************************************************************************/
/* Mono headers                                                               */
/******************************************************************************/
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

/******************************************************************************/
/* Aeon headers                                                               */
/******************************************************************************/
#include <aeon/utility.h>

#include <aeon/mono/mono_exception.h>
#include <aeon/mono/mono_gchandle.h>
#include <aeon/mono/mono_assembly.h>
#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_class.h>
#include <aeon/mono/mono_object.h>
#include <aeon/mono/mono_string.h>
#include <aeon/mono/mono_class_instance.h>
#include <aeon/mono/mono_method.h>