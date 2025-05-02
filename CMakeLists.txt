cmake_minimum_required(VERSION 3.20)

project(TICTACTOE24)
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_EXTENSIONS OFF)

# Ajouter les fichiers source
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp) 
add_executable(${PROJECT_NAME} ${SOURCES}) 
# Ajouter les fichiers d'en-tête au projet
target_include_directories(${PROJECT_NAME} PRIVATE src) 