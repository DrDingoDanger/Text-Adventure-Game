#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>
#include <vector>

#include "NPC.hpp"
#include "Mob.hpp"
#include "CraftingRecipe.hpp"

class Player;
class WorldMap;

class Location {
 private:
    float encounterRate;
    std::string name;
    std::vector<NPC*> _npcCollection;
    std::vector<CraftingRecipe*> _recipes;
    Inventory _areaResources;
    std::vector<Mob*> _mobs;

 public:
    Location(std::string name, std::vector<NPC*> _npcCollection,
         std::vector<CraftingRecipe*> _recipes, std::vector<Mob*> _mobs, Inventory areaResources);
    ~Location();
    void enter(Player* _player);
    void runEncounter(Player* _player, Mob* _mob);
    bool canExit(const std::string& _direction, WorldMap* map);
    std::string getName();
    NPC* getNPC(int index);
    CraftingRecipe* getRecipe(int index);
    Inventory& getInventory();
    Mob* getMob(int index);
    int numOfNPC();
};

#endif
