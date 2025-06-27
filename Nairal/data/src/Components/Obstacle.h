#pragma once
enum class ObstacleTypes {
	Ground,
	Moving,
	Meteor,
	Cannonball
};

struct Obstacle {
	ObstacleTypes type{ ObstacleTypes::Ground };
	float damage{ 1.0f };
	bool deadly{ false };
};