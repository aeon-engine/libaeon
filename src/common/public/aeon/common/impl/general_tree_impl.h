// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <stdexcept>

namespace aeon::common
{

template <typename T>
inline general_tree_iterator<T>::general_tree_iterator(std::vector<tree_leaf_data_type> *leafs, std::vector<T> *values,
                                                       const std::size_t current_index) noexcept
    : leafs_{leafs}
    , values_{values}
    , current_index_{current_index}
{
}

template <typename T>
inline auto general_tree_iterator<T>::operator++() -> general_tree_iterator<T> &
{
    const auto &leaf = (*leafs_)[current_index_];
    current_index_ = leaf.right;
    return *this;
}

template <typename T>
inline auto general_tree_iterator<T>::operator++(int) -> general_tree_iterator<T> &
{
    auto &val = *this;
    ++(*this);
    return val;
}

template <typename T>
inline auto general_tree_iterator<T>::operator==(const general_tree_iterator<T> &other) const -> bool
{
    return leafs_ == other.leafs_ && values_ == other.values_ && current_index_ == other.current_index_;
}

template <typename T>
inline auto general_tree_iterator<T>::operator!=(const general_tree_iterator<T> &other) const -> bool
{
    return !(*this == other);
}

template <typename T>
inline auto general_tree_iterator<T>::operator*() -> value_type
{
    return value_type{leafs_, values_, current_index_};
}

template <typename T>
inline auto general_tree_iterator<T>::operator*() const -> value_type
{
    return value_type{leafs_, values_, current_index_};
}

template <typename T>
inline void general_tree_leaf<T>::reserve(const std::size_t size) const
{
    leafs_->reserve(size);
    values_->reserve(size);
}

template <typename T>
inline auto general_tree_leaf<T>::emplace_child(const value_type &value) -> general_tree_leaf<value_type>
{
    const auto new_index = std::size(*leafs_);
    leafs_->push_back(tree_leaf_data_type{index_, tree_leaf_data_type::npos, tree_leaf_data_type::npos});
    values_->emplace_back(value);
    update_indices(new_index);
    return general_tree_leaf{leafs_, values_, new_index};
}

template <typename T>
inline auto general_tree_leaf<T>::emplace_child(value_type &&value) -> general_tree_leaf<value_type>
{
    const auto new_index = std::size(*leafs_);
    leafs_->push_back(tree_leaf_data_type{index_, tree_leaf_data_type::npos, tree_leaf_data_type::npos});
    values_->emplace_back(std::move(value));
    update_indices(new_index);
    return general_tree_leaf{leafs_, values_, new_index};
}

template <typename T>
inline void general_tree_leaf<T>::add_child(const value_type &value)
{
    emplace_child(value);
}

template <typename T>
inline void general_tree_leaf<T>::add_child(value_type &&value)
{
    emplace_child(std::move(value));
}

template <typename T>
inline auto general_tree_leaf<T>::parent() -> general_tree_leaf<value_type>
{
    const auto current_leaf = &leafs_->at(index_);

    if (current_leaf->parent == tree_leaf_data_type::npos)
        throw std::out_of_range{"Leaf has no parent."};

    return general_tree_leaf{leafs_, values_, current_leaf->parent};
}

template <typename T>
inline auto general_tree_leaf<T>::parent() const -> general_tree_leaf<value_type>
{
    const auto current_leaf = &leafs_->at(index_);

    if (current_leaf->parent == tree_leaf_data_type::npos)
        throw std::out_of_range{"Leaf has no parent."};

    return general_tree_leaf{leafs_, values_, current_leaf->parent};
}

template <typename T>
inline auto general_tree_leaf<T>::is_root() const noexcept -> bool
{
    const auto current_leaf = &leafs_->at(index_);
    return current_leaf->parent == tree_leaf_data_type::npos;
}

template <typename T>
inline auto general_tree_leaf<T>::at(const std::size_t i) -> general_tree_leaf<value_type>
{
    const auto current_leaf = &leafs_->at(index_);

    auto current = current_leaf->left;

    if (current == tree_leaf_data_type::npos)
        throw std::out_of_range{"Child index out of range"};

    for (auto count = 0u; count < i; ++count)
    {
        const auto &leaf = (*leafs_)[current];
        current = leaf.right;

        if (current == tree_leaf_data_type::npos)
            throw std::out_of_range{"Child index out of range"};
    }

    return general_tree_leaf{leafs_, values_, current};
}

template <typename T>
inline auto general_tree_leaf<T>::at(const std::size_t i) const -> general_tree_leaf<value_type>
{
    const auto current_leaf = &leafs_->at(index_);

    auto current = current_leaf->left;

    if (current == tree_leaf_data_type::npos)
        throw std::out_of_range{"Child index out of range"};

    for (auto count = 0u; count < i; ++count)
    {
        const auto &leaf = (*leafs_)[current];
        current = leaf.right;

        if (current == tree_leaf_data_type::npos)
            throw std::out_of_range{"Child index out of range"};
    }

    return general_tree_leaf{leafs_, values_, current};
}

template <typename T>
inline auto general_tree_leaf<T>::child_count() const noexcept -> std::size_t
{
    const auto current_leaf = &leafs_->at(index_);

    auto current = current_leaf->left;

    std::size_t count = 0;

    while (current != tree_leaf_data_type::npos)
    {
        const auto &leaf = (*leafs_)[current];
        current = leaf.right;
        ++count;
    }

    return count;
}

template <typename T>
inline auto general_tree_leaf<T>::begin() noexcept -> iterator_type
{
    const auto parent_leaf = &leafs_->at(index_);
    return iterator_type{leafs_, values_, parent_leaf->left};
}

template <typename T>
inline auto general_tree_leaf<T>::end() noexcept -> iterator_type
{
    return iterator_type{leafs_, values_, tree_leaf_data_type::npos};
}

template <typename T>
inline auto general_tree_leaf<T>::begin() const noexcept -> iterator_type
{
    return begin();
}

template <typename T>
inline auto general_tree_leaf<T>::end() const noexcept -> iterator_type
{
    return end();
}

template <typename T>
inline auto general_tree_leaf<T>::cbegin() const noexcept -> iterator_type
{
    return begin();
}

template <typename T>
inline auto general_tree_leaf<T>::cend() const noexcept -> iterator_type
{
    return end();
}

template <typename T>
inline auto general_tree_leaf<T>::operator*() noexcept -> reference
{
    return (*values_)[index_];
}

template <typename T>
inline auto general_tree_leaf<T>::operator*() const noexcept -> reference
{
    return (*values_)[index_];
}

template <typename T>
inline general_tree_leaf<T>::general_tree_leaf(std::vector<tree_leaf_data_type> *leafs, std::vector<value_type> *values,
                                               const std::size_t index) noexcept
    : leafs_{leafs}
    , values_{values}
    , index_{index}
{
}

template <typename T>
inline void general_tree_leaf<T>::update_indices(const std::size_t new_index) const noexcept
{
    auto leaf = &leafs_->at(index_);

    if (leaf->left == tree_leaf_data_type::npos)
    {
        leaf->left = new_index;
    }
    else
    {
        leaf = &leafs_->at(leaf->left);

        while (leaf->right != tree_leaf_data_type::npos)
            leaf = &leafs_->at(leaf->right);

        leaf->right = new_index;
    }
}

template <typename T>
inline general_tree<T>::general_tree(value_type &&root_value)
    : leafs_{}
    , values_{}
{
    leafs_.push_back(
        tree_leaf_data_type{tree_leaf_data_type::npos, tree_leaf_data_type::npos, tree_leaf_data_type::npos});
    values_.emplace_back(std::move(root_value));
}

template <typename T>
inline general_tree<T>::general_tree(const value_type &root_value)
    : leafs_{}
    , values_{}
{
    leafs_.push_back(
        tree_leaf_data_type{tree_leaf_data_type::npos, tree_leaf_data_type::npos, tree_leaf_data_type::npos});
    values_.emplace_back(root_value);
}

template <typename T>
inline void general_tree<T>::reserve(const std::size_t size)
{
    leafs_.reserve(size);
    values_.reserve(size);
}

template <typename T>
inline void general_tree<T>::clear() noexcept
{
    leafs_.clear();
    values_.clear();
}

template <typename T>
inline auto general_tree<T>::root() -> tree_leaf_type
{
    return tree_leaf_type{&leafs_, &values_, 0};
}

} // namespace aeon::common
