add_executable(Nairal
  "data/src/main.cpp" "data/src/dump.cpp" "data/src/Core/Types.h" "data/src/Core/EntityManager.cpp" "data/src/Core/EntityManager.h" "data/src/Game/Game.cpp" "data/src/Core/ComponentManager.h"  "data/src/Systems/System.h" "data/src/Core/World.h" "data/src/Core/World.cpp" "data/src/Components/Transform.h"  "data/src/Components/Component.h" "data/src/Systems/CollisionSystem.h" "data/src/Systems/ColliderSystem.cpp" "data/src/Systems/RenderSystem.h" "data/src/Systems/RenderSystem.cpp" "data/src/Systems/LifetimeSystem.h" "data/src/Systems/LifetimeSystem.cpp" "data/src/Game/StateManager.h")

target_link_libraries(Nairal PRIVATE
  sfml-graphics
  sfml-window
  sfml-system
)
