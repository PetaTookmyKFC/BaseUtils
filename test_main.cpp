//
// Created by PetaTookmyKFC on 22/10/2025.
//

#include <iostream>
#include <ostream>

#include "formatting.h"
#include "formatting_Refactor.h"

int main () {

    std::cout << " Colours <<  " << base_utils::fmt::c_red("red!") <<
        base_utils::fmt::c_yellow("yellow!") <<
        base_utils::fmt::c_green("green!") << "and done!" << std::endl;

    std::cout << base_utils::fmt::c_strikethrough("strikethrough!") << std::endl;
    std::cout << base_utils::fmt::c_strikethrough( base_utils::fmt::c_red("stricken red"))  << std::endl;
}
