#include <aeon/clang/visitor.h>

namespace aeon::clang
{

void clang_visit(const CXCursor cursor, std::function<void(const CXCursor, const CXCursor)> func)
{
    clang_visitChildren(
        cursor,
        [](const CXCursor c, const CXCursor parent, const CXClientData client_data) {
            const auto func = static_cast<std::function<void(const CXCursor, const CXCursor)> *>(client_data);
            (*func)(c, parent);
            return CXChildVisit_Continue;
        },
        &func);
}

} // namespace aeon::clang
