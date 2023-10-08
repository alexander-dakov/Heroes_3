#ifndef ITEM_LIST_CPP
#define ITEM_LIST_CPP

#include "Item.h"

namespace Item_List
{
    //                       name,               slot,         type,           {  gold, m, s, c, g },  description,                                                
    Item Ring_of_Life(      "Ring of Life",      Slot::Hand,   Type::Minor,    {  5000, 0, 0, 0, 0 }, "This item increases the health of all hero's units by +1." );
    Item Ring_of_Vitality(  "Ring of Vitality",  Slot::Hand,   Type::Treasure, {  5000, 0, 0, 0, 0 }, "This item increases the health of all hero's units by +1." );
    Item Vial_of_Lifeblood( "Vial of Lifeblood", Slot::Pocket, Type::Major,    { 10000, 0, 0, 0, 0 }, "This item increases the health of all hero's units by +2." );
    Item Elixir_of_Life(    "Elixir of Life",    Slot::Pocket, Type::Relic,    { 20000, 0, 0, 0, 0 }, "All creatures get a 25% health bonus and gain the regeneration ability. Does not work on Undead or unliving creatures." );
    Item Ring_of_Wayfarer(  "Ring of Wayfarer",  Slot::Hand,   Type::Major,    {  5000, 0, 0, 0, 0 }, "When placed on the finger, this ring increases the combat speed of all hero's units by +1." );
}

#endif