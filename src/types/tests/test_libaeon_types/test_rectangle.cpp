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
#include <aeon/types/rectangle.h>

using namespace aeon;

TEST(test_rectangle, test_rectangle_default_int)
{
    const types::rectangle<int> rect;

    EXPECT_EQ(types::left(rect), 0);
    EXPECT_EQ(types::top(rect), 0);
    EXPECT_EQ(types::right(rect), 0);
    EXPECT_EQ(types::bottom(rect), 0);

    EXPECT_EQ(types::width(rect), 0);
    EXPECT_EQ(types::height(rect), 0);

    EXPECT_TRUE(types::empty(rect));
    EXPECT_EQ(types::size(rect), types::size2d<int>{});
}

TEST(test_rectangle, test_rectangle_default_float)
{
    const types::rectangle<float> rect;

    EXPECT_EQ(types::left(rect), 0.0f);
    EXPECT_EQ(types::top(rect), 0.0f);
    EXPECT_EQ(types::right(rect), 0.0f);
    EXPECT_EQ(types::bottom(rect), 0.0f);

    EXPECT_EQ(types::width(rect), 0.0f);
    EXPECT_EQ(types::height(rect), 0.0f);

    EXPECT_TRUE(types::empty(rect));
    EXPECT_EQ(types::size(rect), types::size2d<float>{});
}

TEST(test_rectangle, test_rectangle_width_height)
{
    const types::rectangle rect{0, 0, 10, 20};

    EXPECT_EQ(types::width(rect), 10);
    EXPECT_EQ(types::height(rect), 20);

    EXPECT_EQ(types::size(rect), types::size2d(10, 20));
}

TEST(test_rectangle, test_rectangle_translate_positive)
{
    const types::rectangle rect{5, 10, 15, 20};
    const auto new_rect = types::translate(rect, 10, 20);

    EXPECT_EQ(types::left(new_rect), 15);
    EXPECT_EQ(types::top(new_rect), 30);
    EXPECT_EQ(types::right(new_rect), 25);
    EXPECT_EQ(types::bottom(new_rect), 40);

    EXPECT_EQ(types::width(new_rect), types::width(rect));
    EXPECT_EQ(types::height(new_rect), types::height(rect));

    EXPECT_EQ(types::size(new_rect), types::size(rect));
}

TEST(test_rectangle, test_rectangle_translate_positive_vector2)
{
    const types::rectangle rect{5, 10, 15, 20};
    const math::vector2 translation_vec{10, 20};

    const auto new_rect = types::translate(rect, translation_vec);

    EXPECT_EQ(types::left(new_rect), 15);
    EXPECT_EQ(types::top(new_rect), 30);
    EXPECT_EQ(types::right(new_rect), 25);
    EXPECT_EQ(types::bottom(new_rect), 40);

    EXPECT_EQ(types::width(new_rect), types::width(rect));
    EXPECT_EQ(types::height(new_rect), types::height(rect));

    EXPECT_EQ(types::size(new_rect), types::size(rect));
}

TEST(test_rectangle, test_rectangle_contains)
{
    const types::rectangle rect{5, 10, 15, 20};
    const types::rectangle rect2{10, 10, 15, 20};
    const types::rectangle rect3{10, 10, 15, 19};

    EXPECT_TRUE(types::contains(rect, rect));
    EXPECT_TRUE(types::contains(rect2, rect));
    EXPECT_FALSE(types::contains(rect, rect2));
    EXPECT_TRUE(types::contains(rect3, rect));
    EXPECT_FALSE(types::contains(rect, rect3));
    EXPECT_TRUE(types::contains(rect3, rect2));
    EXPECT_FALSE(types::contains(rect2, rect3));
}

TEST(test_rectangle, test_rectangle_contains_vector)
{
    const types::rectangle rect{5, 10, 15, 20};
    const math::vector2 vec{5, 10};
    const math::vector2 vec2{15, 20};
    const math::vector2 vec3{16, 20};
    const math::vector2 vec4{4, 10};

    EXPECT_TRUE(types::contains(vec, rect));
    EXPECT_TRUE(types::contains(vec2, rect));
    EXPECT_FALSE(types::contains(vec3, rect));
    EXPECT_FALSE(types::contains(vec4, rect));
}

TEST(test_rectangle, test_rectangle_overlaps)
{
    const types::rectangle rect{10, 10, 20, 20};
    const types::rectangle rect2{15, 15, 25, 25};
    const types::rectangle rect3{21, 21, 25, 25};

    EXPECT_TRUE(types::overlaps(rect, rect));
    EXPECT_TRUE(types::overlaps(rect, rect2));
    EXPECT_TRUE(types::overlaps(rect2, rect));
    EXPECT_FALSE(types::overlaps(rect, rect3));
    EXPECT_FALSE(types::overlaps(rect3, rect));
    EXPECT_TRUE(types::overlaps(rect2, rect3));
    EXPECT_TRUE(types::overlaps(rect3, rect2));
}

