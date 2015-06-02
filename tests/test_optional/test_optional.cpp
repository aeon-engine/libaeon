#define BOOST_TEST_MODULE test_utility_optional
#include <boost/test/unit_test.hpp>
#include <aeon/utility.h>

static bool optional_value_exception_pred(
    aeon::utility::optional_value_exception const &)
{
    return true;
}

BOOST_AUTO_TEST_CASE(test_utility_optional_create_int)
{
    aeon::utility::optional<int> test;
    BOOST_REQUIRE_EQUAL(false, test.has_value());
}

BOOST_AUTO_TEST_CASE(test_utility_optional_create_float)
{
    aeon::utility::optional<float> test;
    BOOST_REQUIRE_EQUAL(false, test.has_value());
}

BOOST_AUTO_TEST_CASE(test_utility_optional_create_string)
{
    aeon::utility::optional<std::string> test;
    BOOST_REQUIRE_EQUAL(false, test.has_value());
}

BOOST_AUTO_TEST_CASE(test_utility_optional_create_int_with_value)
{
    aeon::utility::optional<int> test = 1337;
    BOOST_REQUIRE_EQUAL(true, test.has_value());

    int testvalue = test;
    BOOST_REQUIRE_EQUAL(1337, testvalue);
}

BOOST_AUTO_TEST_CASE(test_utility_optional_create_float_with_value)
{
    aeon::utility::optional<float> test = 1337.0f;
    BOOST_REQUIRE_EQUAL(true, test.has_value());
}

BOOST_AUTO_TEST_CASE(test_utility_optional_create_string_with_value)
{
    aeon::utility::optional<std::string> test = "1337!";
    BOOST_REQUIRE_EQUAL(true, test.has_value());
}

BOOST_AUTO_TEST_CASE(test_utility_optional_change_int_value)
{
    aeon::utility::optional<int> test = 1337;
    BOOST_REQUIRE_EQUAL(true, test.has_value());

    test = 1338;
    BOOST_REQUIRE_EQUAL(true, test.has_value());
}

BOOST_AUTO_TEST_CASE(test_utility_optional_change_int_value2)
{
    aeon::utility::optional<int> test;
    BOOST_REQUIRE_EQUAL(false, test.has_value());

    test = 1338;
    BOOST_REQUIRE_EQUAL(true, test.has_value());
}

BOOST_AUTO_TEST_CASE(test_utility_optional_change_float_value)
{
    aeon::utility::optional<float> test = 1337.0f;
    BOOST_REQUIRE_EQUAL(true, test.has_value());

    test = 1338.1f;
    BOOST_REQUIRE_EQUAL(true, test.has_value());
}

BOOST_AUTO_TEST_CASE(test_utility_optional_change_float_value2)
{
    aeon::utility::optional<float> test;
    BOOST_REQUIRE_EQUAL(false, test.has_value());

    test = 1338.1f;
    BOOST_REQUIRE_EQUAL(true, test.has_value());
}

BOOST_AUTO_TEST_CASE(test_utility_optional_change_string_value)
{
    aeon::utility::optional<std::string> test = "1337!";
    BOOST_REQUIRE_EQUAL(true, test.has_value());

    test = std::string("42?");
    BOOST_REQUIRE_EQUAL(true, test.has_value());
}

BOOST_AUTO_TEST_CASE(test_utility_optional_change_string_value2)
{
    aeon::utility::optional<std::string> test;
    BOOST_REQUIRE_EQUAL(false, test.has_value());

    test = std::string("42?");
    BOOST_REQUIRE_EQUAL(true, test.has_value());
}

BOOST_AUTO_TEST_CASE(test_utility_optional_reset_int)
{
    aeon::utility::optional<int> test = 3;
    BOOST_REQUIRE_EQUAL(true, test.has_value());

    test.reset();
    BOOST_REQUIRE_EQUAL(false, test.has_value());
}

BOOST_AUTO_TEST_CASE(test_utility_optional_reset_float)
{
    aeon::utility::optional<float> test = 3.0f;
    BOOST_REQUIRE_EQUAL(true, test.has_value());

    test.reset();
    BOOST_REQUIRE_EQUAL(false, test.has_value());
}

BOOST_AUTO_TEST_CASE(test_utility_optional_exception_int)
{
    aeon::utility::optional<int> test;

    BOOST_REQUIRE_EQUAL(false, test.has_value());
    BOOST_REQUIRE_EXCEPTION(int value = test,
        aeon::utility::optional_value_exception,
        optional_value_exception_pred
    );
}

BOOST_AUTO_TEST_CASE(test_utility_optional_exception_int2)
{
    aeon::utility::optional<int> test;

    BOOST_REQUIRE_EQUAL(false, test.has_value());

    BOOST_REQUIRE_EXCEPTION(int value = test,
        aeon::utility::optional_value_exception,
        optional_value_exception_pred
    );

    test = 1337;
    BOOST_REQUIRE_EQUAL(true, test.has_value());
    int value = test;
    BOOST_REQUIRE_EQUAL(1337, value);
}

BOOST_AUTO_TEST_CASE(test_utility_optional_exception_float)
{
    aeon::utility::optional<float> test;

    BOOST_REQUIRE_EQUAL(false, test.has_value());
    BOOST_REQUIRE_EXCEPTION(float value = test,
        aeon::utility::optional_value_exception,
        optional_value_exception_pred
    );
}


BOOST_AUTO_TEST_CASE(test_utility_optional_exception_float2)
{
    aeon::utility::optional<float> test;

    BOOST_REQUIRE_EQUAL(false, test.has_value());

    BOOST_REQUIRE_EXCEPTION(float value = test,
        aeon::utility::optional_value_exception,
        optional_value_exception_pred
    );

    test = 1337.0f;
    BOOST_REQUIRE_EQUAL(true, test.has_value());
    float value = test;
    BOOST_REQUIRE_EQUAL(1337.0f, value);
}

BOOST_AUTO_TEST_CASE(test_utility_optional_exception_string)
{
    aeon::utility::optional<std::string> test;

    BOOST_REQUIRE_EQUAL(false, test.has_value());
    BOOST_REQUIRE_EXCEPTION(std::string value = test,
        aeon::utility::optional_value_exception,
        optional_value_exception_pred
    );
}

BOOST_AUTO_TEST_CASE(test_utility_optional_exception_string2)
{
    aeon::utility::optional<std::string> test;

    BOOST_REQUIRE_EQUAL(false, test.has_value());
    BOOST_REQUIRE_EXCEPTION(std::string value = test,
        aeon::utility::optional_value_exception,
        optional_value_exception_pred
    );

    test = std::string("Hello!");
    BOOST_REQUIRE_EQUAL(true, test.has_value());
    std::string value = test;
    BOOST_REQUIRE_EQUAL(std::string("Hello!"), value);
}

BOOST_AUTO_TEST_CASE(test_utility_optional_compare_int)
{
    aeon::utility::optional<int> test = 3;

    BOOST_REQUIRE(test == 3);
}

BOOST_AUTO_TEST_CASE(test_utility_optional_compare_float)
{
    aeon::utility::optional<float> test = 3.1f;
    BOOST_REQUIRE(test == 3.1f);
}

BOOST_AUTO_TEST_CASE(test_utility_optional_compare_string)
{
    aeon::utility::optional<std::string> test = "Testing";
    BOOST_REQUIRE(std::string(test) == std::string("Testing"));
}
