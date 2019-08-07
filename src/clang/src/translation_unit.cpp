#include <aeon/clang/translation_unit.h>
#include <stdexcept>

namespace aeon::clang
{

translation_unit::translation_unit(const std::filesystem::path &path, const std::vector<const char *> &args)
    : index_{}
    , translation_unit_{nullptr}
{
    const auto path_str = path.string();

    translation_unit_ =
        clang_parseTranslationUnit(index_.get(), path_str.c_str(), std::data(args), static_cast<int>(std::size(args)),
                                   nullptr, 0, CXTranslationUnit_KeepGoing);

    if (translation_unit_ == nullptr)
        throw std::runtime_error{{}};
}

translation_unit::~translation_unit()
{
    clang_disposeTranslationUnit(translation_unit_);
}

auto translation_unit::get_clang_translation_unit() const noexcept -> CXTranslationUnit
{
    return translation_unit_;
}

auto translation_unit::get_cursor() const noexcept -> CXCursor
{
    return clang_getTranslationUnitCursor(translation_unit_);
}

} // namespace aeon::clang
