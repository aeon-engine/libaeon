// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/concepts.h>
#include <type_traits>
#include <memory>

namespace aeon::common
{

template <typename T>
concept intrusive_reference_countable = requires(T val)
{
    val.intrusive_ptr_add_ref();
    val.intrusive_ptr_release();
};

template <concepts::integral_or_atomic_integral T, typename derived_t,
          typename deleter_t = std::default_delete<derived_t>>
class intrusive_ref_counter
{
public:
    using ref_count_type = T;

    constexpr intrusive_ref_counter() noexcept
        : ref_count_{0}
    {
        static_assert(std::is_base_of_v<intrusive_ref_counter<T, derived_t, deleter_t>, derived_t>,
                      "derived_t must be the inherited class.");
    }

    constexpr intrusive_ref_counter(const intrusive_ref_counter<ref_count_type, derived_t, deleter_t> &) noexcept =
        default;
    constexpr auto operator=(const intrusive_ref_counter<ref_count_type, derived_t, deleter_t> &) noexcept
        -> intrusive_ref_counter<ref_count_type, derived_t, deleter_t> & = default;

    constexpr intrusive_ref_counter(intrusive_ref_counter<ref_count_type, derived_t, deleter_t> &&) noexcept = default;
    constexpr auto operator=(intrusive_ref_counter<ref_count_type, derived_t, deleter_t> &&) noexcept
        -> intrusive_ref_counter<ref_count_type, derived_t, deleter_t> & = default;

    constexpr void intrusive_ptr_add_ref() noexcept
    {
        ++ref_count_;
    }

    constexpr void intrusive_ptr_release() noexcept
    {
        --ref_count_;

        if (ref_count_ == 0)
            deleter_t{}(static_cast<derived_t *>(this));
    }

    [[nodiscard]] constexpr auto intrusive_ptr_ref_count() const noexcept -> const T &
    {
        return ref_count_;
    }

protected:
    ~intrusive_ref_counter() = default;

private:
    T ref_count_;
};

template <intrusive_reference_countable T>
class intrusive_ptr final
{
public:
    using element_type = std::remove_extent_t<T>;

    explicit intrusive_ptr() noexcept
        : ptr_{nullptr}
    {
    }

    intrusive_ptr(element_type *p)
        : ptr_{p}
    {
        if (ptr_ != nullptr)
            ptr_->intrusive_ptr_add_ref();
    }

    intrusive_ptr(std::unique_ptr<element_type> &&other)
        : ptr_{other.release()}
    {
        if (ptr_ != nullptr)
            ptr_->intrusive_ptr_add_ref();
    }

    intrusive_ptr(const intrusive_ptr<element_type> &other)
        : ptr_{other.ptr_}
    {
        if (ptr_ != nullptr)
            ptr_->intrusive_ptr_add_ref();
    }

    auto operator=(const intrusive_ptr<element_type> &other) -> intrusive_ptr<element_type> &
    {
        intrusive_ptr<element_type>{other}.swap(*this);
        return *this;
    }

    intrusive_ptr(intrusive_ptr<element_type> &&other) noexcept
        : ptr_{other.ptr_}
    {
        other.ptr_ = nullptr;
    }

    intrusive_ptr &operator=(intrusive_ptr<element_type> &&other) noexcept
    {
        intrusive_ptr<element_type>{other}.swap(*this);
        return *this;
    }

    template <typename U, std::enable_if_t<!std::is_convertible_v<element_type, U>> * = nullptr>
    intrusive_ptr(const intrusive_ptr<U> &other)
        : ptr_{other.ptr_}
    {
        if (ptr_ != nullptr)
            ptr_->intrusive_ptr_add_ref();
    }

    template <class U, std::enable_if_t<!std::is_convertible_v<element_type, U>> * = nullptr>
    auto operator=(const intrusive_ptr<U> &other) -> intrusive_ptr<element_type> &
    {
        intrusive_ptr<element_type>{other}.swap(*this);
        return *this;
    }

    auto operator=(element_type *other) -> intrusive_ptr<element_type> &
    {
        intrusive_ptr<element_type>{other}.swap(*this);
        return *this;
    }

    ~intrusive_ptr()
    {
        if (ptr_ != nullptr)
            ptr_->intrusive_ptr_release();
    }

    void reset()
    {
        intrusive_ptr<element_type>{}.swap(*this);
    }

    void reset(T *other)
    {
        intrusive_ptr<element_type>{other}.swap(*this);
    }

    [[nodiscard]] auto get() const noexcept
    {
        return ptr_;
    }

    auto release() noexcept
    {
        const auto ret = ptr_;
        ptr_ = nullptr;
        return ret;
    }

    [[nodiscard]] auto operator*() const noexcept -> element_type &
    {
        return *ptr_;
    }

    [[nodiscard]] auto operator->() const noexcept -> element_type *
    {
        return ptr_;
    }

    void swap(intrusive_ptr<element_type> &other) noexcept
    {
        auto *const temp = ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = temp;
    }

private:
    element_type *ptr_;
};

template <intrusive_reference_countable T, intrusive_reference_countable U>
inline auto operator==(const intrusive_ptr<T> &lhs, const intrusive_ptr<U> &rhs) noexcept
{
    return lhs.get() == rhs.get();
}

template <intrusive_reference_countable T, intrusive_reference_countable U>
inline bool operator!=(const intrusive_ptr<T> &lhs, const intrusive_ptr<U> &rhs) noexcept
{
    return !(lhs == rhs);
}

template <intrusive_reference_countable T, intrusive_reference_countable U>
inline bool operator==(const intrusive_ptr<T> &lhs, const U *rhs) noexcept
{
    return lhs.get() == rhs;
}

template <intrusive_reference_countable T, intrusive_reference_countable U>
inline bool operator!=(const intrusive_ptr<T> &lhs, const U *rhs) noexcept
{
    return !(lhs == rhs);
}

template <intrusive_reference_countable T, intrusive_reference_countable U>
inline bool operator==(const T *lhs, const intrusive_ptr<U> &rhs) noexcept
{
    return lhs == rhs.get();
}

template <intrusive_reference_countable T, intrusive_reference_countable U>
inline bool operator!=(const T *lhs, const intrusive_ptr<U> &rhs) noexcept
{
    return !(lhs == rhs);
}

template <intrusive_reference_countable T>
inline bool operator==(const intrusive_ptr<T> &lhs, const std::nullptr_t) noexcept
{
    return lhs.get() == nullptr;
}

template <intrusive_reference_countable T, intrusive_reference_countable U>
inline bool operator!=(const intrusive_ptr<T> &lhs, const std::nullptr_t) noexcept
{
    return !(lhs == nullptr);
}

template <intrusive_reference_countable T, typename... args_t>
[[nodiscard]] inline auto make_intrusive_ptr(args_t &&...args) -> intrusive_ptr<T>
{
    return intrusive_ptr<T>{std::make_unique<T>(std::forward<args_t>(args)...)};
}

} // namespace aeon::common
