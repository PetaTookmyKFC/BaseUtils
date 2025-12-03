
#include <iostream>

#include "../include/BaseUtils/FullFormatting.h"
#include "../include/BaseUtils/PrefixFormatting.h"
#include "../include/BaseUtils/SuffixFormatting.h"

using namespace base_utils::fmt;

// --- Custom Styles for Testing ---
template<auto... Styles>
inline constexpr auto ListItem = ComPrefix<Styles...>(
    FixedString("|- ")
);

template<auto... Styles>
inline constexpr auto AutoSemi = ComSuffix<Styles...>(
    FixedString("|- ")
);

inline constexpr auto DangerAuto = ComFormatted<
    BOLD_CODE, UNDERLINE_CODE, FG_GREEN_CODE, BG_BLACK_CODE
    >(FixedString("|- 1: "), FixedString(" -| \n"));

inline constexpr auto Danger = ComPrefix<
    BOLD_CODE, FG_BRIGHT_RED_CODE>(FixedString("🚨 DANGER 🚨"));
inline constexpr auto Success = ComPrefix<
    BOLD_CODE,
    FG_BRIGHT_GREEN_CODE>(FixedString( "SUCCESS : " ));

constexpr inline auto BB = ComSuffix<FG_RED_CODE, UNDERLINE_CODE, BOLD_CODE>(FixedString(" - Affixed!"));
constexpr inline auto LI = ListItem<BG_BRIGHT_GREEN_CODE, FG_BLACK_CODE, BOLD_CODE>;
constexpr inline auto AD = AutoSemi<FG_BRIGHT_RED_CODE, BG_BLACK_CODE>;

// -- End Custom Styles for Testing ---

int main() {


    std::cout << "\n ! TESTING FORMATTING ! \n";

    // // std::cout << "\n";
    // std::cout << Bold(BrightCyan("╔══════════════════════════════════════════════════════════╗")) << "\n";
    // std::cout << Bold(BrightCyan("║")) << "  " << BOLD("BaseUtils Formatting Library - Visual Test Suite") << "     " << BOLD(BRIGHT_CYAN("║")) << "\n";
    // std::cout << Bold(BrightCyan("╚══════════════════════════════════════════════════════════╝")) << "\n";
    //
    //

    std::cout << Danger("Very Bad thing!") << std::endl;
    std::cout << Red("TEST COLOUR") << std::endl;
    std::cout << Success( "Example Text ") << std::endl;
    std::cout << Danger(" - Everythings on fire? ") << std::endl;

    std::cout << Success( " -- TESTIGN LIST -- ") << std::endl;
    std::cout << ListItem<BG_BRIGHT_GREEN_CODE, FG_BLACK_CODE, BOLD_CODE>(
        "Item One!!!") << std::endl;

    std::cout << ListItem<BG_BRIGHT_GREEN_CODE, FG_BLACK_CODE, BOLD_CODE>(
        "Item two!!!") << std::endl;
    std::cout << ListItem<BG_BRIGHT_GREEN_CODE, FG_BRIGHT_RED_CODE, BOLD_CODE>(
    "Item three!!!") << std::endl;
    std::cout << ListItem<BG_BRIGHT_GREEN_CODE, FG_BLACK_CODE, BOLD_CODE>("Item One!!!") << std::endl;

    std::cout << Success( "-- TESTING STYLE CONSTS --\n" );
    std::cout << "List Menu : \n" <<
        LI("Hello Item one!\n") <<
        LI("Item two!") << std::endl;

    std::cout << Success("-- Texting Suffix? --");

    std::cout << BB("Hello World!!! \n") << std::endl;
    std::cout << AD("Example Item!") << std::endl;

    std::cout << Danger("-TESTING FULLY FOPRMATTED-") << std::endl;


    for (int i = 0; i < 5; i++) {

        std::cout << DangerAuto( "hello world" + std::to_string(i) );

    }



    //
    // test_basic_formatting();
    // test_colors();
    // test_bright_colors();
    // test_background_colors();
    // test_combined_formatting();
    // test_message_types();
    // test_debug_formatting();
    // test_complex_examples();
    //
    // print_section("Test Complete");
    // std::cout << SUCCESS("All formatting examples displayed successfully!") << "\n";
    // std::cout << INFO("Visually inspect the output above to verify formatting.") << "\n\n";
    //
    return 0;
}
