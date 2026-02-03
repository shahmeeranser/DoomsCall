cmake_minimum_required(VERSION 3.15)

# 1. Project Name
project(DoomsCall VERSION 1.0.0 LANGUAGES CXX)

# 2. Force C++ Standard (Keeps you in sync with modern VS 2022)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 3. AUTOMATIC SFML DOWNLOAD (FetchContent)
# This ensures you have the exact same version as your friend (2.6.1).
# It downloads once, then saves it forever.
include(FetchContent)
FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG        2.6.2
)
FetchContent_MakeAvailable(sfml)

# 4. FIND SOURCE FILES
# Automatically finds every .cpp file in the folder.
file(GLOB SOURCES "*.cpp")

# 5. CREATE THE GAME
add_executable(DoomsCall ${SOURCES})

# 6. SETUP INCLUDES
target_include_directories(DoomsCall PRIVATE . include)

# 7. LINK LIBRARIES
target_link_libraries(DoomsCall PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)

# 8. FIX THE "ASSET LOADING" ERROR
# This automatically copies your 'resources' folder into the build folder
# every time you change a file.
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})