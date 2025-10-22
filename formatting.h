//
// Created by PetaTookmyKFC on 22/10/2025.
//

#ifndef BASEUTILS_FORMATTING_H
#define BASEUTILS_FORMATTING_H

#define COLOURED_TERM true

#define C_Log(cond ,code) if (cond) { code }
#define DEBUG(code) if (debug) { code }

#if COLOURED_TERM

    #if FORMATTED_TERM
        #define C_LIST(any) std::cout << "  |- " << any << "\n";
        #define C_LIST_No( any ) std::cout << "  |- " << any;
        #define SUCCESS( any ) std::cout << "\033[1;32m[SUCCESS] " << any << " \033[0m\n";
        #define FAILURE( any ) std::cout << "\033[1;31m[FAILURE] " << any << " \033[0m\n";



    #else
        #define C_LIST(any) std::cout << any << "\n";
        #define C_LIST_No( any ) std::cout << any;
        #define SUCCESS( any ) std::cout << "\033[1;32m" << any << " \033[0m\n";
        #define FAILURE( any ) std::cout << "\033[1;31m" << any << " \033[0m\n";

    #endif

    #define C_RED( any ) "\033[1;31m" << any << "\033[0m"
    #define	C_GREEN(any) "\033[1;32m" << any << "\033[0m"
    #define C_YELLOW(any)  "\033[1;33m" << any << "\033[0m"      /* Yellow */


#else
    #if FORMATTED_TERM
        #define C_LIST(any) std::cout << "  |- " << any << "\n";
        #define C_LIST_No( any ) std::cout << "  |- " << any;
        #define SUCCESS( any ) std::cout << "[SUCCESS] " << any << " \n";
        #define FAILURE( any ) std::cout << "[FAILURE] " << any << " \n";
    #else
        #define C_LIST(any) std::cout << any << "\n";
        #define C_LIST_No( any ) std::cout << any;
        #define SUCCESS( any ) std::cout << any << " \n";
        #define FAILURE( any ) std::cout << any << " \n";
    #endif

    #define C_RED( any ) any
    #define	C_GREEN(any) any
    #define C_YELLOW(any) any

#endif


#endif //BASEUTILS_FORMATTING_H