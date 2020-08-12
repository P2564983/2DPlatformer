#pragma once

/*!
\file TextureManager.h
*/

#include <map>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

/*! \class TextureManager
\brief A texture storage container allowing for easy access to textures
*/
class TextureManager
{
private:
	map<string, Texture*> m_textures; //!< Texture container of all possible tetxures

public:
	/*!
	  \brief Destructor which deletes all the textures and empties the texture container
	*/
	~TextureManager();

	/*!
	  \brief Heloer method to insert a new texture into the manager
	  \param key A unique string identifying the texture
	  \param filename The directory path to the texture
	  \return A boolean indicating whether the texture was succesfully added
	  \see getTexture
	*/
	bool addTexture(string key, string filename);

	/*!
	  \brief Returns a texture from the texture container
	  \param key A unique string identifying the texture that was set in call to addTexture
	  \return A texture pointer to the texture requested or a nullptr if the texture could not be found (or does not exist)
	  \see addTexture
	*/
	Texture* getTexture(string key) const; //!< Retrieve a texture in the manager based on key value
};