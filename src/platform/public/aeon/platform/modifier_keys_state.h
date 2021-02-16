// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <cstdint>

namespace aeon::platform
{

namespace internal
{

struct modifier_keys_state_data final
{
    std::uint32_t left_shift_state_ : 1 = false;
    std::uint32_t right_shift_state_ : 1 = false;
    std::uint32_t left_ctrl_state_ : 1 = false;
    std::uint32_t right_ctrl_state_ : 1 = false;
    std::uint32_t left_alt_state_ : 1 = false;
    std::uint32_t right_alt_state_ : 1 = false;
    std::uint32_t left_super_state_ : 1 = false;  // Also known as the "windows key"
    std::uint32_t right_super_state_ : 1 = false; // Also known as the "windows key"
    std::uint32_t caps_lock_state_ : 1 = false;
    std::uint32_t num_lock_state_ : 1 = false;
};

static_assert(sizeof(modifier_keys_state_data) <= sizeof(std::uint32_t));

} // namespace internal

class modifier_keys_state final
{
public:
    explicit modifier_keys_state(const internal::modifier_keys_state_data state) noexcept
        : state_{state}
    {
    }

    ~modifier_keys_state() = default;

    modifier_keys_state(const modifier_keys_state &) noexcept = delete;
    auto operator=(const modifier_keys_state &) noexcept -> modifier_keys_state & = delete;

    modifier_keys_state(modifier_keys_state &&) noexcept = delete;
    auto operator=(modifier_keys_state &&) noexcept -> modifier_keys_state & = delete;

    [[nodiscard]] auto left_shift_key_down() const noexcept
    {
        return state_.left_shift_state_;
    }

    [[nodiscard]] auto right_shift_key_down() const noexcept
    {
        return state_.right_shift_state_;
    }

    [[nodiscard]] auto left_ctrl_key_down() const noexcept
    {
        return state_.left_ctrl_state_;
    }

    [[nodiscard]] auto right_ctrl_key_down() const noexcept
    {
        return state_.right_ctrl_state_;
    }

    [[nodiscard]] auto left_alt_key_down() const noexcept
    {
        return state_.left_alt_state_;
    }

    [[nodiscard]] auto right_alt_key_down() const noexcept
    {
        return state_.right_alt_state_;
    }

    [[nodiscard]] auto left_super_key_down() const noexcept
    {
        return state_.left_super_state_;
    }

    [[nodiscard]] auto right_super_key_down() const noexcept
    {
        return state_.right_super_state_;
    }

    [[nodiscard]] auto left_windows_key_down() const noexcept
    {
        return left_super_key_down();
    }

    [[nodiscard]] auto right_windows_key_down() const noexcept
    {
        return right_super_key_down();
    }

    [[nodiscard]] auto caps_lock_enabled() const noexcept
    {
        return state_.caps_lock_state_;
    }

    [[nodiscard]] auto num_lock_enabled() const noexcept
    {
        return state_.num_lock_state_;
    }

    [[nodiscard]] auto any_shift_key_down() const noexcept
    {
        return state_.left_shift_state_ || state_.right_shift_state_;
    }

    [[nodiscard]] auto any_ctrl_key_down() const noexcept
    {
        return state_.left_ctrl_state_ || state_.right_ctrl_state_;
    }

    [[nodiscard]] auto any_alt_key_down() const noexcept
    {
        return state_.left_alt_state_ || state_.right_alt_state_;
    }

    [[nodiscard]] auto any_super_key_down() const noexcept
    {
        return state_.left_super_state_ || state_.right_super_state_;
    }

    [[nodiscard]] auto any_windows_key_down() const noexcept
    {
        return any_super_key_down();
    }

    [[nodiscard]] auto any_modifier_key_down() const noexcept
    {
        return state_.left_shift_state_ || state_.right_shift_state_ || state_.left_ctrl_state_ ||
               state_.right_ctrl_state_ || state_.left_alt_state_ || state_.right_alt_state_ ||
               state_.left_super_state_ || state_.right_super_state_;
    }

private:
    internal::modifier_keys_state_data state_;
};

} // namespace aeon::platform
