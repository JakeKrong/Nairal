#pragma once
enum class ObstacleTypes {
	Ground,
	Moving,
	Meteor,
	Canonball
};

struct Obstacle {
	ObstacleTypes type{ ObstacleTypes::Ground };
	float damage{ 1.0f };
	bool deadly{ false };
};