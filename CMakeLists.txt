cmake_minimum_required(VERSION 3.15)
project(untitled13 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio)

find_package(Lua 5.4 REQUIRED)

# ---------------------------------------------------------------------------
add_executable(untitled13
        main.cpp
        Bus/EventBuss.cpp
        Player/Player.cpp
        Game.cpp
        Game.h
        Entities/Drawable.cpp
        Entities/Drawable.h
        Entities/Managers/EntityManager.cpp
        Entities/Managers/EntityManager.h
        Entities/Entity.cpp
        Entities/Entity.h
        Entities/Managers/ProjectileManager.cpp
        Entities/Managers/ProjectileManager.h
        LoadGame/loadSpells.cpp
        LoadGame/loadSpells.h
        Spells/Spells/allSpells/spellOne.cpp
        Spells/Spells/Spells.h
        Spells/Spells/allSpells/spellOne.h
        Entities/Projectiles/Projectiles.h
        Entities/Managers/GameEngineAPI.cpp
        Entities/Managers/GameEngineAPI.h
        Entities/Managers/Draw.cpp
        Entities/Managers/Draw.h
        Bus/GameEvents.h
        Bus/EventBuss.h
        Map/Map.cpp
        Map/Map.h
)

target_link_libraries(untitled13
        PRIVATE
        SFML::Graphics
        SFML::Audio
        ${LUA_LIBRARIES}
)

target_include_directories(untitled13 PRIVATE
        ${LUA_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/external/sol2/include   # ← new
)
