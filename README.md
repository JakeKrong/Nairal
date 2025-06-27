# Nairal: Dodge This! #
![Nairal Showcase](https://github.com/user-attachments/assets/e77e6b3b-9afb-493e-b946-5613592d5d39)

************
Description: 
************
A simple 2D dodge-and-survive game built with C++ and SFML, featuring systems such as a custom Entity-Component-System (ECS), sprite animation, audio, and escalating difficulty.

# Gameplay
You control a small character dodging barrages of meteors and birbs. The longer you survive, the faster and harder the game becomes.

- Move left/right with **A/D**
- Jump with **Spacebar**
- Avoid obstacles
- Survive as long as possible to increase your score

## Build Instructions ##

1. Make sure you have SFML 3.0.0 installed on your system
2. Create a build directory: `mkdir build && cd build`
3. Run CMake: `cmake ..`
4. Build the project: `make` (or `cmake --build .`)
5. Run the executable: `./Nairal`

## Features Implemented

### ECS Architecture
- **Entity Manager**: Handles entity creation/destruction and signatures
- **Component Manager**: Type-safe component storage with efficient memory layout
- **System Manager**: Manages system registration and entity filtering
- **World**: Unified interface for ECS operations

### RAII & Smart Pointers
- Uses `std::unique_ptr` and `std::shared_ptr` throughout
- Custom `CreateRef` and `CreateScope` helper functions
- Automatic memory management for all systems and components

### Components
- **Transform**: Position, scale, rotation
- **Physics**: Velocity, acceleration, gravity
- **Renderable**: Visual representation
- **Collider**: Collision detection
- **Player**: Player-specific properties
- **Obstacle**: Obstacle types and damage
- **Lifetime**: Automatic entity destruction

### Systems
- **InputSystem**: Handles keyboard input for player movement
- **PhysicsSystem**: Applies gravity and updates positions
- **CollisionSystem**: Detects collisions between entities
- **RenderSystem**: Renders all visible entities
- **LifetimeSystem**: Manages entity lifetimes
- **AnimationSystem**: Manage entities animation frames

### Game States
- **PlayingState**: Main gameplay loop
- **GameOverState**: Game over screen with restart option
- **StateManager**: Manages state transitions

### Progressive Difficulty
- Spawn rate increases over time
- Different obstacle types unlock as time progresses
- Obstacle speed increases with game time
- Score system based on survival time
