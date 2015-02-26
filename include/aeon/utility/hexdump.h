#ifndef aeon_utility_hexdump_h__
#define aeon_utility_hexdump_h__

namespace aeon
{
namespace utility
{

void hexdump(FILE *dest, const void *src, size_t len);

} // namespace utility
} // namespace aeon

#endif // aeon_utility_hexdump_h__
