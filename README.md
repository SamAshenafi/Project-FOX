[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/UCqQgtmZ)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=11705479&assignment_repo_type=AssignmentRepo)
# CSC3380 Object Oriented Programming using C++ (Fall 2023) - Course Project

See here for more information about the [course project][project]

[project]: https://teaching.hkaiser.org/fall2023/csc3380/assignments/project.html

# Table of Contents
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
Christian Che | Art Lead (backgrounds, sprites, music, & sfx) | 1
Sam Ashenafi | | 1
Robert Smith | | 1
Ryan Trinh | | 1


## TODO
> To keep track of what need to be done
- [ ] Milestone 1
    - [X] Introduction/Description (1-2 paragraph)
        - problem & solution
        - technologies used in project
            - C++ (obviously)
            - if we do GUI
                - SDL 2? (if we do GUI)
                - Drawing software for sprites
                    - pixel art? (Aseprite)
                    - normal (GIMP/CSP/Photoshop)
            - Other?
    - [X] Features
        - [X] Core (3/2+)
            - Dialogue, the back-&-forth
            - GUI
            - Player Input
        - [X] Viable (3/2+)
            - Turn Based Combat System
            - Inventory System
            - Tile-Based Movement System
        - [X] Strech (3/2+) (optional)
            - Multiple Characters Party
            - Save System
            - Expansive World
            - Side Quests System
    - [X] Team name
    - [ ] Members' role & responsibility for each milestone (can be updated later) (WIP) (3/6 filled out their role)
        - Leadership for each milestone (goes to Alton by default)
    - [ ] User Stories (0/1+)
        - We want to create a fun & engaging adventure game?
    - [X] Continuity of Operations Plan (COOP) (1-2 paragraph)
        - We communicate through group chat or the group's server channel in discord
        - [X] What if a member is unable to meet in person/unavailable (temporary or permanently)?
            - [X] temporary
                - cannot attend meeting -> check meeting notes
            - [X] permanently - the work will be split to other member evenly
    - [ ] Project plan (will get updated in milestone 2) (WIP)
        - For each task
            - dependencies
            - level of effort
            - start & completion dates

## Drafting Area
> A place for your ideas

So here's some topics about for our game to get us started.
Feel free to add more, edit them, or answer them here or on Discord

### Questions
- Will it be CLI or GUI?
    - CLI means the user/player can only interact using text
        - pros: simple, easy
        - cons: limiting, no art, hard/unintuitive to interact
        - i (chris) can do some basic GUI (buttons & basic info display)
        w/ React & Tauri if we decided to do CLI
    - GUI means
        - pros: more mechanics/interactions, more intuitive UI, art, maybe even sound
        - cons: difficult
        - i can do the art for the project if we can use sprite
- What is the general Theme/Story? (we can change this later on)

### General Mechanics
- Dialog (back & forth between the player & the game)
- Dialog Choice (player should have multiple options to reply back)

### Optional Mechanics
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


## Resource
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


