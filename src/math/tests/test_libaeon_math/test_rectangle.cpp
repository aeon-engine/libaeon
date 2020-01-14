// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/math/rectangle.h>
#include <aeon/math/rectangle_stream.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_rectangle, test_rectangle_default_int)
{
    const math::rectangle<int> rect;

    EXPECT_EQ(math::left(rect), 0);
    EXPECT_EQ(math::top(rect), 0);
    EXPECT_EQ(math::right(rect), 0);
    EXPECT_EQ(math::bottom(rect), 0);

    EXPECT_EQ(math::width(rect), 0);
    EXPECT_EQ(math::height(rect), 0);

    EXPECT_TRUE(math::empty(rect));
    EXPECT_EQ(math::size(rect), math::size2d<int>{});
}

TEST(test_rectangle, test_rectangle_default_float)
{
    const math::rectangle<float> rect;

    EXPECT_EQ(math::left(rect), 0.0f);
    EXPECT_EQ(math::top(rect), 0.0f);
    EXPECT_EQ(math::right(rect), 0.0f);
    EXPECT_EQ(math::bottom(rect), 0.0f);

    EXPECT_EQ(math::width(rect), 0.0f);
    EXPECT_EQ(math::height(rect), 0.0f);

    EXPECT_TRUE(math::empty(rect));
    EXPECT_EQ(math::size(rect), math::size2d<float>{});
}

TEST(test_rectangle, test_rectangle_width_height)
{
    const math::rectangle rect{0, 0, 10, 20};

    EXPECT_EQ(math::width(rect), 10);
    EXPECT_EQ(math::height(rect), 20);

    EXPECT_EQ(math::size(rect), math::size2d(10, 20));
}

TEST(test_rectangle, test_rectangle_translate_positive)
{
    const math::rectangle rect{5, 10, 15, 20};
    const auto new_rect = math::translated(rect, 10, 20);

    EXPECT_EQ(math::left(new_rect), 15);
    EXPECT_EQ(math::top(new_rect), 30);
    EXPECT_EQ(math::right(new_rect), 25);
    EXPECT_EQ(math::bottom(new_rect), 40);

    EXPECT_EQ(math::width(new_rect), math::width(rect));
    EXPECT_EQ(math::height(new_rect), math::height(rect));

    EXPECT_EQ(math::size(new_rect), math::size(rect));
}

TEST(test_rectangle, test_rectangle_translate_positive_vector2)
{
    const math::rectangle rect{5, 10, 15, 20};
    const math::vector2 translation_vec{10, 20};

    const auto new_rect = math::translated(rect, translation_vec);

    EXPECT_EQ(math::left(new_rect), 15);
    EXPECT_EQ(math::top(new_rect), 30);
    EXPECT_EQ(math::right(new_rect), 25);
    EXPECT_EQ(math::bottom(new_rect), 40);

    EXPECT_EQ(math::width(new_rect), math::width(rect));
    EXPECT_EQ(math::height(new_rect), math::height(rect));

    EXPECT_EQ(math::size(new_rect), math::size(rect));
}

TEST(test_rectangle, test_rectangle_contains)
{
    const math::rectangle rect{5, 10, 15, 20};
    const math::rectangle rect2{10, 10, 15, 20};
    const math::rectangle rect3{10, 10, 15, 19};

    EXPECT_TRUE(math::contains(rect, rect));
    EXPECT_TRUE(math::contains(rect2, rect));
    EXPECT_FALSE(math::contains(rect, rect2));
    EXPECT_TRUE(math::contains(rect3, rect));
    EXPECT_FALSE(math::contains(rect, rect3));
    EXPECT_TRUE(math::contains(rect3, rect2));
    EXPECT_FALSE(math::contains(rect2, rect3));
}

