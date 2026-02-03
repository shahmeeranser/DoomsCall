THIS IS A GAME PROJECT THAT I AM WORKING ON!

it uses SFML library and C++
no game engine is used

```markdown
# ⚔️ DoomsCall

## 🛠️ Prerequisites

Before you start, ensure you have the necessary tools installed.

### 🐧 For Linux (VS Code)

Run this command in your terminal to install the compiler, CMake, and SFML dependencies:

```bash
sudo apt-get update
sudo apt-get install build-essential g++ cmake libgl1-mesa-dev libudev-dev libopenal-dev libvorbis-dev libflac-dev libfreetype6-dev

```

### 🪟 For Windows (Visual Studio)

1. Install **Visual Studio 2022** (Community Edition is free).
2. During installation, check the box: **"Desktop development with C++"**.

---

## 🚀 How to Run: Visual Studio 2022 (Windows)

*Recommended for Windows-only developers.*

**Step 1: Open the Project**

1. Open Visual Studio.
2. Click **"Open a Local Folder"** (Do NOT click "Open Project/Solution").
3. Select the `DoomsCall` folder.

**Step 2: Configure**

1. Wait a few minutes. Visual Studio will automatically find `CMakeLists.txt`.
2. Look at the **Output Window** at the bottom. It will say "Downloading SFML..."
3. Wait until you see "CMake generation finished."

**Step 3: Run**

1. Locate the **Green Play Button** at the top toolbar.
2. If it says "Select Startup Item", click the dropdown and choose **DoomsCall.exe**.
3. Press **F5** to Build and Run.

---

## 🚀 How to Run: VS Code (Linux / Windows)

*Recommended for Linux users or lightweight setups.*

**Step 1: Setup Extensions**

1. Install the **C/C++** extension (Microsoft).
2. Install the **CMake Tools** extension (Microsoft).

**Step 2: Configure**

1. Open the `DoomsCall` folder in VS Code.
2. Press `Ctrl + Shift + P` and type: **CMake: Configure**.
3. **Select a Kit:**
* **Linux:** Choose `GCC 11.x` (or similar).
* **Windows:** Choose `Visual Studio Community Release`.



**Step 3: Build & Run**

1. **Build:** Press **F7** (or click "Build" in the bottom status bar).
* *Note: The first time will be slow as it downloads SFML.*


2. **Run:** Press **Shift + F5** (or the Play button).

---

## ❓ Troubleshooting

### 1. "Segmentation Fault" or "Failed to load image"

* **Cause:** The game cannot find an asset file.
* **Fix A:** Did you put the file inside the `resources/` folder?
* **Fix B:** Check your code paths.
* ❌ `texture.loadFromFile("player.png");`
* ✅ `texture.loadFromFile("resources/player.png");`


* **Fix C:** **Linux is Case-Sensitive!**
* `Resources/Player.png` is NOT the same as `resources/player.png`. Check your spelling.



### 2. "Fatal Error: Cannot find SFML/Graphics.hpp"

* **Cause:** CMake hasn't finished downloading SFML yet.
* **Fix:**
1. Ensure you have an internet connection.
2. In VS Code, run command: **CMake: Delete Cache and Reconfigure**.
3. Wait for the download to finish before building.



### 3. "Ninja not found" (Linux)

* **Cause:** Missing build tool.
* **Fix:** Run `sudo apt-get install ninja-build`.

---

## 📝 Contribution Rules

* **Git:** We use a custom `.gitignore`. **Do not upload** the `build/` folder, `.vs/`, or `.vscode/`.
* **Files:** Do not upload `.sln` or `.vcxproj` files. CMake generates them automatically.
* **Icons:** Please convert `.ico` files to `.png` to prevent crashes on Linux.

```

```