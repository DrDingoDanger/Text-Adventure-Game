### Game
**Responsiblility:** The represents the game world as a whole. It manages the player, map, item win condition, ui/display, and game state.
**Key Methods:**
- 'start()' - Initializes the game.
- 'update()' - Updates the current game/world state.
- 'checkWin(): bool' - Verifies (returns true) if player has possesion of target win item.
- 'checkLose(): bool' - Verifies (returns true) if the players health or hunger have reduced to zero.
- 'endGame()' - Disables player and ends game. Rolls credits.

### ScreenDisplay
**Responsiblility:** Displays the game and its counterparts to the user. 
**Key Methods:**
- 'drawMap(out:ostream,map:WorldMap*)' - Displays the world map with the players location.
- 'displayChoices(out:ostream)' - Displays the players interactible choices to the user.

### UserInput
**Responsiblility:** Translates user input into player actions and movement.
**Key Methods:**
- 'moveDirection(): string' - Translates orthongonal input into a movement string for the player. 
- 'playerAction(): int' - Use specified player actions and world interactions. Ex, "buy from store" or "view inventory".
- 'pressEnter()' - Confirmation input before continuing specified actions or scenarios.

### Player
**Responsiblility:** Represents the player enitity. Manages player stats, crafting, buying, inventory, and location.
**Key Methods:**
- 'move(_direction:string)' - Updates the position of the player a location. Based on the movement string.
- 'takeDamage(damage:int)' - Reduces health bar. Based on damage source.
- 'eat(_food:Food)' - Allows the player to eat a food item.
- 'craft(recipe:CraftingRecipe)' - Creates item using materials from inventory.
- 'Buy(_item:Item,shop:ShopNPC)' - Transfers item from shop NPC to player.

### WorldMap
**Responsiblility:** Contains a list of locations the player can travel to.
**Key Methods:** 
- None

### Location (Abstract)
**Responsiblility:** Tracks the resources, NPC's, recipes, and entounter rate of a set location in the world.
**Key Methods:**
- 'enter(_player:Player)' -  Allows the player to enter a given location.
- 'runEncounter(_player:Player,_mob:Mob): Mob' - Given the region encounter rate, determines if the player ecounters a Mob.
- 'canExit(_direction:string)' - Checks if the direction (world location) chosen is a valid location.

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
**Responsiblility:** Tracks the name and location of each NPC.
**Key Methods:**
- 'interact(_player:Player)' - Allows the player to interact with the given NPC.

### ShopNPC
**Responsiblility:** Contains the inventory and price of a given NPC.
**Key Methods:**
- 'buyItem(_player:Player,item:Item)' - Places item into player inventory in echange for materials.
- 'sellItem(_player:Player,_item:Item)' - Removes item from player inventory and gains materials.

### HelperNPC
**Responsiblility:** Gives unique dialoge that hints how to solve the current puzzle.
**Key Methods:**
- 'giveHing()' - Allows the player to request a hint from the HelperNPC.

### Item (Abstract)
**Responsiblility:** Tracks item names and their corresponding use.
**Key Methods:**
- 'use(_player:Player)' - Allows the player to utalize an items 'use' property.

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
- None

### Inventory
**Responsiblility:** Contains the players items and materials.
**Key Methods:**
- 'add(_item:Item,count:int)' - Adds an amount of an item to the player inventory.
- 'remove(_item:Item,count:int)' - Removes an amount of an item from the player inventory.
- 'has(_item:Item,count:int): bool' - Verifies (returns true) if players inventory contains a specified item.

### Mob
**Responsiblility:** Represents an enemy entity. Manages the mobs health, damage, and droppable inventory.
**Key Methods:**
- 'attackPlayer(_player:Player)' - Deals damage to the player. Based on mod type.
- 'takeDamage(damage:int)' - Reduces the mobs health. Based on player damage.

### Crafting Recipe
**Responsiblility:** Contains a list of items the player can craft in exchange for materials from inventory. 
**Key Methods:**
- 'canCraft(_inventory:Inventory): bool' - Verifies (returns true) if player has enough resources to craft a specified item.
- 'craft(_inventory:Inventory)' -  Adds item into player inventory in echange for materials from inventory.