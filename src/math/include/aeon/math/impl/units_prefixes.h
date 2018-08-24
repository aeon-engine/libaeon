/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <aeon/math/math.h>

namespace aeon::math
{

struct prefix
{
};

struct null_prefix : prefix
{
    static constexpr auto value = 1.0;
};

struct yotta : prefix
{
    static constexpr auto value = 1e24;
};

struct zetta : prefix
{
    static constexpr auto value = 1e21;
};

struct exa : prefix
{
    static constexpr auto value = 1e18;
};

struct peta : prefix
{
    static constexpr auto value = 1e15;
};

struct tera : prefix
{
    static constexpr auto value = 1e12;
};

struct giga : prefix
{
    static constexpr auto value = 1e9;
};

struct mega : prefix
{
    static constexpr auto value = 1e6;
};

struct kilo : prefix
{
    static constexpr auto value = 1e3;
};

struct hecto : prefix
{
    static constexpr auto value = 1e2;
};

struct deca : prefix
{
    static constexpr auto value = 10;
};

struct deci : prefix
{
    static constexpr auto value = 1e-1;
};

struct centi : prefix
{
    static constexpr auto value = 1e-2;
};

struct milli : prefix
{
    static constexpr auto value = 1e-3;
};

struct micro : prefix
{
    static constexpr auto value = 1e-6;
};

struct nano : prefix
{
    static constexpr auto value = 1e-9;
};

struct pico : prefix
{
    static constexpr auto value = 1e-12;
};

struct femto : prefix
{
    static constexpr auto value = 1e-15;
};

struct atto : prefix
{
    static constexpr auto value = 1e-18;
};

struct zepto : prefix
{
    static constexpr auto value = 1e-21;
};

struct yocto : prefix
{
    static constexpr auto value = 1e-24;
};

struct kibi : prefix
{
    static constexpr auto value = 1024.0;
};

struct mebi : prefix
{
    static constexpr auto value = constexpr_pow(1024.0, 2);
};

struct gibi : prefix
{
    static constexpr auto value = constexpr_pow(1024.0, 3);
};

struct tebi : prefix
{
    static constexpr auto value = constexpr_pow(1024.0, 4);
};

struct pebi : prefix
{
    static constexpr auto value = constexpr_pow(1024.0, 5);
};

struct exbi : prefix
{
    static constexpr auto value = constexpr_pow(1024.0, 6);
};

struct zebi : prefix
{
    static constexpr auto value = constexpr_pow(1024.0, 7);
};

struct yobi : prefix
{
    static constexpr auto value = constexpr_pow(1024.0, 8);
};

} // namespace aeon::math
