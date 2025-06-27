#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>


class TextureManager {
public:
    sf::Texture& Load(const std::string& path);

private:
    std::unordered_map<std::string, sf::Texture> m_Textures;
};