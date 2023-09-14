#ifndef MORALE_LUCK_H
#define MORALE_LUCK_H

// how likely is for stack of troops to take initiative during its turn in battle
enum class Morale
{
      Terrible = -3,
      Awful,
      Bad,
      Neutral,
      Good,
      Great,
      Superb
};

// how lucky a stack of troops is when attacking
enum class Luck
{
      Terrible = -3,
      Awful,
      Bad,
      Neutral,
      Good,
      Great,
      Superb
};

#endif