#ifndef ITEM_LIST_CPP
#define ITEM_LIST_CPP

#include "Item.h"

namespace Item_List
{
    //                                    name,                            slot,           type,           {  gold, m, s, c, g },  effect
    // Helmet
    Item Helm_of_Heavenly_Enlightenment( "Helm of Heavenly Enlightenment", Item::Slot::Helmet,   Item::Type::Relic,    { 24000, 0, 0, 0, 0 }, "All primary skills +6." );

    // Cape
    Item Cape_of_Velocity(               "Cape of Velocity",               Item::Slot::Cape,     Item::Type::Major,    { 10000, 0, 0, 0, 0 }, "Unit's speed +2." );
    
    // Necklace
    Item Celestial_Necklace_of_Bliss(    "Celestial Necklace of Bliss",    Item::Slot::Necklace, Item::Type::Relic,    { 12000, 0, 0, 0, 0 }, "All primary skills +3." );
    Item Necklace_of_Swiftness(          "Necklace of Swiftness",          Item::Slot::Necklace, Item::Type::Treasure, {  5000, 0, 0, 0, 0 }, "Unit's speed +1." );
    Item Pendant_of_Courage(             "Pendant of Courage",             Item::Slot::Necklace, Item::Type::Major,    {  7000, 0, 0, 0, 0 }, "Morale +3. Luck +3." );
    
    // Weapon
    Item Sword_of_Judgement(             "Sword of Judgement",             Item::Slot::Weapon,   Item::Type::Relic,    { 20000, 0, 0, 0, 0 }, "All primary skills +5." );
    // Item Angelic_Alliance(               "Angelic Alliance",               Item::Slot::Weapon,   Item::Type::Relic,    { 84000, 0, 0, 0, 0 }, "All primary skills +21. Allows Rampart, Tower, Fortress, Stronghold and Castle creatures to be mixed without a morale penalty. Casts expert Prayer at the start of combat." );
    Item Centaurs_Axe(                    "Centaur's Axe",                 Item::Slot::Weapon,   Item::Type::Treasure, {  2000, 0, 0, 0, 0 }, "Attack skill +2." );
    Item Red_Dragon_Flame_Tongue(         "Red Dragon Flame Tongue",       Item::Slot::Weapon,   Item::Type::Minor,    {  4000, 0, 0, 0, 0 }, "Attack skill +2. Defense skill +2." );
    Item Blackshard_of_the_Dead_Knight(   "Blackshard of the Dead Knight", Item::Slot::Weapon,   Item::Type::Minor,    {  3000, 0, 0, 0, 0 }, "Attack skill +3." );
    // Item Armageddons_Blade(               "Armageddon's Blade",            Item::Slot::Weapon,   Item::Type::Relic,    { 50000, 0, 0, 0, 0 }, "Attack skill +3. Defense skill +3. Power skill +6. Knowledge skill +6. Adds Expert Armageddon spell to spellbook. Immune to Armageddon." );
    Item Greater_Gnolls_Flail(             "Greater Gnoll's Flail",        Item::Slot::Weapon,   Item::Type::Minor,    {  4000, 0, 0, 0, 0 }, "Attack skill +4." );
    Item Ogres_Club_of_Havoc(              "Ogre's Club of Havoc",         Item::Slot::Weapon,   Item::Type::Major,    {  5000, 0, 0, 0, 0 }, "Attack skill +5." );
    Item Sword_of_Hellfire(                "Sword of Hellfire",            Item::Slot::Weapon,   Item::Type::Major,    {  6000, 0, 0, 0, 0 }, "Attack skill +6." );
    Item Trident_of_Dominion(              "Trident of Dominion",          Item::Slot::Weapon,   Item::Type::Major,    {  7000, 0, 0, 0, 0 }, "Attack skill +7." );
    Item Titans_Gladius(                   "Titan's Gladius",              Item::Slot::Weapon,   Item::Type::Relic,    { 10000, 0, 0, 0, 0 }, "Attack skill +12. Defense skill -3." );

