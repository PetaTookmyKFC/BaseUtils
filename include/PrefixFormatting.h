//
// Created by jacka on 26/11/2025.
//

#ifndef BASEUTILS_COLOUREDFORMATTING_FINAL_H
#define BASEUTILS_COLOUREDFORMATTING_FINAL_H

#include <cstdint>

#include "./ColouredFormatting.h"


// PrefixedText
namespace base_utils::fmt {
#ifdef NO_FORMAT
    inline constexpr bool kFormattedTerm = false;
#else
inline constexpr bool kFormattedTerm = true;
#endif

    template<std::size_t preSize, std::size_t stySize>
    struct PrefixedText {
        FixedString<stySize> style;
        FixedString<preSize> prefix;
        std::string_view content;

        constexpr PrefixedText(const FixedString<stySize>& style_code, FixedString<preSize> prefix, std::string_view text)
            :style(style_code), prefix(prefix), content(text) {}

    };

    template<std::size_t preSize, std::size_t stySize>
    inline std::ostream& operator<<(std::ostream& os, const PrefixedText<preSize, stySize>& prefix) {
        if constexpr (kColouredTerm) {
            os << prefix.style.c_str();
        }
        if constexpr (kFormattedTerm) {
            os << prefix.prefix.c_str();
        }
        os << prefix.content;
        if constexpr (kColouredTerm) {
            os << RESET_CODE;
        }
        return os;
    }



    template<std::size_t N, auto... Styles>
    struct CountString {
        static constexpr std::size_t value = (ComputeDigits<Styles...>::value + N);
    };

// PrefixFunction
    template<std::size_t preSize, std::size_t stySize>
    struct PrefixFunction {
        FixedString<stySize> style_code;
        FixedString<preSize> prefix;

        constexpr PrefixFunction(const FixedString<stySize>& styleCode, const FixedString<preSize> prefix) : style_code(styleCode), prefix(prefix) {}

        constexpr auto operator() (std::string_view text) const {
            return PrefixedText<preSize,stySize>(style_code, prefix, text);
        }
    };

    template<auto... Styles, std::size_t preSize>
    constexpr auto ComPrefix(FixedString<preSize> prefix) {
        return PrefixFunction(compose_impl<Styles...>(), prefix);
    }

    // inline constexpr auto MassiveSucc = ComPrefix<
    //         BG_BRIGHT_GREEN_CODE,
    //         FG_BLACK_CODE,
    //         UNDERLINE_CODE
    //     >(
    //         FixedString("Wow Much Changed!")
    //     );
    //

}





#endif //BASEUTILS_COLOUREDFORMATTING_FINAL_H