#pragma once

#include "EngineX/EngineX.h"

void makeDefault(Inventory& inv)
{
	inv.intVal = 
	{
		{"floor", 0},
		{"initialStorySeen", 0},
		{"boss1Complete", 0},
		{"boss2Complete", 0},
		{"boss3Complete", 0},
		// perks
		{"speed", 1},
		{"invincible", 1},
		{"healthBoost", 0},
		{"reLife", 1},
		{"timeFreeze", 0},
		{"phaze", 0}
	};
	inv.doubleVal =
	{
		{"locationX", 0.0},
		{"locationY", 0.0},
	};
}