#ifndef TEAM_H
#define TEAM_H

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

#endif