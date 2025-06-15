add_executable(Nairal
  "data/src/main.cpp" "data/src/dump.cpp" "data/src/Core/Types.h" "data/src/Core/EntityManager.cpp" "data/src/Core/EntityManager.h" "data/src/Game/Game.cpp" "data/src/Core/ComponentManager.h"  "data/src/Systems/System.h" "data/src/Core/World.h" "data/src/Core/World.cpp" "data/src/Components/Transform.h" )

target_link_libraries(Nairal PRIVATE
  sfml-graphics
  sfml-window
  sfml-system
)
