// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <string_view>
#include <regex>

namespace aeon::rdp
{

class cursor;

template <typename T>
class parse_result;

/*!
 * Recursive-Descent-Parsing (RDP).
 * This class contains helper methods (matches and skippers) to aid with implementing RDP.
 * The internal iterator is only moved when a match or check succeeds.
 *
 * Function and method naming scheme:
 * check_* - Check if a certain character is matched. Returns true or false.
 * match_* - Match 1 or more characters. Returns a parse_result with the result
 * skip_*  - Skip a certain character or characters.
 * parse_* - The same as match, however the result is parsed into a pod type (for example parse_hex
 *           would parse to an integer)
 */
class parser
{
    friend class scoped_state;

public:
    explicit parser(const std::string_view v);
    explicit parser(const std::string_view v, const std::string_view filename);

    template <typename iterator_t>
    explicit parser(iterator_t begin, iterator_t end);

    ~parser() = default;

    parser(const parser &) noexcept = default;
    auto operator=(const parser &) noexcept -> parser & = default;

    parser(parser &&) noexcept = default;
    auto operator=(parser &&) noexcept -> parser & = default;

    /*!
     * Check if the index is at the end of the given string ("end of file").
     * \return True on eof
     */
    [[nodiscard]] auto eof() const noexcept -> bool;

    /*!
     * Check if the index is at the beginning of the given string ("beginning of file").
     * \return True on bof
     */
    [[nodiscard]] auto bof() const noexcept -> bool;

    /*!
     * Advance to the next character
     * \return True if possible, false on eof
     */
    auto advance() noexcept -> bool;

    /*!
     * Advance a certain amount of characters
     * \return True if possible, false on eof
     */
    auto advance(const std::size_t count) noexcept -> bool;

    /*!
     * Reverse to the previous character
     * \return True if possible, false if the beginning is reached
     */
    auto reverse() noexcept -> bool;

    /*!
     * Get the character at the current position. Calling this when eof() is true results in undefined behavior.
     * \return Returns the current character.
     */
    auto current() const noexcept -> char;

    /*!
     * Get the character at the current position. Calling this when eof() is true results in undefined behavior.
     * \return Returns the current character.
     */
    auto operator*() const noexcept -> char;

    /*!
     * Get the current parse offset index.
     * \return The current parse offset index.
     */
    auto offset() const noexcept -> std::size_t;

    /*!
     * Get the cursor information of the current offset. The cursor contains the current line, the line number and
     * column. This class can help in forming user-friendly error messages. \return A cursor class containing
     * information of the current offset.
     */
    auto cursor() const noexcept -> rdp::cursor;

    /*!
     * Get the filename of the current object being parsed (if set during construction).
     * This can help in forming user-friendly error messages.
     * \return A filename, if set.
     */
    auto filename() const noexcept -> std::string_view;

    /*!
     * Get a range of characters based on given indices.
     * \return The string in the given range indices of characters. Returns error if the indices are out of range.
     */
    auto get_range(const std::size_t begin, const std::size_t end) const noexcept -> parse_result<std::string_view>;

    /*!
     * Check if a certain character is at the current position. Moves the internal index 1 if matched.
     * \return True if character is at current position
     */
    auto check(const char c) noexcept -> bool;

    /*!
     * Check if a certain string is at the current position. Moves the internal index by the length
     * of the given string if matched.
     * \return True if character is at current position
     */
    auto check(const std::string_view str) noexcept -> bool;

    /*!
     * Skip all occurrences of a certain character and move the internal index to the first character
     * that does not match the given one.
     */
    void skip(const char c) noexcept;

    /*!
     * Skip all characters that are not the given character and move the internal index to right after the first
     * character that matches the given one.
     */
    void skip_until(const char c) noexcept;

    /*!
     * Match with a matcher.
     *
     * The matcher's signature is: auto pred(const char c) noexcept -> bool
     */
    template <typename matcher_t>
    auto match(matcher_t pred) noexcept -> parse_result<std::string_view>;

    /*!
     * Match with a matcher. The second argument given to the predicate is the index of the matched character.
     * This allows for example for matching on C/C++ variable names that can't start with a number or certain
     * characters.
     *
     * The matcher's signature is: auto pred(const char c, const std::size_t index) noexcept -> bool
     */
    template <typename matcher_t>
    auto match_indexed(matcher_t pred) noexcept -> parse_result<std::string_view>;

    /*!
     * Match with regular expressions. The expression is only matched when it starts at the current index.
     * Note that while using a Kleene star, empty sequences are not matched and will return unmatched.
     *
     * Examples:
     * "[a-zA-Z]+"
     * "[0-9]+"
     */
    auto match_regex(const std::string_view regex,
                     std::basic_regex<char>::flag_type flags = std::regex_constants::ECMAScript)
        -> parse_result<std::string_view>;

    /*!
     * Match any character until the given character. The result will not contain the given end character.
     * If eof is reached before the given character is found, unmatched will be returned.
     */
    auto match_until(const char c) noexcept -> parse_result<std::string_view>;

    /*!
     * Match any character until the given string. The result will not contain the given end string.
     * If eof is reached before the given string is found, unmatched will be returned.
     */
    auto match_until(const std::string_view str) noexcept -> parse_result<std::string_view>;

private:
    std::string_view view_;
    std::string_view::const_iterator current_;
    std::string_view filename_;
};

auto eof(const parser &parser) noexcept -> bool;
auto bof(const parser &parser) noexcept -> bool;
auto current(const parser &parser) noexcept -> char;
auto offset(const parser &parser) noexcept -> std::size_t;
auto filename(const parser &parser) noexcept -> std::string_view;

} // namespace aeon::rdp

#include <aeon/rdp/impl/parser_impl.h>
