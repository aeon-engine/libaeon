#include <aeon/clang/index.h>
#include <clang-c/Index.h>

namespace aeon::clang
{

clang_index::clang_index()
    : index_{clang_createIndex(0, 0)}
{
}

clang_index::~clang_index()
{
    clang_disposeIndex(index_);
}

auto clang_index::get() const noexcept -> CXIndex
{
    return index_;
}

} // namespace aeon::clang
