/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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
    const unsigned char *pData = reinterpret_cast<const unsigned char *>(src);

    for (; i < len;)
    {
        std::size_t start = i;
        fprintf(dest, "%08X|", static_cast<unsigned int>(i));
        for (c = 0; c < 16 && i < len;) // write 16 bytes per line
        {
            fprintf(dest, "%02X ", static_cast<int>(pData[i]));
            ++i;
            ++c;
        }

        std::size_t written = c;
        for (; c < 16; ++c) // finish off any incomplete bytes
            fputs("   ", dest);

        // write the text part
        fputc('|', dest);
        for (c = 0; c < written; ++c)
        {
            std::uint8_t byte = pData[start + c];
            if (isprint(static_cast<int>(byte)))
                fputc(static_cast<char>(byte), dest);
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
