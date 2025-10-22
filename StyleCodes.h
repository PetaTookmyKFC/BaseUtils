//
// Created by PetaTookmyKFC on 22/10/2025.
//

#ifndef BASEUTILS_STYLECODES_H
#define BASEUTILS_STYLECODES_H

namespace base_utils::fmt {
    enum class StyleCodes : int {
        Reset = 0,
        Bold = 1,
        Faint = 2,
        Italic = 3,
        Underline = 4,
        SlowBlink = 5,
        RapidBlink = 6,
        Reverse = 7,
        Conceal = 8, // Not widely Supported?
        strikethrough = 9, // Not widely Supported?
        DefaultFont = 10, // Default font

        Farktur = 20, // Not widely Supported
        DoubleUnderline = 21,

        NoBold = 22, // Not bold or faint
        NoItalic = 23, // not italic or farktur
        NoUnderline = 24, // no single or double underline
        NoBlink = 25,
        NoInverse = 27,
        Reveal = 28, // No Conceal
        NotStrikethrough = 29, //

// 4 Byte Colours

        FR_Black = 30,
        FG_Red = 31,
        FG_Green = 32,
        FG_Yellow = 33,
        FG_Blue = 34,
        FG_Magenta = 35,
        FG_Cyan = 36,
        FG_White = 37,

        // Bright Colours not standard
        FG_BBlack = 90,
        FG_BRed = 91,
        FG_BGreen = 92,
        FG_BYellow = 93,
        FG_BBlue = 94,
        FG_BMagenta = 95,
        FG_BCyan = 96,
        FG_BWhite = 97,

        BG_Black = 40,
        BG_RED = 41,
        BG_Green = 42,
        BG_Yellow = 43,
        BG_Blue = 44,
        BG_Magenta = 45,
        BG_Cyan = 46,
        BG_White = 47,

        // Bright Colours not standard
        BG_BBlack = 100,
        BG_BRed = 101,
        BG_BGreen = 102,
        BG_BYellow = 103,
        BG_BBlue = 104,
        BG_BMagenta = 105,
        BG_BCyan = 106,
        BG_BWhite = 107,

        SetForeground = 38, // next arguments are 5;<n> or 2;<r>;<g>;<b>;
        DefaultForeground = 39,

        SetBackground = 48, // next arguments are 5;<n> or 2;<r>;<g>;<b>;
        DefaultBackground = 49,

        Framed = 51,
        Encircled = 52,
        Overlined = 53,
        NoFrame = 54, // not framed or encircled
        NoOverline = 55, //

    };


}

#endif //BASEUTILS_STYLECODES_H