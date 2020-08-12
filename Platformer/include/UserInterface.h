#pragma once

/*!
\file UserInterface.h
*/

#include <SFML/Graphics.hpp>
#include <iostream> // for debugging
#include "World.h"

using namespace sf;

/*! \class UserInterface
\brief Handles the user interface by drawing texts and graphics
*/

struct TextBox : public Drawable
{
private:
	Text text;
	RectangleShape textBox; // This struct generates a rectangle shape around the text
	Vector2f padding;

public:
	TextBox(Text _text = Text(), RectangleShape _rectShape = RectangleShape(), Vector2f _position = Vector2f(0, 0), Vector2f _padding = Vector2f(15, 15));

	// Setters and Getters
	void setText(const String& string);
	void setPosition(const Vector2f& pos);
	void setPosition(const float x, const float y);
	String getText() { return text.getString(); }
	Vector2f getPosition() { return textBox.getPosition(); }
	Vector2f getSize() { return textBox.getSize(); }

	// Helper functions to get the corners of the Text Box:
	Vector2f getTopLeft() { return textBox.getPosition(); }
	Vector2f getTopRight() { return textBox.getPosition() + Vector2f(textBox.getSize().x, 0); }
	Vector2f getBottomLeft() { return textBox.getPosition() + Vector2f(0, textBox.getSize().y); }
	Vector2f getBottomRight() { return textBox.getPosition() + textBox.getSize(); }

	void draw(RenderTarget& target, RenderStates states) const; //!< Overriden function
};

class UserInterface : public Drawable
{
private:
	Font m_font;
	TextBox m_highScore;
	TextBox m_currentScore;
	TextBox m_gameTime;
	TextBox m_gameWon;

	View m_uiView;

public:
	UserInterface();
	void update(); // Required to move the user interface as the camera moves
	void draw(RenderTarget& target, RenderStates states) const; //!< Overriden function
};