TEST(test_rectangle, test_rectangle_contains_vector)
{
    const math::rectangle rect{5, 10, 15, 20};
    const math::vector2 vec{5, 10};
    const math::vector2 vec2{15, 20};
    const math::vector2 vec3{16, 20};
    const math::vector2 vec4{4, 10};

    EXPECT_TRUE(math::contains(vec, rect));
    EXPECT_TRUE(math::contains(vec2, rect));
    EXPECT_FALSE(math::contains(vec3, rect));
    EXPECT_FALSE(math::contains(vec4, rect));
}

TEST(test_rectangle, test_rectangle_overlaps)
{
    const math::rectangle rect{10, 10, 20, 20};
    const math::rectangle rect2{15, 15, 25, 25};
    const math::rectangle rect3{21, 21, 25, 25};

    EXPECT_TRUE(math::overlaps(rect, rect));
    EXPECT_TRUE(math::overlaps(rect, rect2));
    EXPECT_TRUE(math::overlaps(rect2, rect));
    EXPECT_FALSE(math::overlaps(rect, rect3));
    EXPECT_FALSE(math::overlaps(rect3, rect));
    EXPECT_TRUE(math::overlaps(rect2, rect3));
    EXPECT_TRUE(math::overlaps(rect3, rect2));
}

TEST(test_rectangle, test_rectangle_intersection)
{
    const math::rectangle rect{10, 10, 20, 20};
    const math::rectangle rect2{15, 15, 25, 25};

    ASSERT_EQ(math::intersection(rect, rect2), (math::rectangle{15, 15, 20, 20}));
}

TEST(test_rectangle, test_rectangle_bounding_box)
{
    const math::rectangle rect{5, 5, 20, 20};
    const math::rectangle rect2{15, 15, 25, 30};
    const math::rectangle rect3{4, 30, 10, 50};

    ASSERT_EQ(math::bounding_box(rect, rect2, rect3), (math::rectangle{4, 5, 25, 50}));
}

TEST(test_rectangle, test_rectangle_center)
{
    const math::rectangle rect{0, 0, 20, 20};
    const math::rectangle rect2{10, 10, 20, 20};

    ASSERT_EQ(math::center(rect), (math::vector2{10, 10}));
    ASSERT_EQ(math::center(rect2), (math::vector2{15, 15}));
}

TEST(test_rectangle, test_rectangle_set_position)
{
    const math::rectangle rect{0, 0, 20, 20};
    const math::rectangle rect2{10, 10, 20, 20};

    ASSERT_EQ(math::positioned(rect, 10, 10), (math::rectangle{10, 10, 30, 30}));
    ASSERT_EQ(math::positioned(rect2, 0, 0), (math::rectangle{0, 0, 10, 10}));
}

TEST(test_rectangle, test_rectangle_slice_vertical)
{
    const math::rectangle rect{10, 10, 20, 20};

    const auto [rect1, rect2] = math::slice_vertical(rect, 0.5f);
    EXPECT_EQ(rect1, (math::rectangle{10, 10, 15, 20}));
    EXPECT_EQ(rect2, (math::rectangle{15, 10, 20, 20}));

    const auto [rect3, rect4] = math::slice_vertical(rect, 0.5);
    EXPECT_EQ(rect3, (math::rectangle{10, 10, 15, 20}));
    EXPECT_EQ(rect4, (math::rectangle{15, 10, 20, 20}));

    const auto [rect5, rect6] = math::slice_vertical(rect, 0.25f);
    EXPECT_EQ(rect5, (math::rectangle{10, 10, 12, 20}));
    EXPECT_EQ(rect6, (math::rectangle{12, 10, 20, 20}));

    const auto [rect7, rect8] = math::slice_vertical(rect, 0.25);
    EXPECT_EQ(rect7, (math::rectangle{10, 10, 12, 20}));
    EXPECT_EQ(rect8, (math::rectangle{12, 10, 20, 20}));

    const auto [rect9, rect10] = math::slice_vertical(rect, 0.75f);
    EXPECT_EQ(rect9, (math::rectangle{10, 10, 17, 20}));
    EXPECT_EQ(rect10, (math::rectangle{17, 10, 20, 20}));

    const auto [rect11, rect12] = math::slice_vertical(rect, 0.75);
    EXPECT_EQ(rect11, (math::rectangle{10, 10, 17, 20}));
    EXPECT_EQ(rect12, (math::rectangle{17, 10, 20, 20}));
}

