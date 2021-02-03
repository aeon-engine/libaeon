// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#ifndef aeon_concatenate
#define __aeon_concatenate_impl(s1, s2) s1##s2
#define aeon_concatenate(s1, s2) __aeon_concatenate_impl(s1, s2)
#endif

#ifndef aeon_anonymous_variable
#ifdef __COUNTER__
#define aeon_anonymous_variable(str) aeon_concatenate(str, __COUNTER__)
#else
#define aeon_anonymous_variable(str) aeon_concatenate(str, __LINE__)
#endif
#endif

#ifndef aeon_array_length
#define aeon_array_length(a) (sizeof(a) / sizeof(a[0]))
#endif

#ifndef aeon_string_encoding_none
#define aeon_string_encoding_none
#endif

#ifndef aeon_string_encoding_utf8
#define aeon_string_encoding_utf8 u8
#endif

#ifndef aeon_string_encoding_utf16
#define aeon_string_encoding_utf16 u
#endif

#ifndef aeon_string_encoding_utf32
#define aeon_string_encoding_utf32 U
#endif

#ifndef aeon_string_encoding_wide
#define aeon_string_encoding_wide L
#endif

#ifndef aeon_string_encoding
#define aeon_string_encoding aeon_string_encoding_utf8
#endif

#ifndef aeon_text
#define aeon_text(str) aeon_concatenate(aeon_string_encoding, str)
#endif

#ifndef aeon_single_arg
#define aeon_single_arg(...) __VA_ARGS__
#endif
