#ifndef TERRAINS_H
#define TERRAINS_H

// DO NOT CHANGE THE ORDER! IF A CHANGE IS NEEDED CHECK EVERY PLACE 'Terrain' IS USED

enum class Terrain
{
      None,         // native to Neutral
      // brings hero movement penalty
      Grass,        // native to Castle, Rampart
      Highlands,    // native to Conflux
      Dirt,         // native to Necropolis
      Lava,         // native to Inferno
      Rough,        // native to Stronghold
      Snow,         // native to Tower
      Swamp,        // native to Fortress, Cove
      Subterranean, // native to Dungeon
      Sand,         // None, brings penalty (having Nomads in the army negates it), always the terrian for battles on the shore
      Water,
      Favourable_Winds,
      
      // brings buffs or debuffs during battle
      Magic_Plains,
      Rockland,
      Fiery_Fields,
      Lucid_Pools,
      Magic_Clouds,
      Dunes,
      Cursed_Ground,
      Holy_Ground,
      Evil_Fog,
      Clover_Field,
      Cracked_Ice,
      Fields_of_Glory
}; 

#endif