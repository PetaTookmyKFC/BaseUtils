//
// Created by PetaTookmyKFC on 22/10/2025.
//

#ifndef BASEUTILS_FORMATTING_REFACTOR_H
#define BASEUTILS_FORMATTING_REFACTOR_H

#define COLOURED_TERM true
#include <format>
#include <string_view>
#include <utility>

namespace base_utils::fmt {
#ifdef COLOURED_TERM
    inline constexpr bool kColouredTerm = true;
#else
    inline constexpr bool kColouredTerm = false;
#endif

#ifdef FORMATTED_TERM
    inline constexpr bool kFormattedTerm = true;
#else
    inline constexpr bool kFormattedTerm = false;
#endif

template<typename F>
void Log (bool cond, F&& code) {
    if (cond) {
        std::forward<F>(code);
    }
}

inline constexpr bool DEBUG = true;

template <typename F>
void Debug(F&& code ) {
    if (DEBUG) {
        std::forward<F>(code);
    }
}

template <std::size_t N>
using StyleMarker = std::string_view;

inline constexpr StyleMarker<7> RED = "\033[1;31m";
inline constexpr StyleMarker<7> GREEN = "\033[1;32m";
inline constexpr StyleMarker<7> YELLOW = "\033[1;33m";
inline constexpr StyleMarker<4> RESET = "\033[0m";

inline constexpr StyleMarker<4> BOLD          = "\033[1m";  // Bold only
inline constexpr StyleMarker<5> STRIKETHROUGH = "\033[9m";  // Strikethrough only

// For dynamic style code generation



template <std::size_t N>
struct StyledText {
    StyleMarker<N> style;
    std::string_view coloured_text;
};
template <std::size_t N>
inline std::ostream& operator<<(std::ostream& os, const StyledText<N> & str) {
    if constexpr (kColouredTerm) {
        os << str.style << str.coloured_text << RESET;
    } else {
        os << str.coloured_text;
    }
    return os;
}

inline StyledText<7> c_red (const std::string_view str) {
    return StyledText<7>{RED, str};
}
inline StyledText<7> c_green (const std::string_view str) {
    return StyledText<7>{GREEN, str};
}
inline StyledText<7> c_yellow (const std::string_view str) {
    return StyledText<7>{YELLOW, str};
}

inline StyledText<5> c_strikethrough (const std::string_view str) {
    return StyledText<5>{STRIKETHROUGH, str};
}

template <std::size_t... Codes>
inline constexpr StyleMarker<(4 + sizeof...(Codes) + (sizeof...(Codes) -1))>
    make_style(std::index_sequence<Codes...>) {

    return std::vformat("\033[{};{}m", std::make_format_args(Codes...));
}



}

#endif //BASEUTILS_FORMATTING_REFACTOR_H