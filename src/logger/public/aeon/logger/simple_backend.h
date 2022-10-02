// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/logger/base_backend.h>

namespace aeon::logger
{

class simple_backend final : public base_backend
{
public:
    simple_backend() = default;
    virtual ~simple_backend() = default;

    simple_backend(const simple_backend &) = delete;
    auto operator=(const simple_backend &) noexcept -> simple_backend & = delete;

    simple_backend(simple_backend &&) = delete;
    auto operator=(simple_backend &&) noexcept -> simple_backend & = delete;

    void log(const std::string &message, const std::string &module, const log_level level) override;
};

} // namespace aeon::logger
