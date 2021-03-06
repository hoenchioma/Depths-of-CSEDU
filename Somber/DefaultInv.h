#pragma once

#include "EngineX/EngineX.h"

#include <map>

static void makeDefault(Inventory& inv)
{
	inv.intVal = 
	{
		{"floor", 0},
		{"boss1Complete", 0},
		{"boss2Complete", 0},
		{"boss3Complete", 0},
		{"snek", 0},
		{"save", 0},
		// perks
		{"speed",		0},
		{"invincible",	0},
		{"healthBoost", 0},
		{"bandage",		0},
		{"reLife",		0},
		{"timeFreeze",	0},
		{"phase",		2},
		// keys
		{"keys",		0},
	};
	inv.doubleVal =
	{
		{"locationX", 0.0},
		{"locationY", 0.0},
	};
}

static const std::vector <std::string> perkName =
{
	"speed",
	"invincible",
	"healthBoost",
	"bandage",
	"reLife",
	"timeFreeze",
	"phase"
};