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

#include <gtest/gtest.h>
#include <aeon/math/size3d.h>
#include <aeon/math/size3d_stream.h>

using namespace aeon;

TEST(test_size3d, test_size3d_default_int)
{
    math::size3d<int> size;
}

TEST(test_size3d, test_size3d_clamp)
{
    const math::size3d min{5, 10, 20};
    const math::size3d max{50, 100, 200};

    EXPECT_EQ(math::clamp(math::size3d{10, 20, 30}, min, max), (math::size3d{10, 20, 30}));
    EXPECT_EQ(math::clamp(math::size3d{40, 90, 190}, min, max), (math::size3d{40, 90, 190}));
    EXPECT_EQ(math::clamp(math::size3d{4, 20, 19}, min, max), (math::size3d{5, 20, 20}));
    EXPECT_EQ(math::clamp(math::size3d{5, 9, 201}, min, max), (math::size3d{5, 10, 200}));
    EXPECT_EQ(math::clamp(math::size3d{51, 90, 300}, min, max), (math::size3d{50, 90, 200}));
    EXPECT_EQ(math::clamp(math::size3d{50, 110, 1}, min, max), (math::size3d{50, 100, 20}));
}