TEST(test_rectangle, test_rectangle_intersection)
{
    const types::rectangle rect{10, 10, 20, 20};
    const types::rectangle rect2{15, 15, 25, 25};

    ASSERT_EQ(types::intersection(rect, rect2), (types::rectangle{15, 15, 20, 20}));
}

TEST(test_rectangle, test_rectangle_bounding_box)
{
    const types::rectangle rect{5, 5, 20, 20};
    const types::rectangle rect2{15, 15, 25, 30};
    const types::rectangle rect3{4, 30, 10, 50};

    ASSERT_EQ(types::bounding_box(rect, rect2, rect3), (types::rectangle{4, 5, 25, 50}));
}

TEST(test_rectangle, test_rectangle_center)
{
    const types::rectangle rect{0, 0, 20, 20};
    const types::rectangle rect2{10, 10, 20, 20};

    ASSERT_EQ(types::center(rect), (math::vector2{10, 10}));
    ASSERT_EQ(types::center(rect2), (math::vector2{15, 15}));
}

TEST(test_rectangle, test_rectangle_set_position)
{
    const types::rectangle rect{0, 0, 20, 20};
    const types::rectangle rect2{10, 10, 20, 20};

    ASSERT_EQ(types::set_position(rect, 10, 10), (types::rectangle{10, 10, 30, 30}));
    ASSERT_EQ(types::set_position(rect2, 0, 0), (types::rectangle{0, 0, 10, 10}));
}

TEST(test_rectangle, test_rectangle_slice_vertical)
{
    const types::rectangle rect{10, 10, 20, 20};

    const auto [rect1, rect2] = types::slice_vertical(rect, 0.5f);
    EXPECT_EQ(rect1, (types::rectangle{10, 10, 15, 20}));
    EXPECT_EQ(rect2, (types::rectangle{15, 10, 20, 20}));

    const auto [rect3, rect4] = types::slice_vertical(rect, 0.5);
    EXPECT_EQ(rect3, (types::rectangle{10, 10, 15, 20}));
    EXPECT_EQ(rect4, (types::rectangle{15, 10, 20, 20}));

    const auto [rect5, rect6] = types::slice_vertical(rect, 0.25f);
    EXPECT_EQ(rect5, (types::rectangle{10, 10, 12, 20}));
    EXPECT_EQ(rect6, (types::rectangle{12, 10, 20, 20}));

    const auto [rect7, rect8] = types::slice_vertical(rect, 0.25);
    EXPECT_EQ(rect7, (types::rectangle{10, 10, 12, 20}));
    EXPECT_EQ(rect8, (types::rectangle{12, 10, 20, 20}));

    const auto [rect9, rect10] = types::slice_vertical(rect, 0.75f);
    EXPECT_EQ(rect9, (types::rectangle{10, 10, 17, 20}));
    EXPECT_EQ(rect10, (types::rectangle{17, 10, 20, 20}));

    const auto [rect11, rect12] = types::slice_vertical(rect, 0.75);
    EXPECT_EQ(rect11, (types::rectangle{10, 10, 17, 20}));
    EXPECT_EQ(rect12, (types::rectangle{17, 10, 20, 20}));
}

TEST(test_rectangle, test_rectangle_slice_vertical_absolute)
{
    const types::rectangle rect{10, 10, 20, 20};

    const auto [rect1, rect2] = types::slice_vertical_absolute(rect, 15);
    EXPECT_EQ(rect1, (types::rectangle{10, 10, 15, 20}));
    EXPECT_EQ(rect2, (types::rectangle{15, 10, 20, 20}));

    const auto [rect3, rect4] = types::slice_vertical_absolute(rect, 15);
    EXPECT_EQ(rect3, (types::rectangle{10, 10, 15, 20}));
    EXPECT_EQ(rect4, (types::rectangle{15, 10, 20, 20}));

    const auto [rect5, rect6] = types::slice_vertical_absolute(rect, 12);
    EXPECT_EQ(rect5, (types::rectangle{10, 10, 12, 20}));
    EXPECT_EQ(rect6, (types::rectangle{12, 10, 20, 20}));

    const auto [rect7, rect8] = types::slice_vertical_absolute(rect, 12);
    EXPECT_EQ(rect7, (types::rectangle{10, 10, 12, 20}));
    EXPECT_EQ(rect8, (types::rectangle{12, 10, 20, 20}));

    const auto [rect9, rect10] = types::slice_vertical_absolute(rect, 17);
    EXPECT_EQ(rect9, (types::rectangle{10, 10, 17, 20}));
    EXPECT_EQ(rect10, (types::rectangle{17, 10, 20, 20}));

    const auto [rect11, rect12] = types::slice_vertical_absolute(rect, 17);
    EXPECT_EQ(rect11, (types::rectangle{10, 10, 17, 20}));
    EXPECT_EQ(rect12, (types::rectangle{17, 10, 20, 20}));
}

