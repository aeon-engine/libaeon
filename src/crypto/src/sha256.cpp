// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/crypto/sha256.h>
#include <aeon/common/bits.h>
#include <aeon/common/literals.h>
#include <cstring>

namespace aeon::crypto
{

namespace internal
{

constexpr std::array<std::uint32_t, 8> initial_hash = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                                                       0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

constexpr std::array<std::uint32_t, 64> k = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

constexpr auto f1(const std::uint32_t value) noexcept -> std::uint32_t
{
    return common::bits::ror(value, 2) ^ common::bits::ror(value, 13) ^ common::bits::ror(value, 22);
}

constexpr auto f2(const std::uint32_t value) noexcept -> std::uint32_t
{
    return common::bits::ror(value, 6) ^ common::bits::ror(value, 11) ^ common::bits::ror(value, 25);
}

constexpr auto f3(const std::uint32_t value) noexcept -> std::uint32_t
{
    return common::bits::ror(value, 7) ^ common::bits::ror(value, 18) ^ value >> 3;
}

constexpr auto f4(const std::uint32_t value) noexcept -> std::uint32_t
{
    return common::bits::ror(value, 17) ^ common::bits::ror(value, 19) ^ value >> 10;
}

} // namespace internal

sha256::sha256() noexcept
    : hash_{internal::initial_hash}
    , block_{}
    , size_{0}
    , total_size_{0}
{
}

void sha256::write(const char *data, const std::streamsize size) noexcept
{
    const auto tmp_len = block_size - size_;
    auto rem_len = size < tmp_len ? size : tmp_len;

    memcpy(&block_[size_], data, rem_len);
    if (size_ + size < block_size)
    {
        size_ += size;
        return;
    }

    const auto new_len = size - rem_len;
    const auto block_nb = new_len / block_size;
    const auto shifted_message = reinterpret_cast<const unsigned char *>(data) + rem_len;

    transform(std::data(block_), 1);
    transform(shifted_message, block_nb);
    rem_len = new_len % block_size;
    memcpy(std::data(block_), &shifted_message[block_nb << 6], rem_len);
    size_ = rem_len;
    total_size_ += (block_nb + 1) << 6;
}

void sha256::write(const std::string_view str) noexcept
{
    write(std::data(str), static_cast<std::streamsize>(std::size(str)));
}

auto sha256::finalize() noexcept -> sha256_hash
{
    const auto block_nb = (1 + ((block_size - 9) < (size_ % block_size)));
    const auto len_b = (total_size_ + size_) << 3;
    const auto pm_len = block_nb << 6;
    memset(std::data(block_) + size_, 0, pm_len - size_);
    block_.at(size_) = 0x80;
    common::bits::unpack32(static_cast<std::uint32_t>(len_b), std::data(block_) + pm_len - 4);
    transform(std::data(block_), block_nb);

    sha256_hash digest;
    for (auto i = 0; i < 8; i++)
    {
        common::bits::unpack32(hash_[i], &digest[i << 2]);
    }

    return digest;
}

void sha256::reset() noexcept
{
    hash_ = internal::initial_hash;
    std::fill(std::begin(block_), std::end(block_), 0_uint8_t);
    size_ = 0;
    total_size_ = 0;
}

void sha256::transform(const unsigned char *message, const std::streamsize size) noexcept
{
    std::array<std::uint32_t, 64> w;

    for (auto i = 0u; i < size; i++)
    {
        const auto sub_block = message + (static_cast<std::ptrdiff_t>(i) << 6);

        for (auto j = 0; j < 16; j++)
        {
            w[j] = common::bits::pack32(&sub_block[j << 2]);
        }

        for (auto j = 16; j < 64; j++)
        {
            w[j] = internal::f4(w[j - 2]) + w[j - 7] + internal::f3(w[j - 15]) + w[j - 16];
        }

        auto wv = hash_;

        for (auto j = 0; j < 64; j++)
        {
            const auto t1 = wv[7] + internal::f2(wv[4]) + ((wv[4] & wv[5]) ^ (~wv[4] & wv[6])) + internal::k[j] + w[j];
            const auto t2 = internal::f1(wv[0]) + ((wv[0] & wv[1]) ^ (wv[0] & wv[2]) ^ (wv[1] & wv[2]));
            wv[7] = wv[6];
            wv[6] = wv[5];
            wv[5] = wv[4];
            wv[4] = wv[3] + t1;
            wv[3] = wv[2];
            wv[2] = wv[1];
            wv[1] = wv[0];
            wv[0] = t1 + t2;
        }

        for (auto j = 0; j < 8; j++)
        {
            hash_[j] += wv[j];
        }
    }
}

} // namespace aeon::crypto
