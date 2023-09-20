# Part 2 to Raylib Setup Tutorial

# For Windows (VSCode) (Window 10)
- Open the raylib project
- Use the terminal to `cd` into the project folder.
- To compile, run this in the terminal
```bash
mingw32-make all clean-object
```
- This should generate a `game.exe`
- You can probably make this easier (script file, task.json, etc.).

### Why use this instead of the previous tutorial way
- The Makefile is much simpler (basically my Linux Makefile with some modification)
    - This make it easier for me to change stuffs in the `Makefile`
    - For example, previous method only compile the `.cpp` file that you currently have open
    - I changed it to compile all `.cpp` file in the `src/` folder instead.
- Previously, you needed to copy both the `Makefile` & the `.vscode/` folder to make it work
    - Now you only need the Makefile (this tutorial folder has that Makefile).



# For Arch Linux
I separated my Makefile & made a script instead. To compile just do.
```bash
./compile.sh
```
