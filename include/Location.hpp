#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>
#include <vector>
#include <random>

#include "NPC.hpp"
#include "Mob.hpp"
#include "Player.hpp"
#include "Inventory.hpp"
#include "CraftingRecipe.hpp"

class Player;
class WorldMap;

class Location {
 private:
    float encounterRate;
    std::string name;
    std::vector<NPC*> _npcCollection;
    std::vector<CraftingRecipe*> _recipes;
    Inventory* _areaResources;
    std::vector<Mob*> _mobs;

 public:
    Location(std::string name, std::vector<NPC*> _npcCollection,
         std::vector<CraftingRecipe*> _recipes, std::vector<Mob*> _mobs,
         Inventory* areaResources, float encounterRate);
    virtual ~Location();
    void runEncounter(Player* player);
    bool canExit(const std::string& _direction, WorldMap* map);
    std::string getName();
    NPC* getNPC(int index);
    CraftingRecipe* getRecipe(int index);
    Inventory* getInventory();
    Mob* getMob(int index);
    int numOfNPC();
};

class Terrain : public Location {
 public:
    Terrain(std::string name, std::vector<NPC*> _npcCollection,
            std::vector<CraftingRecipe*> _recipes,
            std::vector<Mob*> _mobs, Inventory* inv);
    ~Terrain();
};

class Unique : public Location {
 public:
    Unique(std::string name, std::vector<NPC*> _npcCollection,
          std::vector<CraftingRecipe*> _recipes,
          std::vector<Mob*> _mobs, Inventory* inv);
    ~Unique();
};

class Village : public Location {
 public:
    Village(std::string name, std::vector<NPC*> _npcCollection,
          std::vector<CraftingRecipe*> _recipes,
          std::vector<Mob*> _mobs, Inventory* inv);
    ~Village();
};

#endif
