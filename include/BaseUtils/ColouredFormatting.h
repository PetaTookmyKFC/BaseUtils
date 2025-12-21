#ifndef BASEUTILS_LIBRARY_H
#define BASEUTILS_LIBRARY_H

#include <format>
#include <string_view>
#include <utility>
#include <iostream>
/***
 * NO_COLOUR = Can the terminal use shell colours (Escape codes)
 * NO_FORMAT = Should the text have icons such as bulletpoints?
 * NO_DEBUG = Removes any the base_util_Debug from executing (for release)
***/

namespace base_utils::fmt {
#ifdef NO_COLOUR
    inline constexpr bool kColouredTerm = false;
# else
    inline constexpr bool kColouredTerm = true;
#endif


    // Passes the statement onto the next operator
    template<typename F>
    void log(bool cond, F &&code) {
        if (cond) {
            std::forward<F>(code);
        }
    }



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
        os << Fixed_text.c_str();
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



    // Compile-time style code constants (zero allocation)
    inline constexpr FixedString RESET_CODE = "\033[0m";
    inline constexpr FixedString BOLD_CODE = "\033[1m";
    inline constexpr FixedString FAINT_CODE = "\033[2m";
    inline constexpr FixedString ITALIC_CODE = "\033[3m";
    inline constexpr FixedString UNDERLINE_CODE = "\033[4m";
    inline constexpr FixedString BLINK_CODE = "\033[5m";
    inline constexpr FixedString REVERSE_CODE = "\033[7m";
    inline constexpr FixedString STRIKETHROUGH_CODE = "\033[9m";

    // Foreground colors
    inline constexpr FixedString FG_BLACK_CODE = "\033[30m";
    inline constexpr FixedString FG_RED_CODE = "\033[31m";
    inline constexpr FixedString FG_GREEN_CODE = "\033[32m";
    inline constexpr FixedString FG_YELLOW_CODE = "\033[33m";
    inline constexpr FixedString FG_BLUE_CODE = "\033[34m";
    inline constexpr FixedString FG_MAGENTA_CODE = "\033[35m";
    inline constexpr FixedString FG_CYAN_CODE = "\033[36m";
    inline constexpr FixedString FG_WHITE_CODE = "\033[37m";

    // Bright foreground colors
    inline constexpr FixedString FG_BRIGHT_BLACK_CODE = "\033[90m";
    inline constexpr FixedString FG_BRIGHT_RED_CODE = "\033[91m";
    inline constexpr FixedString FG_BRIGHT_GREEN_CODE = "\033[92m";
    inline constexpr FixedString FG_BRIGHT_YELLOW_CODE = "\033[93m";
    inline constexpr FixedString FG_BRIGHT_BLUE_CODE = "\033[94m";
    inline constexpr FixedString FG_BRIGHT_MAGENTA_CODE = "\033[95m";
    inline constexpr FixedString FG_BRIGHT_CYAN_CODE = "\033[96m";
    inline constexpr FixedString FG_BRIGHT_WHITE_CODE = "\033[97m";

    // Background colors
    inline constexpr FixedString BG_BLACK_CODE = "\033[40m";
    inline constexpr FixedString BG_RED_CODE = "\033[41m";
    inline constexpr FixedString BG_GREEN_CODE = "\033[42m";
    inline constexpr FixedString BG_YELLOW_CODE = "\033[43m";
    inline constexpr FixedString BG_BLUE_CODE = "\033[44m";
    inline constexpr FixedString BG_MAGENTA_CODE = "\033[45m";
    inline constexpr FixedString BG_CYAN_CODE = "\033[46m";
    inline constexpr FixedString BG_WHITE_CODE = "\033[47m";