TEST(test_rectangle, test_rectangle_slice_horizontal)
{
    const types::rectangle rect{10, 10, 20, 20};

    const auto [rect1, rect2] = types::slice_horizontal(rect, 0.5f);
    EXPECT_EQ(rect1, (types::rectangle{10, 10, 20, 15}));
    EXPECT_EQ(rect2, (types::rectangle{10, 15, 20, 20}));

    const auto [rect3, rect4] = types::slice_horizontal(rect, 0.5);
    EXPECT_EQ(rect3, (types::rectangle{10, 10, 20, 15}));
    EXPECT_EQ(rect4, (types::rectangle{10, 15, 20, 20}));

    const auto [rect5, rect6] = types::slice_horizontal(rect, 0.25f);
    EXPECT_EQ(rect5, (types::rectangle{10, 10, 20, 12}));
    EXPECT_EQ(rect6, (types::rectangle{10, 12, 20, 20}));

    const auto [rect7, rect8] = types::slice_horizontal(rect, 0.25);
    EXPECT_EQ(rect7, (types::rectangle{10, 10, 20, 12}));
    EXPECT_EQ(rect8, (types::rectangle{10, 12, 20, 20}));

    const auto [rect9, rect10] = types::slice_horizontal(rect, 0.75f);
    EXPECT_EQ(rect9, (types::rectangle{10, 10, 20, 17}));
    EXPECT_EQ(rect10, (types::rectangle{10, 17, 20, 20}));

    const auto [rect11, rect12] = types::slice_horizontal(rect, 0.75);
    EXPECT_EQ(rect11, (types::rectangle{10, 10, 20, 17}));
    EXPECT_EQ(rect12, (types::rectangle{10, 17, 20, 20}));
}

TEST(test_rectangle, test_rectangle_slice_horizontal_absolute)
{
    const types::rectangle rect{10, 10, 20, 20};

    const auto [rect1, rect2] = types::slice_horizontal_absolute(rect, 15);
    EXPECT_EQ(rect1, (types::rectangle{10, 10, 20, 15}));
    EXPECT_EQ(rect2, (types::rectangle{10, 15, 20, 20}));

    const auto [rect3, rect4] = types::slice_horizontal_absolute(rect, 15);
    EXPECT_EQ(rect3, (types::rectangle{10, 10, 20, 15}));
    EXPECT_EQ(rect4, (types::rectangle{10, 15, 20, 20}));

    const auto [rect5, rect6] = types::slice_horizontal_absolute(rect, 12);
    EXPECT_EQ(rect5, (types::rectangle{10, 10, 20, 12}));
    EXPECT_EQ(rect6, (types::rectangle{10, 12, 20, 20}));

    const auto [rect7, rect8] = types::slice_horizontal_absolute(rect, 12);
    EXPECT_EQ(rect7, (types::rectangle{10, 10, 20, 12}));
    EXPECT_EQ(rect8, (types::rectangle{10, 12, 20, 20}));

    const auto [rect9, rect10] = types::slice_horizontal_absolute(rect, 17);
    EXPECT_EQ(rect9, (types::rectangle{10, 10, 20, 17}));
    EXPECT_EQ(rect10, (types::rectangle{10, 17, 20, 20}));

    const auto [rect11, rect12] = types::slice_horizontal_absolute(rect, 17);
    EXPECT_EQ(rect11, (types::rectangle{10, 10, 20, 17}));
    EXPECT_EQ(rect12, (types::rectangle{10, 17, 20, 20}));
}

TEST(test_rectangle, test_anchor_points)
{
    EXPECT_EQ((types::rectangle{math::vector2{0, 0}, types::size2d{10, 10}, types::anchor_point::left_top}),
              (types::rectangle{0, 0, 10, 10}));
    EXPECT_EQ((types::rectangle{math::vector2{0, 0}, types::size2d{10, 10}, types::anchor_point::left_center}),
              (types::rectangle{0, -5, 10, 5}));
    EXPECT_EQ((types::rectangle{math::vector2{0, 0}, types::size2d{10, 10}, types::anchor_point::left_bottom}),
              (types::rectangle{0, -10, 10, 0}));

    EXPECT_EQ((types::rectangle{math::vector2{0, 0}, types::size2d{10, 10}, types::anchor_point::right_top}),
              (types::rectangle{-10, 0, 0, 10}));
    EXPECT_EQ((types::rectangle{math::vector2{0, 0}, types::size2d{10, 10}, types::anchor_point::right_center}),
              (types::rectangle{-10, -5, 0, 5}));
    EXPECT_EQ((types::rectangle{math::vector2{0, 0}, types::size2d{10, 10}, types::anchor_point::right_bottom}),
              (types::rectangle{-10, -10, 0, 0}));

    EXPECT_EQ((types::rectangle{math::vector2{0, 0}, types::size2d{10, 10}, types::anchor_point::top_center}),
              (types::rectangle{-5, 0, 5, 10}));
    EXPECT_EQ((types::rectangle{math::vector2{0, 0}, types::size2d{10, 10}, types::anchor_point::bottom_center}),
              (types::rectangle{-5, -10, 5, 0}));
    EXPECT_EQ((types::rectangle{math::vector2{0, 0}, types::size2d{10, 10}, types::anchor_point::center}),
              (types::rectangle{-5, -5, 5, 5}));
}
