#define BOOST_TEST_MODULE test_memory_stream
#include <boost/test/unit_test.hpp>
#include <aeon/utility.h>

struct test_fixture_linear_map_default_data
{
    test_fixture_linear_map_default_data()
    {
        linear_map_["One"] = 1;
        linear_map_["Two"] = 2;
        linear_map_["Three"] = 3;
        linear_map_["Four"] = 4;
        linear_map_["Five"] = 5;

        BOOST_REQUIRE_EQUAL(5, linear_map_.size());
    }

    ~test_fixture_linear_map_default_data()
    {
    }

    aeon::utility::linear_map<std::string, int> linear_map_;
};

BOOST_FIXTURE_TEST_SUITE(test_fixture_linear_map_default_data_suite,
    test_fixture_linear_map_default_data)

BOOST_AUTO_TEST_CASE(test_linear_map_at)
{
    int at_one = linear_map_.at("One");
    int at_two = linear_map_.at("Two");
    int at_three = linear_map_.at("Three");
    int at_four = linear_map_.at("Four");
    int at_five = linear_map_.at("Five");

    BOOST_REQUIRE_EQUAL(1, at_one);
    BOOST_REQUIRE_EQUAL(2, at_two);
    BOOST_REQUIRE_EQUAL(3, at_three);
    BOOST_REQUIRE_EQUAL(4, at_four);
    BOOST_REQUIRE_EQUAL(5, at_five);
}

BOOST_AUTO_TEST_CASE(test_linear_map_index_operator)
{
    int at_one = linear_map_["One"];
    int at_two = linear_map_["Two"];
    int at_three = linear_map_["Three"];
    int at_four = linear_map_["Four"];
    int at_five = linear_map_["Five"];

    BOOST_REQUIRE_EQUAL(1, at_one);
    BOOST_REQUIRE_EQUAL(2, at_two);
    BOOST_REQUIRE_EQUAL(3, at_three);
    BOOST_REQUIRE_EQUAL(4, at_four);
    BOOST_REQUIRE_EQUAL(5, at_five);
}

BOOST_AUTO_TEST_CASE(test_linear_map_index_operator_overwrite)
{
    linear_map_["Three"] = 42;
    linear_map_["Four"] = 32;

    int at_one = linear_map_["One"];
    int at_two = linear_map_["Two"];
    int at_three = linear_map_["Three"];
    int at_four = linear_map_["Four"];
    int at_five = linear_map_["Five"];

    BOOST_REQUIRE_EQUAL(1, at_one);
    BOOST_REQUIRE_EQUAL(2, at_two);
    BOOST_REQUIRE_EQUAL(42, at_three);
    BOOST_REQUIRE_EQUAL(32, at_four);
    BOOST_REQUIRE_EQUAL(5, at_five);

    BOOST_REQUIRE_EQUAL(5, linear_map_.size());
}

BOOST_AUTO_TEST_CASE(test_linear_map_index_operator_default)
{
    int cant_find = linear_map_["Something! 123"];

    BOOST_REQUIRE_EQUAL(0, cant_find);
    BOOST_REQUIRE_EQUAL(6, linear_map_.size());
}

BOOST_AUTO_TEST_CASE(test_linear_map_empty_and_clear)
{
    BOOST_REQUIRE_EQUAL(false, linear_map_.empty());
    linear_map_.clear();
    BOOST_REQUIRE_EQUAL(true, linear_map_.empty());
}

BOOST_AUTO_TEST_CASE(test_linear_map_find)
{
    auto result = linear_map_.find("Three");

    BOOST_REQUIRE_EQUAL("Three", result->first);
    BOOST_REQUIRE_EQUAL(3, result->second);
}

BOOST_AUTO_TEST_CASE(test_linear_map_not_found)
{
    auto result = linear_map_.find("Something! 123");

    BOOST_REQUIRE(result == linear_map_.end());
    BOOST_REQUIRE_EQUAL(5, linear_map_.size());
}

BOOST_AUTO_TEST_CASE(test_linear_map_iterate)
{
    int loop_times = 0;
    for (auto item : linear_map_)
    {
        if (item.first == "One")
            BOOST_REQUIRE_EQUAL(1, item.second);

        if (item.first == "Two")
            BOOST_REQUIRE_EQUAL(2, item.second);

        if (item.first == "Three")
            BOOST_REQUIRE_EQUAL(3, item.second);

        if (item.first == "Four")
            BOOST_REQUIRE_EQUAL(4, item.second);

        if (item.first == "Five")
            BOOST_REQUIRE_EQUAL(5, item.second);

        ++loop_times;
    }

    BOOST_REQUIRE_EQUAL(5, linear_map_.size());
    BOOST_REQUIRE_EQUAL(5, loop_times);
}

BOOST_AUTO_TEST_CASE(test_linear_map_erase_by_key)
{
    linear_map_.erase("Something! 123");
    BOOST_REQUIRE_EQUAL(5, linear_map_.size());

    linear_map_.erase("Three");
    BOOST_REQUIRE_EQUAL(4, linear_map_.size());

    linear_map_.erase("Two");
    BOOST_REQUIRE_EQUAL(3, linear_map_.size());
}

BOOST_AUTO_TEST_CASE(test_linear_map_erase_by_iterator)
{
    BOOST_REQUIRE_EQUAL(5, linear_map_.size());

    auto result = linear_map_.find("Three");
    linear_map_.erase(result);

    BOOST_REQUIRE_EQUAL(4, linear_map_.size());

    result = linear_map_.find("Two");
    linear_map_.erase(result);

    BOOST_REQUIRE_EQUAL(3, linear_map_.size());
}

BOOST_AUTO_TEST_SUITE_END()
