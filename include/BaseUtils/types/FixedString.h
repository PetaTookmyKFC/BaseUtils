//
// Created by PetaTookmyKFC on 11/02/2026.
//

#ifndef BASEUTILS_FIXEDSTRING_H
#define BASEUTILS_FIXEDSTRING_H

namespace base_utils::types
{
#ifdef NO_COLOUR
    inline constexpr bool kColouredTerm = false;
# else
    inline constexpr bool kColouredTerm = true;
#endif

    // For Compile time decleration (Set the string size at compile time without
    // the need for runtime variable or any memory allocation
    template<std::size_t N>
    struct FixedString {
        char data[N + 1]{};

        // Copy the data into the fixed string
        // NOLINTNEXTLINE(google-explicit-constructor, hicpp-explicit-conversions)
        constexpr FixedString(const char (&str)[N+1]) {
            for (std::size_t i =0; i < N; i++) {
                data[i] = str[i];
            }
            data[N] = '\0';
        }

        constexpr FixedString() {
            data[N] = '\0';
        }

        // NOLINTNEXTLINE(google-explicit-constructor, hicpp-explicit-conversions)
        constexpr operator std::string_view() const {
            return std::string_view{data, N};
        }

        [[nodiscard]] constexpr const char * c_str() const {return data;}
        [[nodiscard]] constexpr std::size_t size() const {return N;}

    };

    template<std::size_t N>
    inline std::ostream& operator<<(std::ostream& os, const FixedString<N>& Fixed_text) {
        if constexpr (kColouredTerm) {
            os << Fixed_text.c_str();
        }
        return os;
    }

    template<std::size_t N>
    FixedString(const char (&str)[N]) -> FixedString<N - 1>;

    template<std::size_t N, std::size_t M>
    inline constexpr FixedString<N+M> operator+(const FixedString<N>& textA, const FixedString<M>& textB ) {
        auto ResultString = FixedString<N + M>();

        std::size_t pos = 0;
        for (std::size_t i = 0; i < N; i++) {
            ResultString.data[pos] = textA.data[i];
            pos++;
        }

        for (std::size_t i = 0; i < M; i++) {
            ResultString.data[pos] = textB.data[i];
            pos++;
        }

        return ResultString;
    }
    template<std::size_t N>
    inline constexpr FixedString<N> operator+(const FixedString<N>& textA, std::string_view textB) {
        auto ResultString = FixedString<N + textB.size()>();
        std::size_t pos = 0;
        for (std::size_t i = 0; i < N; i++) {
            ResultString.data[pos] = textA.data[i];
            pos++;
        }
        size_t viewSize = textB.size();
        for (std::size_t i = 0; i < viewSize; i++) {
            ResultString.data[pos] = textB[i];
            pos++;
        }
        return ResultString;
    }
}
#endif //BASEUTILS_FIXEDSTRING_H