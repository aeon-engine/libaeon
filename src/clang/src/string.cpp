#include <aeon/clang/string.h>
#include <aeon/common/compilers.h>
#include <clang-c/Index.h>

namespace aeon::clang
{
scoped_cxstring::scoped_cxstring(const CXString str) noexcept
    : str_{str}
{
}

scoped_cxstring::~scoped_cxstring()
{
    dispose();
}

scoped_cxstring::scoped_cxstring(scoped_cxstring &&other) noexcept
    : str_{other.str_}
{
    other.str_.data = nullptr;
}

auto scoped_cxstring::operator=(scoped_cxstring &&other) noexcept -> scoped_cxstring &
{
    if (AEON_LIKELY(this != &other))
    {
        dispose();
        str_ = other.str_;
        other.str_.data = nullptr;
    }

    return *this;
}

auto scoped_cxstring::to_std_string() const -> std::string
{
    return clang_getCString(str_);
}

void scoped_cxstring::dispose() noexcept
{
    if (str_.data)
        clang_disposeString(str_);

    str_.data = nullptr;
}

} // namespace aeon::clang
