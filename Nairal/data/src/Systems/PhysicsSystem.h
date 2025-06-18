#pragma once
#include "System.h"
#include <SFML/System/Time.hpp>

class PhysicsSystem :public System{
public:
	void Update(float deltaTime);

private:
	const float GRAVITY = 980.0f; // pixels per second squared
	const float GROUND_Y = 500.0f;
};