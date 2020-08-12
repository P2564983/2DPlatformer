#include "..\include\UserInterface.h"

TextBox::TextBox(Text _text, RectangleShape _rectShape, Vector2f _position, Vector2f _padding) 
	: text(_text), textBox(_rectShape), padding(_padding)
{
	// Set positions
	textBox.setPosition(_position);
	text.setPosition(_position + (_padding * 0.5f));
	// Get the size of the text
	FloatRect bounds = text.getLocalBounds();
	textBox.setSize(Vector2f(bounds.width + bounds.left + _padding.x, bounds.height + bounds.top + _padding.y));
}

void TextBox::setText(const String& string)
{
	// Set the string
	text.setString(string);
	// Recalculate the Text Box
	FloatRect bounds = text.getLocalBounds();
	textBox.setSize(Vector2f(bounds.width + bounds.left + padding.x, bounds.height + bounds.top + padding.y));
}

void TextBox::setPosition(const Vector2f& pos)
{
	textBox.setPosition(pos);
	text.setPosition(pos + (padding * 0.5f));
}

void TextBox::setPosition(const float x, const float y)
{
	this->setPosition(Vector2f(x, y)); // Calls the other setPosition method
}

void TextBox::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(textBox);
	target.draw(text);
}

UserInterface::UserInterface()
{
	if (!m_font.loadFromFile("./assets/fonts/bahnschrift.ttf"))
		std::cout << "Error setting up UI: Could not find font" << std::endl;

	// Set the UI View
	m_uiView.setViewport(FloatRect(0.f, 0.f, 1.f, 1.f)); // Entire window size

	Text sampleText;
	sampleText.setString("Text not set");
	sampleText.setFont(m_font);
	sampleText.setCharacterSize(30);
	sampleText.setFillColor(Color::White);
	sampleText.setPosition(0, 0);

	RectangleShape sampleRect;
	sampleRect.setFillColor(Color::Black);
	// Could also add an outline

	m_highScore = TextBox(sampleText, sampleRect, Vector2f(0, 0));
	m_highScore.setText("High Score = 0");

	m_currentScore = TextBox(sampleText, sampleRect, m_highScore.getBottomLeft());
	m_currentScore.setText("Current Score = 0");

	m_gameTime = TextBox(sampleText, sampleRect, m_currentScore.getBottomLeft());
	m_gameTime.setText("Game Time (s) = 0");
	m_gameTime.setPosition(m_uiView.getSize().x - m_gameTime.getSize().x, 0); // position top right

	m_gameWon = TextBox(sampleText, sampleRect, m_gameTime.getBottomLeft());
	m_gameWon.setText("You have won!");
	m_gameWon.setPosition(m_uiView.getSize().x - m_gameWon.getSize().x, m_gameTime.getBottomLeft().y);
}

void UserInterface::update()
{
	m_currentScore.setText("Current Score = " + std::to_string(Score::getCurrentScore()));
	m_highScore.setText("High Score = " + std::to_string(Score::getHighScore()));

	m_gameTime.setText("Game Time (s) = " + std::to_string((int)Score::getGameTimeAsSeconds()));
	m_gameTime.setPosition(m_uiView.getSize().x - m_gameTime.getSize().x, 0); // position top right
}

void UserInterface::draw(RenderTarget& target, RenderStates states) const
{
	View prevView = target.getView();

	// Change the view to UI View and Render:
	target.setView(m_uiView);
	target.draw(m_highScore);
	target.draw(m_currentScore);
	target.draw(m_gameTime);
	if (Score::getCurrentScore() >= 100)
		target.draw(m_gameWon);

	// Revert to the previous view:
	target.setView(prevView);
}


