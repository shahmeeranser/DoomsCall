Here is a complete, professional **`README.md`** file that you can add to your project root.

This documentation is designed to help anyone (using **VS Code on Linux** or **Visual Studio on Windows**) download your code and start working immediately without breaking anything.

You can copy-paste this directly into a file named `README.md`.

---


# DoomsCall - Developer Guide

Welcome to the development repository for **DoomsCall**. Please follow these instructions to set up your environment, build the game, and contribute correctly.

## 📂 Project Structure

It is critical that you follow this folder structure to ensure the game works on everyone's machine.

```text
DoomsCall/
├── CMakeLists.txt       <-- Build Script (DO NOT DELETE)
├── main.cpp             <-- Source Code
├── option.txt           <-- User Settings (Resolution, FPS)
└── resources/           <-- ALL ASSETS GO HERE
    ├── images/          <-- .png files
    ├── audio/           <-- .wav / .ogg files
    └── fonts/           <-- .ttf files

```

---

## 🛠️ Setup Instructions

### Option A: Visual Studio Code (Linux / Windows)

*Recommended for cross-platform development.*

**Prerequisites:**

1. Install **VS Code**.
2. Install the **C/C++ Extension** and **CMake Tools Extension**.
3. **Linux:** Install GCC and dependencies:
`sudo apt-get install build-essential libgl1-mesa-dev libudev-dev libopenal-dev libvorbis-dev libflac-dev libfreetype6-dev`
4. **Windows:** Install MinGW or a Visual Studio Compiler.

**How to Build & Run:**

1. Open the `DoomsCall` folder in VS Code.
2. Press `Ctrl + Shift + P` and select **CMake: Configure**.
* *Select your compiler (e.g., GCC 11.4 or Visual Studio Community).*


3. Wait for CMake to download SFML (approx. 2-5 mins on first run).
4. **To Build:** Press **F7** (or click "Build" in the bottom bar).
5. **To Run:** Press **Shift + F5** (or click the Play button).

---

### Option B: Visual Studio 2022 (Windows Only)

*Best for Windows-only developers.*

**Prerequisites:**

1. Install **Visual Studio 2022**.
2. During installation, ensure **"Desktop development with C++"** is checked.

**How to Build & Run:**

1. Open Visual Studio.
2. Select **"Open a Local Folder"** (Do NOT look for a .sln file).
3. Select the `DoomsCall` folder.
4. Visual Studio will detect `CMakeLists.txt` and automatically configure the project.
* *Check the "Output" window at the bottom to see progress.*


5. Select `DoomsCall.exe` from the "Startup Item" dropdown (green play button at the top).
6. Press **F5** to Build and Run.

---

## ⚠️ Important Contribution Rules

### 1. Asset Management (CRITICAL)

**Do NOT put images, sounds, or fonts in the root folder.**

* ❌ `DoomsCall/player.png` (WRONG - Will not be copied)
* ✅ `DoomsCall/resources/player.png` (CORRECT - CMake handles this automatically)

**In your Code:**
Always load assets using the `resources/` prefix:

```cpp
// Correct way to load
texture.loadFromFile("resources/player.png");

```

### 2. The `option.txt` File

This file stores local user settings (Resolution, FPS).

* Keep it in the **root directory** (next to `main.cpp`).
* Do not hardcode these values in C++; read them from the file.

### 3. File Formats

* **Images:** Use `.png` (Avoid `.ico` or `.bmp` as they cause issues on Linux).
* **Audio:** Use `.wav` for sound effects, `.ogg` for music.

---

## 🐛 Troubleshooting

**"Fatal Error: cannot find SFML/..."**

* Make sure you are opening the **Folder** in your IDE, not just a single file.
* Wait for the CMake Configuration step to finish downloading SFML.

**"Segmentation Fault" or "Crash on Start"**

* Check the console output. It usually means an image failed to load.
* Did you check if the file is inside `resources/`?
* Did you spell the filename correctly? (Linux is case-sensitive: `Player.png` ≠ `player.png`).

---

### 📝 Final Note for Git Users

Please add the following lines to your `.gitignore` file to avoid uploading junk files:

```gitignore
build/
out/
.vscode/
.vs/
*.exe
*.o
CMakeCache.txt

```

