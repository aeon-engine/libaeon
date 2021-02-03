// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <cstddef>
#include <memory>
#include <vector>

namespace aeon::common
{

template <typename T>
class shared_vector final
{
public:
    using value_type = typename std::vector<T>::value_type;
    using allocator_type = typename std::vector<T>::allocator_type;
    using size_type = typename std::vector<value_type>::size_type;
    using difference_type = typename std::vector<value_type>::difference_type;
    using reference = typename std::vector<value_type>::reference;
    using const_reference = typename std::vector<value_type>::const_reference;
    using pointer = typename std::vector<value_type>::pointer;
    using const_pointer = typename std::vector<value_type>::const_pointer;
    using iterator = typename std::vector<value_type>::iterator;
    using const_iterator = typename std::vector<value_type>::const_iterator;
    using reverse_iterator = typename std::vector<value_type>::reverse_iterator;
    using const_reverse_iterator = typename std::vector<value_type>::const_reverse_iterator;

    explicit shared_vector()
        : data_{std::make_shared<std::vector<value_type>>()}
    {
    }

    explicit shared_vector(const std::size_t size)
        : data_{std::make_shared<std::vector<value_type>>(size)}
    {
    }

    explicit shared_vector(const std::size_t size, const value_type value)
        : data_{std::make_shared<std::vector<value_type>>(size, value)}
    {
    }

    explicit shared_vector(std::initializer_list<value_type> init)
        : data_{std::make_shared<std::vector<value_type>>(init)}
    {
    }

    ~shared_vector() = default;

    shared_vector(const shared_vector<T> &) = default;
    auto operator=(const shared_vector<T> &) -> shared_vector<T> & = default;

    shared_vector(shared_vector<T> &&) noexcept = default;
    auto operator=(shared_vector<T> &&) noexcept -> shared_vector<T> & = default;

    explicit shared_vector(std::vector<value_type> &&other) noexcept
        : data_{std::make_shared<std::vector<value_type>>(std::move(other))}
    {
    }

    auto operator=(std::vector<value_type> &&other) noexcept -> shared_vector<value_type> &
    {
        *data_ = std::move(other);
        return *this;
    }

    auto operator=(std::initializer_list<T> other) noexcept -> shared_vector<value_type> &
    {
        *data_ = other;
        return *this;
    }

    void assign(const size_type count, const value_type &value)
    {
        data_->assign(count, value);
    }

    template <typename itr>
    void assign(itr first, itr second)
    {
        data_->assign(first, second);
    }

    void assign(std::initializer_list<T> other)
    {
        data_->assign(other);
    }

    auto at(const size_type pos) -> reference
    {
        return data_->at(pos);
    }

    auto at(const size_type pos) const -> const_reference
    {
        return data_->at(pos);
    }

    auto operator[](const size_type pos) -> reference
    {
        return (*data_)[pos];
    }

    auto operator[](const size_type pos) const -> const_reference
    {
        return (*data_)[pos];
    }

    auto front() -> reference
    {
        return data_->front();
    }

    auto front() const -> const_reference
    {
        return data_->front();
    }

    auto back() -> reference
    {
        return data_->back();
    }

    auto back() const -> const_reference
    {
        return data_->back();
    }

    auto begin() noexcept -> iterator
    {
        return data_->begin();
    }

    auto begin() const noexcept -> const_iterator
    {
        return data_->begin();
    }

    auto cbegin() const noexcept -> const_iterator
    {
        return data_->begin();
    }

    auto end() noexcept -> iterator
    {
        return data_->end();
    }

    auto end() const noexcept -> const_iterator
    {
        return data_->end();
    }

    auto cend() const noexcept -> const_iterator
    {
        return data_->cend();
    }

    auto rbegin() noexcept -> iterator
    {
        return data_->rbegin();
    }

    auto rbegin() const noexcept -> const_iterator
    {
        return data_->rbegin();
    }

    auto crbegin() const noexcept -> const_iterator
    {
        return data_->rbegin();
    }

    auto rend() noexcept -> iterator
    {
        return data_->rend();
    }

    auto rend() const noexcept -> const_iterator
    {
        return data_->rend();
    }

    auto crend() const noexcept -> const_iterator
    {
        return data_->crend();
    }

    [[nodiscard]] auto empty() const noexcept
    {
        return data_->empty();
    }

    [[nodiscard]] auto size() const noexcept
    {
        return std::size(*data_);
    }

    [[nodiscard]] auto max_size() const noexcept
    {
        return data_->max_size();
    }

    void reserve(const size_type new_cap)
    {
        data_->reserve(new_cap);
    }

    void resize(const std::size_t size) const
    {
        data_->resize(size);
    }

    auto capacity() const noexcept
    {
        return data_->capacity();
    }

    void shrink_to_fit()
    {
        data_->shrink_to_fit();
    }

    auto insert(const_iterator pos, const value_type &value) -> iterator
    {
        return data_->insert(pos, value);
    }

    auto insert(const_iterator pos, value_type &&value) -> iterator
    {
        return data_->insert(pos, std::forward<value_type>(value));
    }

    auto insert(const_iterator pos, const size_type count, const value_type &value) -> iterator
    {
        return data_->insert(pos, count, value);
    }

    template <class itr>
    auto insert(const_iterator pos, itr first, itr last) -> iterator
    {
        return data_->insert(pos, first, last);
    }

    auto insert(const_iterator pos, std::initializer_list<value_type> ilist) -> iterator
    {
        return data_->insert(pos, ilist);
    }

    template <class... Args>
    auto emplace(const_iterator pos, Args &&...args) -> iterator
    {
        return data_->emplace(pos, std::forward<Args>(args)...);
    }

    auto erase(const_iterator pos) -> iterator
    {
        return data_->erase(pos);
    }

    auto erase(const_iterator first, const_iterator last) -> iterator
    {
        return data_->erase(first, last);
    }

    void push_back(const T &value)
    {
        data_->push_back(value);
    }

    void push_back(T &&value)
    {
        data_->push_back(std::move(value));
    }

    template <class... Args>
    auto emplace_back(Args &&...args) -> reference
    {
        return data_->emplace_back(std::forward<Args>(args)...);
    }

    void pop_back()
    {
        data_->pop_back();
    }

    void clear() const noexcept
    {
        data_->clear();
    }

    [[nodiscard]] auto data() noexcept
    {
        return std::data(*data_);
    }

    [[nodiscard]] auto data() const noexcept
    {
        return std::data(*data_);
    }

    void swap(std::vector<value_type> &other) noexcept(
        std::allocator_traits<allocator_type>::propagate_on_container_swap::value)
    {
        std::swap(*data_, other);
    }

private:
    // Replace implementation once https://github.com/microsoft/STL/commit/a099e85ce37b2bf1a680506ee44489e24c5cb05b
    // is integrated in Visual Studio. This should save 1 allocation for each resource_data object
    // std::shared_ptr<std::byte[]> data_;

    std::shared_ptr<std::vector<value_type>> data_;
};

} // namespace aeon::common
