#include "AnimationSystem.h"
#include "../Components/Renderable.h"
#include "../Components/Transform.h"
#include "../Core/World.h"

void AnimationSystem::Update(float deltaTime) {
	if (!m_World) return;

	for (auto entity : m_Entities) {
		auto& renderable = m_World->GetComponent<Renderable>(entity);
		//std::cout << "Animating entity frame: " << renderable.currentFrame << "\n";
		if (!renderable.animated || renderable.totalFrames <= 1)
			continue;

		renderable.timeSinceLastFrame += deltaTime;

		if (renderable.timeSinceLastFrame >= renderable.frameTime) {
			renderable.currentFrame = (renderable.currentFrame + 1) % renderable.totalFrames;
			renderable.textureRect = {
				{renderable.currentFrame * renderable.frameWidth, 0},
				{renderable.frameWidth, renderable.frameHeight}
			};
			renderable.timeSinceLastFrame = 0.0f;
		}
	}

}