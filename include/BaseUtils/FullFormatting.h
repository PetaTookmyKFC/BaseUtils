//
// Created by jacka on 01/12/2025.
//

#ifndef FORMATTING_FULLFORMATTING_H
#define FORMATTING_FULLFORMATTING_H

#include "PrefixFormatting.h"

namespace base_utils::fmt {

    template<std::size_t preSize, size_t sufSize, std::size_t stySize>
    struct FormattedText {
        FixedString<stySize> style;
        FixedString<preSize> prefix;
        FixedString<sufSize> suffix;
        std::string_view content;

        constexpr FormattedText(const FixedString<stySize>& style_code, FixedString<preSize> prefix, FixedString<sufSize> suf, std::string_view text)
            : style(style_code), prefix(prefix), suffix(suf) , content(text) {}
    };

    template<std::size_t preSize, std::size_t sufSize, std::size_t stySize>
    inline std::ostream& operator<<(std::ostream& os, const FormattedText<preSize, sufSize, stySize>& formatted) {
        if constexpr (kColouredTerm) {
            os << formatted.style.c_str();
        }
        if constexpr (kFormattedTerm) {
            os << formatted.prefix.c_str();
        }

        os << formatted.content;

        if constexpr (kFormattedTerm) {
            os << formatted.suffix.c_str();
        }
        if constexpr (kColouredTerm) {
            os << RESET_CODE;
        }
        return os;
    }

    template<std::size_t preSize, std::size_t sufSize, std::size_t stySize>
    struct FormattedFunction {
        FixedString<stySize> style_code;
        FixedString<preSize> prefix;
        FixedString<sufSize> suffix;

        constexpr FormattedFunction(
            const FixedString<stySize> styleCode,
            const FixedString<preSize> prefix,
            const FixedString<sufSize> suffix
        ) : style_code(styleCode), prefix(prefix), suffix(suffix) {}

        constexpr auto operator() (std::string_view text) const {
            return FormattedText<preSize, sufSize, stySize>(style_code, prefix, suffix, text);
        }

    };

    template <auto... Styles, std::size_t preSize, std::size_t sufSize>
    constexpr auto ComFormatted(FixedString<preSize> prefix,  FixedString<sufSize> suffix) {
        return FormattedFunction(compose_impl<Styles...>(), prefix, suffix);
    }


}

#endif //FORMATTING_FULLFORMATTING_H