    // Shield
    Item Lions_Shield_of_Courage(        "Lion's Shield of Courage",       Item::Slot::Shield,   Item::Type::Relic,    { 16000, 0, 0, 0, 0 }, "All primary skills +4." );
    Item Dragon_Scale_Shield(            "Dragon Scale Shield",            Item::Slot::Shield,   Item::Type::Major,    {  6000, 0, 0, 0, 0 }, "Attack skill +3. Defense skill +3." );
    Item Shield_of_the_Dwarven_Lords(    "Shield of the Dwarven Lords",    Item::Slot::Shield,   Item::Type::Treasure, {  2000, 0, 0, 0, 0 }, "Defense skill +2." );
    Item Shield_of_the_Yawning_Dead(     "Shield of the Yawning Dead",     Item::Slot::Shield,   Item::Type::Minor,    {  3000, 0, 0, 0, 0 }, "Defense skill +3." );
    Item Buckler_of_the_Gnoll_King(      "Buckler of the Gnoll King",      Item::Slot::Shield,   Item::Type::Minor,    {  4000, 0, 0, 0, 0 }, "Defense skill +4." );
    Item Targ_of_the_Rampaging_Ogre(     "Targ of the Rampaging Ogre",     Item::Slot::Shield,   Item::Type::Major,    {  5000, 0, 0, 0, 0 }, "Defense skill +5." );
    Item Shield_of_the_Damned(           "Shield of the Damned",           Item::Slot::Shield,   Item::Type::Major,    {  6000, 0, 0, 0, 0 }, "Defense skill +6." );
    Item Shield_of_Naval_Glory(          "Shield of Naval Glory",          Item::Slot::Shield,   Item::Type::Major,    {  7000, 0, 0, 0, 0 }, "Defense skill +7." );
    Item Sentinels_Shield(               "Sentinel's Shield",              Item::Slot::Shield,   Item::Type::Relic,    { 10000, 0, 0, 0, 0 }, "Defense skill +12. Attack skill -3." );
    
    // Armor
    Item Armor_of_Wonder(                "Armor of Wonder",                Item::Slot::Armor,    Item::Type::Minor,    {  4000, 0, 0, 0, 0 }, "All primary skills +1." );
    Item Dragon_Scale_Armor(             "Dragon Scale Armor",             Item::Slot::Armor,    Item::Type::Relic,    {  8000, 0, 0, 0, 0 }, "Attack skill +4. Defense skill +4." );
    // Item Plate_of_Dying_Light(           "Plate of Dying Light",           Item::Slot::Armor,    Item::Type::Relic,    { 10000, 0, 0, 0, 0 }, "Enemy's Power skill -25%." );
    Item Breastplate_of_Petrified_Wood(  "Breastplate of Petrified Wood",  Item::Slot::Armor,    Item::Type::Treasure, {  1000, 0, 0, 0, 0 }, "Power skill +1." );
    Item Rib_Cage(                       "Rib Cage",                       Item::Slot::Armor,    Item::Type::Minor,    {  3000, 0, 0, 0, 0 }, "Power skill +2." );
    Item Scales_of_the_Greater_Basilisk( "Scales of the Greater Basilisk", Item::Slot::Armor,    Item::Type::Minor,    {  4000, 0, 0, 0, 0 }, "Power skill +3." );
    Item Tunic_of_the_Cyclops_King(      "Tunic of the Cyclops King",      Item::Slot::Armor,    Item::Type::Major,    {  5000, 0, 0, 0, 0 }, "Power skill +4." );
    Item Breastplate_of_Brimstone(       "Breastplate of Brimstone",       Item::Slot::Armor,    Item::Type::Major,    {  6000, 0, 0, 0, 0 }, "Power skill +5." );
    Item Royal_Armor_of_Nix(             "Royal Armor of Nix",             Item::Slot::Armor,    Item::Type::Major,    {  7000, 0, 0, 0, 0 }, "Power skill +6." );
    Item Titans_Cuirass(                 "Titan's Cuirass",                Item::Slot::Armor,    Item::Type::Relic,    { 10000, 0, 0, 0, 0 }, "Power skill +10. Knowledge skill -2." );
    
