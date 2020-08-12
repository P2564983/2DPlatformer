#pragma once

/*!
\file UserInterface.h
*/

#include "World.h"

/*! \struct TextBox
\brief A Textbox containing text and a box that surrounds the text
*/
struct TextBox : public Drawable
{
private:
	Text text; //!< The text to be shown
	RectangleShape textBox; //!< A rectangle box surrounding the text
	Vector2f padding; //!< Some padding/margin around the text

public:
	/*!
	  \brief Default constructor - it is a good idea to setup a Text and RextangleShape ahead of creating a TextBox with the properties you want (e.g. colour, font...)
	  \param _text The text inside this textbox (default value: empty Text() object)
	  \param _rectShape The rectangle shape around the text (default value: empty RectangleShape() object) - this rectangle shapes size is overridden but other properties are maintained (e.g. Fill Colour)
	  \param _position The top left position of the TextBox (default value: (0, 0))
	  \param _padding Some space around the text (default value (15, 15))
	*/
	TextBox(Text _text = Text(), RectangleShape _rectShape = RectangleShape(), Vector2f _position = Vector2f(0, 0), Vector2f _padding = Vector2f(15, 15));

	/*!
	  \brief Set the text string and then resize the TextBox based on the new text value
	  \param string The new string to set the text to
	*/
	void setText(const String& string);

	/*!
	  \brief Set the position of the TextBox - this also moves the position of the text 
	  \param pos The new position of the TextBox
	*/
	void setPosition(const Vector2f& pos);

	/*!
	  \brief Set the position of the TextBox - this also moves the position of the text
	  \param x The new x position of the TextBox
	  \param y The new y position of the TextBox
	*/
	void setPosition(const float x, const float y);

	/*!
	  \brief Returns the text string 
	  \return A copy of the string contained in the text
	*/
	String getText() { return text.getString(); }

	/*!
	  \brief Returns the position of the TextBox
	  \return A Vector2f containing the position of the TextBox
	*/
	Vector2f getPosition() { return textBox.getPosition(); }

	/*!
	  \brief Returns the size of the TextBox
	  \return A Vector2f containing the size of the TextBox
	*/
	Vector2f getSize() { return textBox.getSize(); }

	/*!
	  \brief Returns the top left position of the TextBox
	  \return A Vector2f containing the top left position of the TextBox
	*/
	Vector2f getTopLeft() { return textBox.getPosition(); }

	/*!
	  \brief Returns the top right position of the TextBox
	  \return A Vector2f containing the top right position of the TextBox
	*/
	Vector2f getTopRight() { return textBox.getPosition() + Vector2f(textBox.getSize().x, 0); }

	/*!
	  \brief Returns the bottom left position of the TextBox
	  \return A Vector2f containing the bottom left position of the TextBox
	*/
	Vector2f getBottomLeft() { return textBox.getPosition() + Vector2f(0, textBox.getSize().y); }

	/*!
	  \brief Returns the bottom right position of the TextBox
	  \return A Vector2f containing the bottom right position of the TextBox
	*/
	Vector2f getBottomRight() { return textBox.getPosition() + textBox.getSize(); }

	/*!
	  \brief Draw the TextBox and Text to render context
	  \param target The target to draw to (usually the window)
	  \param states The states used for drawing to a RenderTarget
	*/
	void draw(RenderTarget& target, RenderStates states) const;
};

/*! \class UserInterface
\brief Handles the user interface by drawing texts and graphics
*/
class UserInterface : public Drawable
{
private:
	Font m_font; //!< The font used for the user interfave
	TextBox m_highScore; //!< A TextBox that will display the high score
	TextBox m_currentScore; //!< A TextBox that will display the current score
	TextBox m_gameTime; //!< A TextBox that will display the running game time 
	TextBox m_gameWon; //!< A TextBox that will display when the player has won

	View m_uiView; //!< The renderable view used to draw the User Interface

public:
	/*!
	  \brief Default constructor - Creates TextBox's and places them in the corners of the screen
	*/
	UserInterface();

	/*!
	  \brief Updates the text values of the TextBox's and resets the position where required
	*/
	void update();

	/*!
	  \brief Draw the User Interface to render context
	  \param target The target to draw to (usually the window)
	  \param states The states used for drawing to a RenderTarget
	*/
	void draw(RenderTarget& target, RenderStates states) const;
};