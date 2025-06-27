#pragma once
#include "../Systems/System.h"

class AnimationSystem:public System {
public:
	void Update(float deltaTime);
};