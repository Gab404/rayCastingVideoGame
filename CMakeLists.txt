cmake_minimum_required(VERSION 3.23)
project(rayCastingVideoGame C)

set(CMAKE_C_STANDARD 99)

add_executable(rayCastingVideoGame src/main.c src/createGraphe.c src/dijkstra.c src/file.c src/display.c src/free.c src/game.c src/getNumNpc.c src/gun.c src/handleError.c src/loadMap.c src/opps.c src/pauseMenu.c src/player.c src/quickSort.c src/raycasting.c src/loadTexture.c)

INCLUDE_DIRECTORIES(./includes/)

target_link_libraries(rayCastingVideoGame -lm -lalleg44 -lmingw32 -lwinmm)