// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

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

    [[nodiscard]] auto to_uchars(const std::u8string_view &str) const
    {
        UErrorCode status = U_ZERO_ERROR;
        const auto target_length = to_uchars_length(str);

        std::u16string target;
        target.resize(target_length);

        ucnv_toUChars(converter_, reinterpret_cast<UChar *>(std::data(target)), target_length,
                      reinterpret_cast<const char *>(std::data(str)), static_cast<int32_t>(std::size(str)), &status);

        if (U_FAILURE(status))
            throw unicode_conversion_exception{};

        return target;
    }

    [[nodiscard]] auto from_uchars(const std::u16string_view &str) const
    {
        UErrorCode status = U_ZERO_ERROR;
        const auto target_length = from_uchars_length(str);

        std::u8string target;
        target.resize(target_length);

        ucnv_fromUChars(converter_, reinterpret_cast<char *>(std::data(target)), target_length,
                        reinterpret_cast<const UChar *>(std::data(str)), static_cast<int32_t>(std::size(str)), &status);

        if (U_FAILURE(status))
            throw unicode_conversion_exception{};

        return target;
    }

    uconverter(uconverter &&) noexcept = delete;
    auto operator=(uconverter &&) noexcept -> uconverter & = delete;

    uconverter(const uconverter &) = delete;
    auto operator=(const uconverter &) -> uconverter & = delete;

private:
    [[nodiscard]] auto to_uchars_length(const std::u8string_view &str) const -> int32_t
    {
        UErrorCode status = U_ZERO_ERROR;
        const auto size = ucnv_toUChars(converter_, nullptr, 0, reinterpret_cast<const char *>(std::data(str)),
                                        static_cast<int32_t>(std::size(str)), &status);

        if (status != U_BUFFER_OVERFLOW_ERROR)
            throw unicode_conversion_exception{};

        return size;
    }

    [[nodiscard]] auto from_uchars_length(const std::u16string_view &str) const -> int32_t
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
