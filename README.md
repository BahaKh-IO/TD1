# Snake.cpp

Simple console Snake game implemented in a single file: `snake.cpp`.

What this is

- Minimal, beginner-friendly Snake clone that runs in a Windows console.
- Uses `conio.h` for keyboard input and `windows.h` for `Sleep()` and `system("cls")`.

Controls

- W / A / S / D — move Up / Left / Down / Right
- X — quit the game

Build & run

- Recommended: use the included VS Code task "C/C++: gcc.exe build active file" (configured for MSYS2 UCRT64). Open `snake.cpp` and run the Build task.

- Manual (PowerShell + MSYS2 UCRT64 gcc):

  C:/msys64/ucrt64/bin/gcc.exe -fdiagnostics-color=always -g snake.cpp -o snake.exe; ./snake.exe

Notes

- This project is Windows-specific because it relies on `conio.h` and `windows.h`.
- If the snake doesn't move on start, edit `dir` and `Sleep()` in `snake.cpp` to tweak starting direction and game speed.
- The source is intentionally simple so you can extend it (add walls, scoring, levels, or nicer rendering).
