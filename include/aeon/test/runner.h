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

namespace aeon
{
namespace test
{

class test_assert_failure_exception : public std::runtime_error
{
public:
    test_assert_failure_exception(const std::string &file, int line, const std::string &msg) :
        std::runtime_error("(" + file + ":" + std::to_string(line) + ") " + msg)
    {
    }
};

using test_case_func = std::function<void()>;
using test_failure_list = std::list<std::string>;

class test_case
{
public:
    test_case(const std::string &test_suite, const std::string &test_name, test_case_func f) :
        suite(test_suite),
        name(test_name),
        func(f),
        failures(0)
    {
    }

    std::string suite;
    std::string name;
    test_case_func func;
    test_failure_list failures;
};

using test_case_map = std::map<std::string, test_case>;
using test_suite_map = std::map<std::string, test_case_map>;
using test_failed_list = std::list<test_case *>;

class runner : public utility::noncopyable
{
public:
    runner();
    ~runner();

    int run_all();

    void add_test_case(const std::string &suite,
        const std::string &testcase, test_case_func f);

    static runner *get();

private:
    test_suite_map tests_;
    test_failed_list failed_tests_;
};

extern runner *runner_;

class test_case_registrator : public utility::noncopyable
{
public:
    test_case_registrator(const std::string &suite,
        const std::string &testcase, test_case_func f)
    {
        runner::get()->add_test_case(suite, testcase, f);
    }
};

static int initialize(int argc, char *argv[])
{
    return runner::get()->run_all();
}

#define AEON_TEST_CASE(suite, case) \
    void func_##suite##_##case##__(); \
    aeon::test::test_case_registrator registrator_##suite##_##case##__(#suite, #case, []() { func_##suite##_##case##__(); }); \
    void func_##suite##_##case##__()

#define AEON_TEST_ASSERT_EQ(expected, actual) \
    if (expected != actual) \
    { \
        throw aeon::test::test_assert_failure_exception(__FILE__, __LINE__, "AEON_TEST_ASSERT_EQ");  \
    }

#define AEON_TEST_ASSERT_NE(expected, actual) \
    if (expected == actual) \
    { \
        throw aeon::test::test_assert_failure_exception(__FILE__, __LINE__, "AEON_TEST_ASSERT_NE");  \
    }

#define AEON_TEST_ASSERT_TRUE(actual) \
    if (actual != true) \
    { \
        throw aeon::test::test_assert_failure_exception(__FILE__, __LINE__, "AEON_TEST_ASSERT_TRUE");  \
    }

#define AEON_TEST_ASSERT_FALSE(actual) \
    if (actual != false) \
    { \
        throw aeon::test::test_assert_failure_exception(__FILE__, __LINE__, "AEON_TEST_ASSERT_FALSE");  \
    }

} // namespace test
} // namespace aeon
