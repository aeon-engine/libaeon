// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/logger/base_backend.h>

namespace aeon::logger
{

class simple_backend final : public base_backend
{
public:
    simple_backend() = default;
    ~simple_backend() final = default;

    simple_backend(const simple_backend &) = delete;
    auto operator=(const simple_backend &) noexcept -> simple_backend & = delete;

    simple_backend(simple_backend &&) = delete;
    auto operator=(simple_backend &&) noexcept -> simple_backend & = delete;

    void log(const common::string &message, const common::string &module, const log_level level) final;
};

} // namespace aeon::logger
