#pragma once

#include "GameState.h"
#include <memory>

class GameStateManager {
private:
	std::unique_ptr<GameState> currentState;

public:
	void ChangeState(std::unique_ptr<GameState> newState) {
        if (currentState) currentState->OnExit();
        currentState = std::move(newState);
        if (currentState) currentState->OnEnter();
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