TEST(test_rectangle, test_rectangle_slice_vertical_absolute)
{
    const math::rectangle rect{10, 10, 20, 20};

    const auto [rect1, rect2] = math::slice_vertical_absolute(rect, 15);
    EXPECT_EQ(rect1, (math::rectangle{10, 10, 15, 20}));
    EXPECT_EQ(rect2, (math::rectangle{15, 10, 20, 20}));

    const auto [rect3, rect4] = math::slice_vertical_absolute(rect, 15);
    EXPECT_EQ(rect3, (math::rectangle{10, 10, 15, 20}));
    EXPECT_EQ(rect4, (math::rectangle{15, 10, 20, 20}));

    const auto [rect5, rect6] = math::slice_vertical_absolute(rect, 12);
    EXPECT_EQ(rect5, (math::rectangle{10, 10, 12, 20}));
    EXPECT_EQ(rect6, (math::rectangle{12, 10, 20, 20}));

    const auto [rect7, rect8] = math::slice_vertical_absolute(rect, 12);
    EXPECT_EQ(rect7, (math::rectangle{10, 10, 12, 20}));
    EXPECT_EQ(rect8, (math::rectangle{12, 10, 20, 20}));

    const auto [rect9, rect10] = math::slice_vertical_absolute(rect, 17);
    EXPECT_EQ(rect9, (math::rectangle{10, 10, 17, 20}));
    EXPECT_EQ(rect10, (math::rectangle{17, 10, 20, 20}));

    const auto [rect11, rect12] = math::slice_vertical_absolute(rect, 17);
    EXPECT_EQ(rect11, (math::rectangle{10, 10, 17, 20}));
    EXPECT_EQ(rect12, (math::rectangle{17, 10, 20, 20}));
}

TEST(test_rectangle, test_rectangle_slice_horizontal)
{
    const math::rectangle rect{10, 10, 20, 20};

    const auto [rect1, rect2] = math::slice_horizontal(rect, 0.5f);
    EXPECT_EQ(rect1, (math::rectangle{10, 10, 20, 15}));
    EXPECT_EQ(rect2, (math::rectangle{10, 15, 20, 20}));

    const auto [rect3, rect4] = math::slice_horizontal(rect, 0.5);
    EXPECT_EQ(rect3, (math::rectangle{10, 10, 20, 15}));
    EXPECT_EQ(rect4, (math::rectangle{10, 15, 20, 20}));

    const auto [rect5, rect6] = math::slice_horizontal(rect, 0.25f);
    EXPECT_EQ(rect5, (math::rectangle{10, 10, 20, 12}));
    EXPECT_EQ(rect6, (math::rectangle{10, 12, 20, 20}));

    const auto [rect7, rect8] = math::slice_horizontal(rect, 0.25);
    EXPECT_EQ(rect7, (math::rectangle{10, 10, 20, 12}));
    EXPECT_EQ(rect8, (math::rectangle{10, 12, 20, 20}));

    const auto [rect9, rect10] = math::slice_horizontal(rect, 0.75f);
    EXPECT_EQ(rect9, (math::rectangle{10, 10, 20, 17}));
    EXPECT_EQ(rect10, (math::rectangle{10, 17, 20, 20}));

    const auto [rect11, rect12] = math::slice_horizontal(rect, 0.75);
    EXPECT_EQ(rect11, (math::rectangle{10, 10, 20, 17}));
    EXPECT_EQ(rect12, (math::rectangle{10, 17, 20, 20}));
}

