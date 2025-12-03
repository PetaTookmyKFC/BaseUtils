//
// Created by PetaTookmyKFC on 01/12/2025.
//

#ifndef BASEUTILS_SUFFIXFORMATTING_H
#define BASEUTILS_SUFFIXFORMATTING_H
#include "PrefixFormatting.h"

namespace base_utils::fmt {
    // Size of style and Text -- Required to be placed at compile time
    template<std::size_t sufSize, std::size_t stySize>
    struct SuffixedText {
        FixedString<stySize> style;
        FixedString<sufSize> suffix;
        std::string_view content;
        // Base Constructor
        constexpr SuffixedText(const FixedString<stySize>& style_code, FixedString<sufSize> sufix, std::string_view text)
            : style(style_code), suffix(sufix), content(text) {}
    };

    // Override the operator for pushing into the console
    template<std::size_t sufSize, std::size_t stySize>
    inline std::ostream& operator<<(std::ostream& os, const SuffixedText<sufSize, stySize> suffix) {
        // Set styling is enabled
        if constexpr (kColouredTerm) {
            os << suffix.style.c_str();
        }
        // Push content
        os << suffix.content;
        // Push Suffix at the end if formatting enabled
        if constexpr (kFormattedTerm) {
            os << suffix.suffix.c_str();
        }
        // Set reset code if coloured
        if constexpr (kColouredTerm) {
            os << RESET_CODE;
        }
        return os;
    }

    // Suffix Function (the one user calls to call all other templates)
    template<std::size_t stySize, std::size_t sufSize>
    struct SuffixFunction {
        FixedString<sufSize> suffix;
        FixedString<stySize> style_code;

        constexpr SuffixFunction(const FixedString<stySize>& styleCode, const FixedString<sufSize> suffix)
            :style_code(styleCode), suffix(suffix) {}

        constexpr auto operator() (std::string_view text) const {
            return SuffixedText<sufSize,stySize>(style_code, suffix, text);
        }

    };

    // Generate the Suffix Function for the user to call
    template<auto... Styles, std::size_t sufSize>
    constexpr auto ComSuffix(FixedString<sufSize> suffix) {
        return SuffixFunction(compose_impl<Styles...>(), suffix);
    }


}

#endif //BASEUTILS_SUFFIXFORMATTING_H