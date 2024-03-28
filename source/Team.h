#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <windows.h>
#include "../utilities/types.h"

constexpr uint8_t WHITE_COLOR = 7;

enum class Team // might be called Loyalty
{
    Neutral = 0, // available for map object (buildings and creatures). Neutral is not an option for players, but it is the only option for some map objects (obelisks, portals, huts, etc.)
    Red,
    Blue,
    Tan,
    Green,
    Orange,
    Purple,
    Teal,
    Pink,
};

void print_colored_string(const char ch, const Team team);
void print_colored_string(const std::string str, const Team team);

#endif