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

#include <aeon/test.h>

namespace aeon
{
namespace test
{

static const int test_max_line_length = 70;

runner *runner_ = nullptr;

runner::runner()
{
}

runner::~runner()
{
}

int runner::run_all()
{
    std::cout << "Running " << tests_.size()
        << " test suite(s)." << std::endl;

    for (auto &suite : tests_)
    {
        std::string suite_name = suite.first;

        std::cout << "Running " << suite.second.size() << " tests in " << suite_name << std::endl;

        for (auto &suite_test_case : suite.second)
        {
            test_case &c = suite_test_case.second;

            std::string full_test_name = c.suite + "." + c.name;
            int dot_count = test_max_line_length - full_test_name.length();

            if (dot_count <= 0)
                dot_count = 1;

            std::cout << full_test_name << std::string(dot_count, '.');

            try
            {
                c.func();
            }
            catch (const test_assert_failure_exception &e)
            {
                c.failures.push_back(e.what());
            }
            catch (const std::exception &e)
            {
                c.failures.push_back(std::string("Exception thrown: ") + e.what());
            }
            catch (...)
            {
                c.failures.push_back("Unknown exception thrown.");
            }

            if (!c.failures.empty())
            {
                std::cout << "failed" << std::endl;
                failed_tests_.push_back(&c);
            }
            else
            {
                std::cout << "ok" << std::endl;
            }
        }
    }

    std::cout << std::endl << std::endl;

    if (!failed_tests_.empty())
    {
        std::cout << "Failed tests: " << std::endl;
        for (auto f : failed_tests_)
        {
            std::string full_test_name = f->suite + "." + f->name;
            std::cout << "  - " << full_test_name << std::endl;
            for (auto fm : f->failures)
            {
                std::cout << "    - " << fm << std::endl;
            }
        }
    }

    int return_code = failed_tests_.size();
    delete this;

    return return_code;
}

void runner::add_test_case(const std::string &suite, const std::string &testcase, test_case_func f)
{
    auto &test_case_map = tests_[suite];
    test_case_map.emplace(testcase, test_case(suite, testcase, f));
}

runner *runner::get()
{
    if (!runner_)
    {
        runner_ = new runner();
    }

    return runner_;
}

} // namespace test
} // namespace aeon
