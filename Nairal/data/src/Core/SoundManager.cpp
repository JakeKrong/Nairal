#include "SoundManager.h"
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

sf::Sound& SoundManager::Play(const std::string& path) {
	//Load buffer if not already loaded
	if (m_Buffers.count(path) == 0) {
		sf::SoundBuffer buffer;
		if (!buffer.loadFromFile(path)) {
			std::cerr << "[SoundManager] Failed to load : " << path << "\n";
		}
		m_Buffers[path] = std::move(buffer);
	}

	m_Sounds.emplace_back(m_Buffers[path]);
	return m_Sounds.back();
}

void SoundManager::CleanupStopped() {
	while (!m_Sounds.empty() && m_Sounds.front().getStatus() == sf::SoundSource::Status::Stopped) {
		m_Sounds.pop_front();
	}
}

void SoundManager::StopAll() {
	for (auto& s : m_Sounds) {
		s.stop();
	}
}