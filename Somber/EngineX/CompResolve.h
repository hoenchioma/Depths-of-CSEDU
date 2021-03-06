#pragma once

/*
    The file contains necessary macros for
    * previous versions of SFML
    * resolve conflicts between Windows and Unix
*/

// support for previous versions of SFML
#if SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR >= 5
#define ENTER_KEY sf::Keyboard::Enter
#else
#define ENTER_KEY sf::Keyboard::Return
#endif

// changes sprintf for MSVC compiler
#ifdef _MSC_VER
#define sprintf sprintf_s
#endif
