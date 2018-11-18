#ifndef PCH_H
#define PCH_H


// only include if the compiler is GCC
#if (defined(__GNUC__) || defined(__GNUG__)) && !(defined(__clang__) || defined(__INTEL_COMPILER))
	#include <bits/stdc++.h>
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "EngineX/EngineX.h"


#endif //PCH_H