TEST(test_rectangle, test_rectangle_slice_horizontal_absolute)
{
    const math::rectangle rect{10, 10, 20, 20};

    const auto [rect1, rect2] = math::slice_horizontal_absolute(rect, 15);
    EXPECT_EQ(rect1, (math::rectangle{10, 10, 20, 15}));
    EXPECT_EQ(rect2, (math::rectangle{10, 15, 20, 20}));

    const auto [rect3, rect4] = math::slice_horizontal_absolute(rect, 15);
    EXPECT_EQ(rect3, (math::rectangle{10, 10, 20, 15}));
    EXPECT_EQ(rect4, (math::rectangle{10, 15, 20, 20}));

    const auto [rect5, rect6] = math::slice_horizontal_absolute(rect, 12);
    EXPECT_EQ(rect5, (math::rectangle{10, 10, 20, 12}));
    EXPECT_EQ(rect6, (math::rectangle{10, 12, 20, 20}));

    const auto [rect7, rect8] = math::slice_horizontal_absolute(rect, 12);
    EXPECT_EQ(rect7, (math::rectangle{10, 10, 20, 12}));
    EXPECT_EQ(rect8, (math::rectangle{10, 12, 20, 20}));

    const auto [rect9, rect10] = math::slice_horizontal_absolute(rect, 17);
    EXPECT_EQ(rect9, (math::rectangle{10, 10, 20, 17}));
    EXPECT_EQ(rect10, (math::rectangle{10, 17, 20, 20}));

    const auto [rect11, rect12] = math::slice_horizontal_absolute(rect, 17);
    EXPECT_EQ(rect11, (math::rectangle{10, 10, 20, 17}));
    EXPECT_EQ(rect12, (math::rectangle{10, 17, 20, 20}));
}

TEST(test_rectangle, test_anchor_points)
{
    EXPECT_EQ((math::rectangle{math::vector2{0, 0}, math::size2d{10, 10}, math::anchor_point::left_top}),
              (math::rectangle{0, 0, 10, 10}));
    EXPECT_EQ((math::rectangle{math::vector2{0, 0}, math::size2d{10, 10}, math::anchor_point::left_center}),
              (math::rectangle{0, -5, 10, 5}));
    EXPECT_EQ((math::rectangle{math::vector2{0, 0}, math::size2d{10, 10}, math::anchor_point::left_bottom}),
              (math::rectangle{0, -10, 10, 0}));

    EXPECT_EQ((math::rectangle{math::vector2{0, 0}, math::size2d{10, 10}, math::anchor_point::right_top}),
              (math::rectangle{-10, 0, 0, 10}));
    EXPECT_EQ((math::rectangle{math::vector2{0, 0}, math::size2d{10, 10}, math::anchor_point::right_center}),
              (math::rectangle{-10, -5, 0, 5}));
    EXPECT_EQ((math::rectangle{math::vector2{0, 0}, math::size2d{10, 10}, math::anchor_point::right_bottom}),
              (math::rectangle{-10, -10, 0, 0}));

    EXPECT_EQ((math::rectangle{math::vector2{0, 0}, math::size2d{10, 10}, math::anchor_point::top_center}),
              (math::rectangle{-5, 0, 5, 10}));
    EXPECT_EQ((math::rectangle{math::vector2{0, 0}, math::size2d{10, 10}, math::anchor_point::bottom_center}),
              (math::rectangle{-5, -10, 5, 0}));
    EXPECT_EQ((math::rectangle{math::vector2{0, 0}, math::size2d{10, 10}, math::anchor_point::center}),
              (math::rectangle{-5, -5, 5, 5}));
}

TEST(test_rectangle, test_normalized)
{
    const math::rectangle rect1{0, 10, 20, 30};
    const math::rectangle rect2{20, 30, 0, 10};
    const math::rectangle rect3{0, 30, 20, 10};
    const math::rectangle rect4{20, 10, 0, 30};

    EXPECT_EQ(math::normalized(rect1), rect1);
    EXPECT_TRUE(math::valid(rect1));
    EXPECT_EQ(math::normalized(rect2), rect1);
    EXPECT_FALSE(math::valid(rect2));
    EXPECT_EQ(math::normalized(rect3), rect1);
    EXPECT_FALSE(math::valid(rect3));
    EXPECT_EQ(math::normalized(rect4), rect1);
    EXPECT_FALSE(math::valid(rect4));
}
