//
// Created by jacka on 03/12/2025.
//

#ifndef BASEUTILS_ALL_H
#define BASEUTILS_ALL_H

#include "ColouredFormatting.h"
#include "FullFormatting.h"
#include "PrefixFormatting.h"
#include "SuffixFormatting.h"


namespace base_utils::fmt {
#ifdef NO_DEBUG
    inline constexpr bool kDebugTerm = false;
    template<typename Func>
    constexpr inline void Debug(Func&&) {}

#else
    inline constexpr bool kDebugTerm = true;
    // WOW ai be teaching my CPP --- this be crazy! COMPILE TIME - Only enable this function if the item is invocable (multiline)
    template <typename Func>
    constexpr inline typename std::enable_if<std::is_invocable<Func&&>::value>::type
    Debug(Func&& func) {
        std::forward<Func>(func)();
    }

    template <typename Expr>
    constexpr inline typename std::enable_if<!std::is_invocable<Expr&&>::value>::type
    Debug(Expr&& expr) {
        static_cast<void>(std::forward<Expr>(expr));
    }



#endif

}

#endif //BASEUTILS_ALL_H