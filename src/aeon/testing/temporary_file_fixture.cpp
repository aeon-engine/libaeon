/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/testing.h>

namespace aeon
{
namespace testing
{

temporary_file::temporary_file()
    : path_(filesystem::generate_temporary_file_path())
{
}

temporary_file::temporary_file(const std::string &extension)
    : path_(filesystem::generate_temporary_file_path() + "." + extension)
{
}

temporary_file::~temporary_file()
{
    if (filesystem::exists(path_))
        delete_temporary_file();
}

std::string temporary_file::get_temporary_file_path() const
{
    return path_;
}

bool temporary_file::assert_temporary_file_present() const
{
    return filesystem::exists(path_);
}

void temporary_file::delete_temporary_file() const
{
    filesystem::delete_file(path_);
}

} // namespace testing
} // namespace aeon
