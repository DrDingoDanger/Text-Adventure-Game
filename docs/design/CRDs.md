### Game
**Responsiblility:**  Handles the interactions for player movement, ui/display (map, inventory, NPC, crafting), win/lose/dead state.
**Key Methods:**
- 'isOver(): bool const' - Represents if the game is over.
- 'start()' - Initializes the game.
- 'update()' - Handles the player interactions, displaying options.
- 'checkWin(): bool const' - Verifies (returns true) if player has possesion of target win item.
- 'checkLose(): bool const' - Verifies (returns true) if the players health has reduced to zero.
- 'endGame()' - Tracks if game ends. Rolls credits.

### ScreenDisplay
**Responsiblility:** Displays player inventory, map, user actions, dialog, and gernal interfaces. 
**Key Methods:**
- 'gameInstructions(out:ostream&)' - Displays the instrucitons for the game.
- 'drawMap(out:ostream&,map:WorldMap*)' - Displays the world map with the players location.
- 'displayChoices(out:ostream&)' - Displays the players interactible choices.
- 'displayInventory(out:ostream&,_player:Player)' - Displays the characters current inventory.

### UserInput
**Responsiblility:** Translates user input into player actions and movement.
**Key Methods:**
- 'moveDirection(): std::string' - takes orthoginal input and stores it as a movement string. 
- 'playerAction(): int' - Use specified player actions and world interactions.
- 'limitInput(max:int): int' - Checks that the players input is valid.
- 'yesorNo(): char' - User confirmation prompt.
- 'pressEnter()' - Confirmation input before continuing specified actions or scenarios.

### Player
**Responsiblility:** Represents the player enitity. Manages player stats, crafting, buying, inventory, and location.
**Key Methods:**
- 'getHealth(): int const' - Returns the players current health.
- 'getHunger(): int const' - Returns the players current hunger.
- 'getInventory(): Inventory&' - Returns reference for player inventory.
- 'getitemAt(ind:int): Item*' - Return pointer to player item.
- 'getCurrent(): Location*' - return pointer to player location.
- 'inventorySize(): int' - Returns the number of items in player inventory.
- 'move(direction:Const std::string&,map:WorldMap*,valid:bool&)' - Validiates and preforms player move on map.
- 'takeDamage(damage:int)' - Reduces health bar. Based on damage source.
- 'eat(restore:int)' - Allows the player to eat a food item, restoring hunger.
- 'craft(recipe:CraftingRecipe&)' - Verifies and creates item using materials from inventory.
- 'Buy(_item:Item&,shop:ShopNPC&)' - Transfers item from shop NPC to player in echange for something else.

### WorldMap
**Responsiblility:** Contains a list of locations the player can travel to and movement.
**Key Methods:** 
- 'getCurrentIndex(current:Location*): int' - Returns the index of a given location.
- 'updateLocation(_direction:const std::string&,current:Location*): Location*' - Updated the players current location based on user input direction.
- 'getLocation(index:int): Location*' - Returns a location given the index.

### Location (Abstract)
**Responsiblility:** Tracks the name, resources, NPC's, Mobs, recipes, and entounter rate of a set location in the world.
**Key Methods:**
- 'enter(_player:Player*)' -  Allows the player to enter a given location.
- 'runEncounter(_player:Player*,_mob:Mob*)' - Given the region encounter rate, determines if the player ecounters a Mob.
- 'canExit(_direction:const std::string&,map:WorldMap*)' - Checks if the direction chosen to move is a valid location based on world border (3x3 grid square).
- 'getName(_player:Player*): std::string' -  Returns the name of a given location.
- 'getNPC(index:int): NPC*' -  Returns a specified NPC from a list within a given location.
- 'getRecipe(index:int*): CraftingRecipe*' -  Returns a specified recipe from a list within a given location.
- 'getInventoryt(_player:Player*): Inventory&' -  Returns a reference to the inventory (resources) of a given location.
- 'getMob(index:int): Mob*' - Returns a specified Mob from a list within a given location..
- 'numOfNPC(): int' -  Returns the number of NPCs in a given location.

### Village
**Responsiblility:** Generalized reference for 'village' location.
**Key Methods:**
- None

### Field
**Responsiblility:** Generalized reference for 'field' location.
**Key Methods:**
- None

### Mountain
**Responsiblility:** Generalized reference for 'mountain' location.
**Key Methods:**
- None

### NPC (Abstract)
**Responsiblility:** Tracks the name and type of each NPC.
**Key Methods:**
- 'getName(): std::string' - Returns NPC name;
- 'getType(): std::string' - Returns NPC type;

### ShopNPC
**Responsiblility:** Contains the inventory of a given shop NPC.
**Key Methods:**
- 'sellItem(player:Player&,item:Item&)' - Removes item from player inventory and player gains something.

### HelperNPC
**Responsiblility:** Gives unique dialoge that hints how to solve the current puzzle.
**Key Methods:**
- 'giveHing(): std::string' - Allows the player to request a hint from the HelperNPC.

### Item (Abstract)
**Responsiblility:** Tracks item names and types.
**Key Methods:**
- 'getName(): std::string' - Returns item name;
- 'getType(): std::string' - Returns item type;

### Material
**Responsiblility:** Represents a type of material used for crafting or trading. 
**Key Methods:**
- None

### Weapon
**Responsiblility:** Gives the player bonus damage during encounters. Amount is based on the weapon. 
**Key Methods:**
- None

### Food
**Responsiblility:** Refills the player hunger bar when used. Amount replenished varies on the food.
**Key Methods:**
- 'getHunger(): int' - Returns the players hunger.
- 'setHunger(value:int)' - Sets the players hunger.

### ItemCollection
**Responsiblility:** Contains a list of all items and acts as the origin while everything either copies or points to its contents.
**Key Methods:**
- 'getSpecifiedItem(name:std::string): Item*' - Returns a pointer to a specified item.

### Inventory
**Responsiblility:** A vector containing the players items and materials.
**Key Methods:**
- 'add(_item:Item*,count:int)' - Adds an amount of an item to the player inventory.
- 'remove(_item:Item,count:int)' - Removes an amount of an item from the player inventory.
- 'has(_item:Item*,count:int): bool' - Verifies (returns true) if players inventory contains a specified item.
- 'size(): int' - Returns the total number of items within player inventory.

### Mob
**Responsiblility:** Represents an enemy entity. Manages the mobs name, health, damage, and droppable inventory.
**Key Methods:**
- 'attackPlayer(_player:Player)' - Deals damage to the player.
- 'takeDamage(damage:int)' - Reduces the mobs health.
- 'isDead(): bool' - Verifies (returns true) if the mobs health is zero.

### Crafting Recipe
**Responsiblility:** Contains a list of items the player can craft in exchange for materials from inventory. 
**Key Methods:**
- 'canCraft(_inventory:Inventory): bool' - Verifies (returns true) if player has enough resources to craft a specified item.
- 'craft(_inventory:Inventory)' -  Adds item into player inventory in echange for materials from inventory.