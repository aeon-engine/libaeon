// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/unicode/exception.h>
#include <unicode/ucnv.h>
#include <string>

namespace aeon::unicode::internal
{

class uconverter final
{
public:
    explicit uconverter(const char *const encoding)
        : converter_{nullptr}
    {
        UErrorCode status = U_ZERO_ERROR;
        converter_ = ucnv_open(encoding, &status);

        if (U_FAILURE(status))
            throw unicode_conversion_exception{};
    }

    ~uconverter()
    {
        if (converter_ != nullptr)
            ucnv_close(converter_);
    }

    auto to_uchars(const std::string &str) const
    {
        UErrorCode status = U_ZERO_ERROR;
        const auto target_length = to_uchars_length(str);

        std::wstring target;
        target.resize(target_length);

        ucnv_toUChars(converter_, reinterpret_cast<UChar *>(std::data(target)), target_length, std::data(str),
                      static_cast<int32_t>(std::size(str)), &status);

        if (U_FAILURE(status))
            throw unicode_conversion_exception{};

        return target;
    }

    auto from_uchars(const std::wstring &str) const
    {
        UErrorCode status = U_ZERO_ERROR;
        const auto target_length = from_uchars_length(str);

        std::string target;
        target.resize(target_length);

        ucnv_fromUChars(converter_, std::data(target), target_length, reinterpret_cast<const UChar *>(std::data(str)),
                        static_cast<int32_t>(std::size(str)), &status);

        if (U_FAILURE(status))
            throw unicode_conversion_exception{};

        return target;
    }

    uconverter(uconverter &&) noexcept = delete;
    auto operator=(uconverter &&) noexcept -> uconverter & = delete;

    uconverter(const uconverter &) = delete;
    auto operator=(const uconverter &) -> uconverter & = delete;

private:
    auto to_uchars_length(const std::string &str) const -> int32_t
    {
        UErrorCode status = U_ZERO_ERROR;
        const auto size =
            ucnv_toUChars(converter_, nullptr, 0, std::data(str), static_cast<int32_t>(std::size(str)), &status);

        if (status != U_BUFFER_OVERFLOW_ERROR)
            throw unicode_conversion_exception{};

        return size;
    }

    auto from_uchars_length(const std::wstring &str) const -> int32_t
    {
        UErrorCode status = U_ZERO_ERROR;

        const auto size = ucnv_fromUChars(converter_, nullptr, 0, reinterpret_cast<const char16_t *>(std::data(str)),
                                          static_cast<int32_t>(std::size(str)), &status);

        if (status != U_BUFFER_OVERFLOW_ERROR)
            throw unicode_conversion_exception{};

        return size;
    }

    UConverter *converter_;
};

} // namespace aeon::unicode::internal
