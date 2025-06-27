#pragma once
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <unordered_map>
#include <string>
#include <deque>

class SoundManager {
public:
	sf::Sound& Play(const std::string& path);
	void CleanupStopped();
	void StopAll ();

private:
	std::unordered_map<std::string, sf::SoundBuffer> m_Buffers;
	std::deque<sf::Sound> m_Sounds;
};