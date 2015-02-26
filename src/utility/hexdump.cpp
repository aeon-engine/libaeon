#include <aeon/utility.h>

namespace aeon
{
namespace utility
{

void hexdump(FILE *dest, const void *src, std::size_t len)
{
    fputs("--------|------------------------------------------------|----------------|\n", dest);
    fputs(" offset |00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |0123456789ABCDEF|\n", dest);
    fputs("--------|------------------------------------------------|----------------|\n", dest);

    std::size_t i = 0;
    std::size_t c = 0;
    std::size_t start;
    std::size_t written;
    std::uint8_t byte;
    const unsigned char *pData = (const unsigned char *)src;

    for (; i < len;)
    {
        start = i;
        fprintf(dest, "%08X|", (unsigned int) i);
        for (c = 0; c < 16 && i < len;) // write 16 bytes per line
        {
            fprintf(dest, "%02X ", (int)pData[i]);
            ++i; ++c;
        }

        written = c;
        for (; c < 16; ++c)	// finish off any incomplete bytes
            fputs("   ", dest);

        // write the text part
        fputc('|', dest);
        for (c = 0; c < written; ++c)
        {
            byte = pData[start + c];
            if (isprint((int)byte))
                fputc((char)byte, dest);
            else
                fputc('.', dest);
        }

        for (; c < 16; ++c)
            fputc(' ', dest);

        fputs("|\n", dest);
    }

    fputs("---------------------------------------------------------------------------\n", dest);
}

} // namespace utility
} // namespace aeon
