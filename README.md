[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/UCqQgtmZ)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=11705479&assignment_repo_type=AssignmentRepo)
# CSC3380 Object Oriented Programming using C++ (Fall 2023) - Course Project

See here for more information about the [course project][project]

[project]: https://teaching.hkaiser.org/fall2023/csc3380/assignments/project.html

# Table of Contents
- [Game Design Document](./.github/game-design-document.md)
- [TODO](#todo)
- [Drafting Area](#drafting-area)
- [Resources](#resources)
    - [SDL2](#sdl-2)
    - [Helpful/Convenience Links](#helpfulconvenience-links)


## Team

### Team Name: Aang Gang

### Members
| Name | Role | Milestone |
|------|------|-----------|
Alton Dupre | Leader, Structure Management | 1
Blaire Newburger | Tile-Based Movement System | 1
Christian Che (ganhaque) | Art Lead (backgrounds, sprites, music, & sfx) & Planner | 1
Sam Ashenafi | Story Guidelines| 1
Ryan Trinh | Backend Dev | 1
Robert Smith | Backend Dev | 1

### Jobs
> Specific jobs/tasks to be done. A job can have multiple people doing it.

**Combat Prototype**
| Job | Who | Notes? |
|-----|-----|-------------|

**Movement Prototype**
| Job | Who | Notes? |
|-----|-----|-------------|
Room Tile Editor | Christian | Optional. A tool to generate a room's tilemap, instead of manually typing out the 2D array of the room's Tiles. It will be saved as a JSON file to be interpreted

**Arts**
| Job | Who | Notes? |
|-----|-----|-------------|
Narrative/Story | ? |
Dialogue | ? |
Art | Christian | 
SoundFX | Christian | 
OST | Christian? | 

## TODO
> To keep track of what need to be done
- [ ] Combat Prototype
- [ ] Movement Prototype
    - [ ] Optional: Room Tile Editor
- [ ] Art
    - [ ] Character Design/Concept Art
    - [ ] Character Spritesheet (Animation)
    - [ ] Ability animation
    - [ ] Ability Icons
    - [ ] UI Icons
    - [ ] Enemy Spritesheet
    - [ ] Room Background Image
- [ ] Music & Sounds
    - [ ] SFX
    - [ ] OST

## Drafting Area
> A place for your ideas

So here's some topics about for our game to get us started.
Feel free to add more, edit them, or answer them here or on Discord

### Options when it comes to developing a game in C++
- [SDL2 (tested)](https://wiki.libsdl.org/SDL2/FrontPage)
    - Pros:
        - There's tutorial on the basics
        - Found several games made w/ SDL2 w/ their source code available
    - Cons:
        - No game engine -> we will have to build the game from scratch, which includes:
            - Manually loading in & interpreting the texture/sprites/sounds
            - Manually implementing common game features such as TileMap, SpriteAnimation, Hitbox/Collision, etc.
        - This can be difficult considering our group's skill in C++ & limited amount of tutorials for SDL2
- [raylib (tested)](https://www.raylib.com/)
    - Work
    - Might be better than SDL2
    - Pros:
        - Less complicated compared to SDL 2
<!-- - [Gosu (not tested)](https://www.libgosu.org/cpp.html) -->
- Godot
    - There's 2 way to do C++ in Godot:
        - [GDExtension (attempted)](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html)
            - Pros:
                - Don't need to recompile the game engine after every changes to the code
                - Can build the game entirely in C++ (no gdscript)
            - Cons:
                - your editor might scream at you (file not found, etc.)
                - no tutorial except the example in the documentation
                - dll is platform specific (need a different dll for Windows, Linux, Mac)
                - need to carry the dll in the game folder
        - [C++ Custom Modules (not tested)](https://docs.godotengine.org/en/stable/contributing/development/core_and_modules/custom_modules_in_cpp.html)
            - Pros:
                - don't need dll for each platform
            - Cons:
                - Have to rebuild the game engine for every changes to the code
                - Need GDScript to use the module in the game engine (Not pure c++)


### Questions
- What is the general Theme/Story? (we can change this later on)

### Features
which one should we do? how will it be implemented?
- Navigation
    - move to new area -> something happen
- Quest System
- NPC System (player can actively choose to interact w/ NPC)
- Combat System
    - Enemy
    - Combat Statistics
        - HP
        - Attack Damage (AD)
        - Armor (Flat & %DMG Negation)
        - ...
    - Player Inventory
        - Equipment
        - Level/EXP?
        - Consumable/Items?
        - Undertale act/spare mechanic?


## Resources
> Convenience way to find help/inspiration outside of the group

### SDL 2
If we decided to do GUI, SDL 2 is an option to build our game engine from.

- [Official Website Installation Guide](https://wiki.libsdl.org/SDL2/Installation)

- [SDL 2 Tutorial by Lazyfoo](https://lazyfoo.net/tutorials/SDL/)
    - [Set up guide for Windows & Linux](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)
    - In-depth & up-to-date tutorial.
    - Provide source file for its codes.
    - @ganhaque if you need the Makefile or general help to build the tutorials' code

- [Game Engine using C++ SDL 2 Blog]https://www.gamedeveloper.com/blogs/how-to-make-your-own-c-game-engine

- [TwinklebearDev SDL 2 Tutorial](https://www.willusher.io/pages/sdl2/)
    - [Github lessons repo link](https://github.com/Twinklebear/TwinklebearDev-Lessons)
    - Short, basic
    - Old (last update to github repo is 3 years ago) tutorial

### Tools
[SFX Maker](https://sfxr.me/)

### Helpful/Convenience Links

[Class website](https://teaching.hkaiser.org/fall2023/csc3380/)


