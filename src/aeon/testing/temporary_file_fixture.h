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
namespace testing
{

class temporary_file
{
public:
    temporary_file();
    explicit temporary_file(const std::string &extension);

    ~temporary_file();

    std::string get_temporary_file_path() const;

    bool assert_temporary_file_present() const;

    void delete_temporary_file() const;

protected:
    std::string path_;
};

// If gtest was included before this header, enable the test fixture code.
#ifdef ENABLE_TEMPORARY_FILE_FIXTURE
struct temporary_file_fixture : public temporary_file, public ::testing::Test
{
};
#endif // ENABLE_TEMPORARY_FILE_FIXTURE

} // namespace testing
} // namespace aeon
