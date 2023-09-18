#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include "../utilities/types.h"

enum Placement
{
      Helmet = 1, // 1 = crown, hat
      Necklace,   // 2
      Armor,      // 3
      Cape,       // 4
      Boots,      // 5
      Sword,      // 6 = mace, trident, club
      Right_hand, // 7 = ring, gloves
      Shield,     // 8
      Left_hand,  // 9 = ring, gloves
      Pocket_1,   // 10 = orbs, tomes, figurines, badges and others
      Pocket_2,   // 11 = orbs, tomes, figurines, badges and others
      Pocket_3,   // 12 = orbs, tomes, figurines, badges and others
      Pocket_4,   // 13 = orbs, tomes, figurines, badges and others
      Pocket_5,   // 14 = orbs, tomes, figurines, badges and others
      Treasure_chest // 15
};

class Item
{
      private:
      Placement _placement;
      std::string _name;
      std::string _effect;
      bool _equipped;
      

      public:


};


#endif