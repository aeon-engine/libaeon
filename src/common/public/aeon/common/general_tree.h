// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <type_traits>
#include <limits>
#include <vector>

#include <forward_list>

namespace aeon::common
{

namespace internal
{

struct general_tree_leaf_data
{
    static constexpr auto npos = std::numeric_limits<std::size_t>::max();

    std::size_t parent = npos;
    std::size_t left = npos;
    std::size_t right = npos;
};

} // namespace internal

template <typename T>
class general_tree_leaf;

template <typename T>
class general_tree_iterator
{
    using tree_leaf_data_type = internal::general_tree_leaf_data;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = general_tree_leaf<T>;
    using difference_type = std::size_t;
    using pointer = value_type *;
    using reference = value_type &;

    explicit general_tree_iterator(std::vector<tree_leaf_data_type> *leafs, std::vector<T> *values,
                                   const std::size_t current_index) noexcept;

    auto operator++() -> general_tree_iterator<T> &;

    auto operator++(int) -> general_tree_iterator<T> &;

    [[nodiscard]] auto operator==(const general_tree_iterator<T> &other) const -> bool;

    [[nodiscard]] auto operator!=(const general_tree_iterator<T> &other) const -> bool;

    auto operator*() -> value_type;

    auto operator*() const -> value_type;

private:
    std::vector<tree_leaf_data_type> *leafs_;
    std::vector<T> *values_;
    std::size_t current_index_;
};

template <typename T>
class general_tree_leaf final
{
    template <typename>
    friend class general_tree;

    template <typename>
    friend class general_tree_iterator;

    using tree_leaf_data_type = internal::general_tree_leaf_data;

public:
    using value_type = T;
    using pointer = value_type *;
    using reference = value_type &;
    using iterator_type = general_tree_iterator<value_type>;

    general_tree_leaf(const general_tree_leaf<value_type> &) = delete;
    auto operator=(const general_tree_leaf<value_type> &) -> general_tree_leaf<value_type> & = delete;

    general_tree_leaf(general_tree_leaf<value_type> &&) noexcept = delete;
    auto operator=(general_tree_leaf<value_type> &&) noexcept -> general_tree_leaf<value_type> & = delete;

    void reserve(const std::size_t size) const;

    auto emplace_child(const value_type &value) -> general_tree_leaf<value_type>;

    auto emplace_child(value_type &&value) -> general_tree_leaf<value_type>;

    void add_child(const value_type &value);

    void add_child(value_type &&value);

    [[nodiscard]] auto parent() -> general_tree_leaf<value_type>;

    [[nodiscard]] auto parent() const -> general_tree_leaf<value_type>;

    [[nodiscard]] auto is_root() const noexcept -> bool;

    [[nodiscard]] auto at(const std::size_t i) -> general_tree_leaf<value_type>;

    [[nodiscard]] auto at(const std::size_t i) const -> general_tree_leaf<value_type>;

    [[nodiscard]] auto child_count() const noexcept -> std::size_t;

    [[nodiscard]] auto begin() noexcept -> iterator_type;

    [[nodiscard]] auto end() noexcept -> iterator_type;

    [[nodiscard]] auto begin() const noexcept -> iterator_type;

    [[nodiscard]] auto end() const noexcept -> iterator_type;

    [[nodiscard]] auto cbegin() const noexcept -> iterator_type;

    [[nodiscard]] auto cend() const noexcept -> iterator_type;

    [[nodiscard]] auto operator*() noexcept -> reference;

    [[nodiscard]] auto operator*() const noexcept -> reference;

private:
    explicit general_tree_leaf(std::vector<tree_leaf_data_type> *leafs, std::vector<value_type> *values,
                               const std::size_t index) noexcept;

    void update_indices(const std::size_t new_index) const noexcept;

    std::vector<tree_leaf_data_type> *leafs_;
    std::vector<value_type> *values_;
    std::size_t index_;
};

/*!
 * A general tree implemented as left-child right-sibling (LCRS).
 */
template <typename T>
class general_tree final
{
    using tree_leaf_data_type = internal::general_tree_leaf_data;

public:
    using value_type = T;
    using tree_leaf_type = general_tree_leaf<value_type>;

    explicit general_tree(value_type &&root_value);

    explicit general_tree(const value_type &root_value);

    ~general_tree() = default;

    general_tree(const general_tree &) = default;
    auto operator=(const general_tree &) -> general_tree & = default;

    general_tree(general_tree &&) noexcept = default;
    auto operator=(general_tree &&) noexcept -> general_tree & = default;

    void reserve(const std::size_t size);

    void clear() noexcept;

    [[nodiscard]] auto root() -> tree_leaf_type;

private:
    std::vector<tree_leaf_data_type> leafs_;
    std::vector<value_type> values_;
};

} // namespace aeon::common

#include <aeon/common/impl/general_tree_impl.h>
