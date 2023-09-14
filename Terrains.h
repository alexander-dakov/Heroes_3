#ifndef TERRAINS_H
#define TERRAINS_H

enum Terrain
{
// brings hero movement penalty
      Grass, // Castle, Rampart
      Highlands, // Conflux
      Dirt, // Necropolis
      Lava, // Inferno
      Rough, // Stronghold
      Snow, // Tower
      Swamp, // Fortress, Cove
      Subterranean, // Dungeon
      Sand, // None, brings penalty (having Nomads in the army negates it), always the terrian for battles on the shore
      Water,
      
// brings buffs or debuffs during battle
      Magic_Plains,
      Cursed_Ground,
      Rockland,
      Fiery_Fields,
      Lucid_Pools,
      Magic_Clouds,
      Holy_Ground,
      Evil_Fog,
      Clover_Field,
      Cracked_Ice,
      Dunes,
      Fields_of_Glory
}; 

#endif