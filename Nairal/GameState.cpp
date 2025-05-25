#include "GameState.h"
#include <memory>

class GameStateManager {
private:
    std::unique_ptr<GameState> currentState;

public:
    void SetState(std::unique_ptr<GameState> newState) {
        currentState = std::move(newState);
    }

    void Update(float deltaTime) {
        if (currentState) currentState->Update(deltaTime);
    }

    void Render() {
        if (currentState) currentState->Render();
    }

    void OnEnter() {
        if (currentState) currentState->OnEnter();
    }

    void OnExit() {
        if (currentState) currentState->OnExit();
    }
};
