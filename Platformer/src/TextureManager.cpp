#include "TextureManager.h"

TextureManager::~TextureManager()
{
	// Delete all the Textures in the container
	for (auto& pair : m_textures) delete pair.second;

	// Clear the map container
	m_textures.clear();
}

bool TextureManager::addTexture(string key, string filename)
{
	// Check if the file has already been loaded
	if (m_textures.find(key) != m_textures.end()) return false;

	// Attempt to load the texture
	Texture tmp;
	if (!tmp.loadFromFile(filename)) return false;

	// Texture succesfully loaded - add to Texture container
	m_textures[key] = new Texture(tmp);
	return true;
}

Texture* TextureManager::getTexture(string key) const
{
	// Look for the Texture in the container
	auto it = m_textures.find(key);

	// Texture found - return the second stored value (i.e. the value in the map, not the key)
	if (it != m_textures.end()) return it->second;

	// Texture not found, return nullptr
	return nullptr;
}