    // Bright background colors
    inline constexpr FixedString BG_BRIGHT_BLACK_CODE = "\033[100m";
    inline constexpr FixedString BG_BRIGHT_RED_CODE = "\033[101m";
    inline constexpr FixedString BG_BRIGHT_GREEN_CODE = "\033[102m";
    inline constexpr FixedString BG_BRIGHT_YELLOW_CODE = "\033[103m";
    inline constexpr FixedString BG_BRIGHT_BLUE_CODE = "\033[104m";
    inline constexpr FixedString BG_BRIGHT_MAGENTA_CODE = "\033[105m";
    inline constexpr FixedString BG_BRIGHT_CYAN_CODE = "\033[106m";
    inline constexpr FixedString BG_BRIGHT_WHITE_CODE = "\033[107m";

    template<std::size_t N>
    struct StyledText {
        FixedString<N> style;
        std::string_view content;
        constexpr StyledText(const FixedString<N>& style_code, std::string_view text) : style (style_code), content(text) {
            std::cout << "TEXT " << content << "\n";
        }
    };

    template<std::size_t N>
    inline std::ostream& operator<<(std::ostream& os, const StyledText<N>& styled_text) {
        if constexpr (kColouredTerm) {
        os << styled_text.style.c_str() << styled_text.content << RESET_CODE.c_str();
        } else {
            os << styled_text.content;
        }

        return os;
    }

    // THE AI IS VIBING AT THE MOMENT

    // CompileTime extract the numeric code from the escape sequence
    template<std::size_t N>
    constexpr int extract_code (const FixedString<N>& style) {
        int result = 0;
        bool in_number =false;
        for (std::size_t i = 0; i < N; i++) {
            if (style.data[i] == '[') {
                in_number = true;
            } else if (style.data[i] == 'm' || style.data[i] == ';') {
                break;
            } else if (in_number && style.data[i] >= '0' && style.data[i] <= '9') {
                result = result * 10 + (style.data[i] - '0');
            }
        }
        return result;
    }
    // CompileTime count the digits in a number
    constexpr std::size_t count_digits(int num) {
        if (num == 0) return 1;
        std::size_t count = 0;
        if (num < 0) {
            count = 1;
            num = -num;
        }
        while (num > 0) {
            count++;
            num /= 10;
        }
        return count;
    }
    // Just copied from AI !

     // Compile-time helper to convert int to string
    constexpr void int_to_str(int num, char* buffer, std::size_t& pos) {
        if (num == 0) {
            buffer[pos++] = '0';
            return;
        }

        if (num < 0) {
            buffer[pos++] = '-';
            num = -num;
        }

        char temp[12];
        int temp_pos = 0;
        while (num > 0) {
            temp[temp_pos++] = '0' + (num % 10);
            num /= 10;
        }

        while (temp_pos > 0) {
            buffer[pos++] = temp[--temp_pos];
        }
    }

    template<std::size_t... Ns>
    constexpr std::size_t sum_code_digits(const FixedString<Ns>&... styles) {
        return (count_digits(extract_code(styles)) + ...);
    }

    // Helper to compute digits from actual FixedString values as template parameters
    template<auto... Styles>
    struct ComputeDigits {
        static constexpr std::size_t value = (count_digits(extract_code(Styles)) + ...);
    };

    // Compile-time composition of multiple styles
    template<auto... Styles>
    constexpr auto compose_impl() {
        constexpr std::size_t num_styles = sizeof...(Styles);
        constexpr std::size_t total_digits = ComputeDigits<Styles...>::value;
        constexpr std::size_t result_size = 2 + total_digits + (num_styles - 1) + 1;

        int codes[] = { extract_code(Styles)... };

        char result[result_size + 1] = {};
        std::size_t pos = 0;

        result[pos++] = '\033';
        result[pos++] = '[';

        for (std::size_t i = 0; i < num_styles; ++i) {
            if (i > 0) {
                result[pos++] = ';';
            }
            int_to_str(codes[i], result, pos);
        }

        result[pos++] = 'm';
        result[pos] = '\0';

        return FixedString<result_size>(result);
    }

