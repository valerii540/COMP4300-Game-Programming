cmake_minimum_required(VERSION 3.21)
project(Assignment_2)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment_2 main.cpp libs/json.hpp game-engine/Entity.h game-engine/components/CTransform.h game-engine/util/Vec2.cpp game-engine/util/Vec2.h game-engine/components/CCollision.h game-engine/components/CScore.h game-engine/components/CShape.h game-engine/components/CInput.h game-engine/components/CLifespan.h game-engine/Entity.cpp game-engine/EntityManager.cpp game-engine/EntityManager.h Game.cpp Game.h game-engine/Common.h game-engine/util/ConfigLoader.cpp game-engine/util/ConfigLoader.h)
target_link_libraries(Assignment_2 sfml-graphics sfml-audio)