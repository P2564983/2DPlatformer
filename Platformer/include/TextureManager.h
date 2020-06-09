#pragma once

#include <map>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class TextureManager
{
private:
	map<string, Texture*> m_textures; //!< Texture container of all possible tetxures

public:
	~TextureManager(); //!< Destructor
	bool addTexture(string key, string filename); //!< Add a texture to the manager
	Texture* getTexture(string key) const; //!< Retrieve a texture in the manager based on key value
};