    // Wrapper that returns a callable style function
    template<std::size_t N>
    struct StyleFunction {
        FixedString<N> style_code;

        constexpr StyleFunction(const FixedString<N>& code) : style_code(code) {}

        constexpr auto operator()(std::string_view text) const {
            return StyledText<N>(style_code, text);
        }
    };

    // Public Compose function
    template<auto... Styles>
    constexpr auto Compose() {
        return StyleFunction(compose_impl<Styles...>());
    }




    // Preset style functions (zero heap allocation)
    inline constexpr auto Bold(std::string_view str) {
        return StyledText<BOLD_CODE.size()>(BOLD_CODE, str);
    }

    inline constexpr auto Italic(std::string_view str) {
        return StyledText<ITALIC_CODE.size()>(ITALIC_CODE, str);
    }

    inline constexpr auto Underline(std::string_view str) {
        return StyledText<UNDERLINE_CODE.size()>(UNDERLINE_CODE, str);
    }

    inline constexpr auto Strikethrough(std::string_view str) {
        return StyledText<STRIKETHROUGH_CODE.size()>(STRIKETHROUGH_CODE, str);
    }

    inline constexpr auto Blink(std::string_view str) {
        return StyledText<BLINK_CODE.size()>(BLINK_CODE, str);
    }

    inline constexpr auto Reverse(std::string_view str) {
        return StyledText<REVERSE_CODE.size()>(REVERSE_CODE, str);
    }

    // Color functions
    inline constexpr auto Red(std::string_view str) {
        return StyledText<FG_RED_CODE.size()>(FG_RED_CODE, str);
    }

    inline constexpr auto Green(std::string_view str) {
        return StyledText<FG_GREEN_CODE.size()>(FG_GREEN_CODE, str);
    }

    inline constexpr auto Yellow(std::string_view str) {
        return StyledText<FG_YELLOW_CODE.size()>(FG_YELLOW_CODE, str);
    }

    inline constexpr auto Blue(std::string_view str) {
        return StyledText<FG_BLUE_CODE.size()>(FG_BLUE_CODE, str);
    }

    inline constexpr auto Cyan(std::string_view str) {
        return StyledText<FG_CYAN_CODE.size()>(FG_CYAN_CODE, str);
    }

    inline constexpr auto Magenta(std::string_view str) {
        return StyledText<FG_MAGENTA_CODE.size()>(FG_MAGENTA_CODE, str);
    }

    inline constexpr auto White(std::string_view str) {
        return StyledText<FG_WHITE_CODE.size()>(FG_WHITE_CODE, str);
    }

    // Bright colors
    inline constexpr auto BrightRed(std::string_view str) {
        return StyledText<FG_BRIGHT_RED_CODE.size()>(FG_BRIGHT_RED_CODE, str);
    }

    inline constexpr auto BrightGreen(std::string_view str) {
        return StyledText<FG_BRIGHT_GREEN_CODE.size()>(FG_BRIGHT_GREEN_CODE, str);
    }

    inline constexpr auto BrightYellow(std::string_view str) {
        return StyledText<FG_BRIGHT_YELLOW_CODE.size()>(FG_BRIGHT_YELLOW_CODE, str);
    }

    inline constexpr auto BrightCyan(std::string_view str) {
        return StyledText<FG_BRIGHT_CYAN_CODE.size()>(FG_BRIGHT_CYAN_CODE, str);
    }

    // inline constexpr auto Danger = Compose<
    //     BOLD_CODE,
    //     FG_BRIGHT_RED_CODE,
    //     UNDERLINE_CODE
    // >();
    //
    // inline constexpr auto Sucess = Compose <
    //         BOLD_CODE,
    //         FG_BRIGHT_GREEN_CODE,
    //         UNDERLINE_CODE
    //     >();

}


#endif // BASEUTILS_LIBRARY_H
