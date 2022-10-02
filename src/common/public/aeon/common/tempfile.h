// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/uuid.h>
#include <filesystem>

namespace aeon::common
{

[[nodiscard]] inline auto generate_temporary_file_path()
{
    const auto uuid = uuid::generate();
    return std::filesystem::temp_directory_path() / uuid.str();
}

} // namespace aeon::common
