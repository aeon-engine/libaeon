/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

namespace aeon
{
namespace utility
{
namespace container
{

template <typename T>
std::vector<T *> unique_ptr_to_raw_ptr(const std::vector<std::unique_ptr<T>> &c)
{
    std::vector<T *> c_ptr(c.size());

    for (auto &i : c)
    {
        c_ptr.push_back(i.get());
    }

    return std::move(c_ptr);
}

template<typename container_t, typename predicate_t>
void erase_if(container_t &items, const predicate_t &predicate)
{
    for (auto itr = items.begin(); itr != items.end(); )
    {
        if (predicate(*itr))
            itr = items.erase(itr);
        else
            ++itr;
    }
}

} // namespace container
} // namespace utility
} // namespace aeon
