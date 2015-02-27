#ifndef endianness_h__
#define endianness_h__

namespace aeon
{
namespace utility
{
namespace endianness
{

template<typename T>
T swap16(T val)
{
    static_assert(sizeof(T) == sizeof(std::uint16_t),
        "swap16 used on type of different size.");

    typedef std::conditional<std::is_integral<T>::value,
        T, std::uint16_t>::type swap_type;

    swap_type swap =
        (((*((swap_type*)&val) & 0x00FF) << 8) |
        ((*((swap_type*)&val) & 0xFF00) >> 8));

    return *((T *)&swap);
}

template<typename T>
T swap32(T val)
{
    static_assert(sizeof(T) == sizeof(std::uint32_t),
        "swap32 used on type of different size.");

    typedef std::conditional<std::is_integral<T>::value,
        T, std::uint32_t>::type swap_type;

    swap_type swap =
        (((*((swap_type*)&val) & 0x000000FF) << 24) |
        ((*((swap_type*)&val) & 0x0000FF00) << 8) |
        ((*((swap_type*)&val) & 0x00FF0000) >> 8) |
        ((*((swap_type*)&val) & 0xFF000000) >> 24));

    return *((T *)&swap);
}

template<typename T>
T swap64(T val)
{
    static_assert(sizeof(T) == sizeof(std::uint64_t),
        "swap64 used on type of different size.");

    typedef std::conditional<std::is_integral<T>::value,
        T, std::uint64_t>::type swap_type;

    swap_type swap =
        (((*((swap_type*)&val) & 0x00000000000000FFULL) << 56) |
        ((*((swap_type*)&val) & 0x000000000000FF00ULL) << 40) |
        ((*((swap_type*)&val) & 0x0000000000FF0000ULL) << 24) |
        ((*((swap_type*)&val) & 0x00000000FF000000ULL) << 8) |
        ((*((swap_type*)&val) & 0x000000FF00000000ULL) >> 8) |
        ((*((swap_type*)&val) & 0x0000FF0000000000ULL) >> 24) |
        ((*((swap_type*)&val) & 0x00FF000000000000ULL) >> 40) |
        ((*((swap_type*)&val) & 0xFF00000000000000ULL) >> 56));

    return *((T *) &swap);

}

} // namespace endianness
} // namespace utility
} // namespace aeon

#endif // endianness_h__
