
The Game of ChamberCrawler3000
The video game ChamberCrawler3000 (CC3k), which is a simplified rogue-like (a genre of video game based upon the game Rogue1 - https: //en.wikipedia.org/wiki/Rogue_(video_game)).A game of CC3k consists of a board 79 columns wide and 30 rows high (5 rows are reserved for displaying information). 

Game play is as follows: the player character moves through a dungeon and slays enemies and collects treasure until reaching the end of the dungeon (where the end of the dungeon is the 5th floor). A dungeon consists of different floors that consist of chambers connected with passages. In our simplification, each floor will always consist of the same 5 chambers connected in exactly the same way (outlined below).
1 Some DefinitionsDefinition 1: A character is a person/animal/thing in the game of CC3k. This can be either the player character (PC), who is controlled by the player of the game, or non-playable characters, who are strictly enemies in CC3k.
Definition 2 : An item is something the player character can pick up or use. In CC3k, this is either gold or potions. Potions offer potentially positive and negative effects to the player character.
Definition 3: A chamber is an individual room in the game of CC3k. Chambers are connected by passages.
Definition 4: A floor in CC3k is a predefined configuration of 5 chambers with connecting passageways. Figure 1 depicts an empty floor. Note that the configuration is the same for every floor in a game of CC3k.
Definition 5: Health Points (HP) is the representation of a character’s health (both enemies and the player character). When a character’s HP reaches 0, they are slain. For an enemy this means that they are removed from the floor and a tidy sum of gold is given to the player character. When the player character has 0 HP then the current game ends.
Definition 6 : Attack (Atk) is the representation of a character’s strength. This is how hard a character can hit another character. Though in CC3k conflict is solely between the player character and non-playable characters.
Definition 7 : Defence (Def) is the representation of a character’s toughness. This is how hard a character can be hit by another character.
Definition 8: A cell is either a wall, floor tile, doorway, or passage.
Definition 9: A 1-block radius denotes the 8 cells adjacent to the character or item.

2 System Components2.1 Player CharacterThe default player character race is a shade that has starting stats (125 HP, 25 Atk, 25 Def). 
However, players have the option of choosing an alternate (but no less heroic) race: 

drow (150 HP, 25 Atk , 15 Def, all potions have their effect magnified by 1.5), 
vampire (50 HP, 25 Atk, 25 Def, gains 5 HP every successful attack and has no maximum HP), 
troll (120 HP, 25 Atk, 15 Def, regains 5 HP every turn; HP is capped at 120 HP), 
goblin (110 HP, 15 Atk, 20 Def, steals 5 gold from every slain enemy). 
In our game board, the player character is always denoted by the ‘@’ symbol.2.2 EnemiesEnemies are the mortal foes of our illustrious player character. 
Enemies can be one of 
human (140 HP, 20 Atk, 20 Def, drops 2 normal piles of gold), 
dwarf (100 HP, 20 Atk, 30 Def, Vampires are allergic to dwarves and lose 5HP rather than gain), 
elf (140 HP, 30 Atk, 10 Def, gets two attacks against every race except drow), 
orcs (180 HP, 30 Atk, 25 Def, does 50% more damage to goblins), 
merchant (30 HP, 70 Atk, 5 Def), 
dragon (150 HP, 20 Atk, 20 Def, dragons are stationary and always guard a treasure hoard.), 
and halfling (100 HP, 15 Atk, 20 Def, has a 50% chance to cause the player character to miss in combat, i.e. takes priority over player character’s ability to never miss).
By default, merchants are neutral to all parties. However, merchants can be attacked and slain by the player character. Attacking or slaying a Merchant will cause every Merchant from that point forward to become hostile to the player character (and will attack them if they pass within a one block radius).
Dragons always spawn in a one block radius of its dragon hoard(see Treasure). That is, if a dragon hoard is spawned then a dragon is spawned.Upon their demise, any enemy that is not a dragon, human, or merchant will drop either a small pile or normal pile of gold (discussed below). This gold is immediately added to the player character’s total.
Enemies (except dragons, who are stationary) move randomly 1 floor tile at a time. An enemy will never leave the room it was spawned (created) in. 

Enemies are denoted on the map as follows: (H)uman, d(W)arf, (E)lf, (O)rc, (M)erchant, (D)ragon, Half(L)ing.2.3 Items
2.3.1 PotionsIn the game of CC3k, there is only one type of usable item: a potion. Potions are of two types: positive and negative. Potions can provide the player character with positive and negative bonuses as outlined below. Regardless of the potion itself, all potions are denoted on the map with a P. A player may not hold any potions. 
Positive Potions:• Restore health (RH): restore up to 10 HP (cannot exceed maximum prescribed by race)• Boost Atk (BA): increase ATK by 5• Boost Def (BD): increase Def by 5Negative Potions:• Poison health (PH): lose up to 10 HP (cannot fall below 0 HP)• Wound Atk (WA): decrease Atk by 5• Wound Def (WD): decrease Def by 5
The effects of RH and PH are permanent while the effects of all other potions are limited to the floor they are used on. For example, using a BA potion will only boost the player character’s Atk until the beginning of the next floor.Note that the PC’s Atk and Def will never drop below 0.2.3.2 TreasureTreasure in CC3k consists only of gold. Gold can be in several types of piles: small (value 1), normal (value 2), merchant hoard (value 4), and dragon hoard (value 6). A dragon hoard can only be picked up once the dragon guarding it has been slain. Gold, regardless of type, is denoted by ‘G’ on the map.
A merchant hoard is dropped upon the death of a merchant. Gold dropped by a merchant (merchant hoard, value 4) or a human (2 normal piles, value 2x2=4) is picked up only when the PC walks over it.2.4 Floors20 enemies are spawned per floor (this number does not include dragons). Every chamber is equally likely to spawn any particular monster (similarly for floor tiles).When the PC attempts to move on to a stairway, the next level is instead generated and displayed, with the PC spawning in a random position on the new level.2.5 Combat
By default, all enemies except for Merchants and Dragons are hostile to the player character. If the player character enters within a 1 block radius of any hostile enemy, they will attempt to attack the player character (even before the player character has had a chance to attack). 
Dragons are considered hostile when the player is next to (read: in the 1 block radius of) its dragon hoard or itself. This means that a Dragon might attack even if the player is not next to the Dragon, but because it is next to a dragon hoard. If the player character is not within a 1 block radius of the enemy then it will resume random movement (as previously described).Combat is resolved as follows: Enemies will auto-attack players given the previously specified criteria, however, there is a 50% chance their attack misses. 
The player character has the option of attacking any of the 8 squares adjacent to them and within in a 1 block radius. The PC never misses. Recall, that the PC has initiative and always attacks first.
Damage is calculated as follows: 
Damage(Def ender) = ceiling((100/(100+ Def(Defender)))/ Atk(Attacker)), where Attacker specifies the attacking character (enemy or PC) and defender specifies the character being attacked. Thus, in a single round a character can be both an attacker and a defender.
3 Display
The display of CC3k is relatively simple, Figure 1 depicts an empty board. Walls are denoted by ‘|’ and ‘ ’, doorways by ‘+’, and passages by ‘#’. Floor tiles that can be walked upon are denoted by ‘.’. Chambers are denoted by the smaller polygons inside the larger rectangle.

4 Command Interpreter
Initially, the game will demand the player enter one of the specified races or quit. Entering ‘q’ or EOF (e.g. Ctrl-D) at the race prompt will cause the program to terminate. Supplying a valid race selection (below) will start that game using that race. Other values will be ignored.
The following commands can be supplied to your command interpreter:• no,so,ea,we,ne,nw,se,sw: moves the player character one block in the appropriate cardinal direction.
• u <direction>: uses the potion indicated by the direction (e.g. no, so, ea).
• a <direction>: attacks the enemy in the specified direction, if the monster is in the immediately specified block (e.g. must be one block north of the @).
• s, d, v, g, t: specifies the race the player wishes to be when starting a game.
• f: stops enemies from moving until this key is pressed again.
• r: restarts the game. All stats, inventory, and gold are reset. A new race should be selected.
• q: allows the player to admit defeat and exit the game.5 Ending the Game and Scoring
A game session ends in one of the following ways: the player character reaches the stairs on floor 5, the player character’s health reaches 0, the player restarts the game or quits.


