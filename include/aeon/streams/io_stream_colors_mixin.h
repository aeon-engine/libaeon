/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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

namespace aeon
{
namespace streams
{

enum class color
{
    black,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white
};

enum class weight
{
    normal,
    bold
};

class io_stream_colors_mixin
{
public:
    void set_color(color c, weight w = weight::normal);
    void reset_color();
};

} // namespace streams
} // namespace aeon
