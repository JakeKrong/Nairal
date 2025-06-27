#include "TextureManager.h"
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <iostream>

sf::Texture& TextureManager::Load(const std::string& path) {
    auto it = m_Textures.find(path);
    if (it != m_Textures.end()) {
        return it->second;
    }

    sf::Texture tex;
    if (!tex.loadFromFile(path)) {
        std::cerr << "[TextureManager] Failed to load texture: " << path << "\n";
    }

    return m_Textures[path] = std::move(tex);
}