    // Hand
    Item Quiet_Eye_of_the_Dragon(        "Quiet Eye of the Dragon",        Item::Slot::Hand,     Item::Type::Treasure, {  2000, 0, 0, 0, 0 }, "Attack skill +1. Defense skill +1." );
    Item Ring_of_Vitality(               "Ring of Vitality",               Item::Slot::Hand,     Item::Type::Treasure, {  5000, 0, 0, 0, 0 }, "Unit's health points +1." );
    Item Ring_of_Life(                   "Ring of Life",                   Item::Slot::Hand,     Item::Type::Minor,    {  5000, 0, 0, 0, 0 }, "Unit's health points +1." );
    Item Ring_of_Wayfarer(               "Ring of Wayfarer",               Item::Slot::Hand,     Item::Type::Major,    {  5000, 0, 0, 0, 0 }, "Unit's speed +1." );
    Item Still_Eye_of_the_Dragon(        "Still Eye of the Dragon",        Item::Slot::Hand,     Item::Type::Treasure, {  2000, 0, 0, 0, 0 }, "Morale +1. Luck +1." );
    Item Ring_of_Suppression(            "Ring of Suppression",            Item::Slot::Hand,     Item::Type::Treasure, {  4000, 0, 0, 0, 0 }, "Enemy morale -1." );
    
    // Boots
    Item Sandals_of_the_Saint(           "Sandals of the Saint",           Item::Slot::Boots,    Item::Type::Relic,    {  8000, 0, 0, 0, 0 }, "All primary skills +2." );
    
    // Pocket
    Item Vial_of_Lifeblood(              "Vial of Lifeblood",              Item::Slot::Pocket,   Item::Type::Major,    { 10000, 0, 0, 0, 0 }, "Unit's health points +2." );
    // Item Elixir_of_Life(                 "Elixir of Life",                 Item::Slot::Pocket, Item::Type::Relic,    { 20000, 0, 0, 0, 0 }, "All creatures get a 25% health bonus and gain the regeneration ability. Does not work on Undead or unliving creatures." );
    Item Badge_of_Courage(               "Badge of Courage",               Item::Slot::Pocket,   Item::Type::Treasure, {  1000, 0, 0, 0, 0 }, "Morale +1." );
    Item Crest_of_Valor(                 "Crest of Valor",                 Item::Slot::Pocket,   Item::Type::Treasure, {  1000, 0, 0, 0, 0 }, "Morale +1." );
    Item Glyph_of_Gallantry(             "Glyph of Gallantry",             Item::Slot::Pocket,   Item::Type::Treasure, {  1000, 0, 0, 0, 0 }, "Morale +1." );
    Item Hideous_Mask(                   "Hideous Mask",                   Item::Slot::Pocket,   Item::Type::Minor,    {  4000, 0, 0, 0, 0 }, "Enemy morale -1." );
    Item Pendant_of_Downfall(            "Pendant of Downfall",            Item::Slot::Pocket,   Item::Type::Major,    {  7000, 0, 0, 0, 0 }, "Enemy morale -2." );
    Item Spirit_of_Oppression(           "Spirit of Oppression",           Item::Slot::Pocket,   Item::Type::Treasure, {  2000, 0, 0, 0, 0 }, "Negates all positive morale bonuses during combat for both you and your opponent." );
    Item Cards_of_Prophecy(              "Cards of Prophecy",              Item::Slot::Pocket,   Item::Type::Treasure, {  1000, 0, 0, 0, 0 }, "Luck +1." );
    Item Clover_of_Fortune(              "Clover of Fortune",              Item::Slot::Pocket,   Item::Type::Treasure, {  1000, 0, 0, 0, 0 }, "Luck +1." );
    Item Ladybird_of_Luck(               "Ladybird of Luck",               Item::Slot::Pocket,   Item::Type::Treasure, {  1000, 0, 0, 0, 0 }, "Luck +1." );
    Item Runes_of_Imminency(             "Runes of Imminency",             Item::Slot::Pocket,   Item::Type::Treasure, {  2000, 0, 0, 0, 0 }, "Enemy luck -1." );
    Item Demons_Horseshoe(               "Demon's Horseshoe",              Item::Slot::Pocket,   Item::Type::Treasure, {  2000, 0, 0, 0, 0 }, "Enemy luck -1." );
    Item Shamans_Puppet(                 "Shaman's Puppet",                Item::Slot::Pocket,   Item::Type::Minor,    {  4000, 0, 0, 0, 0 }, "Enemy luck -2." );
    Item Hourglass_of_the_Evil_Hour(     "Hourglass of the Evil Hour",     Item::Slot::Pocket,   Item::Type::Treasure, {  2000, 0, 0, 0, 0 }, "Negates all positive luck bonuses during combat for both you and your opponent." );

    // TO DO : add all items
}

#endif