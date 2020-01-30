/// @file

#ifndef _KEYBINDING_HPP
#define _KEYBINDING_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "tekst.hpp"

/// \brief
/// KeyBinding
/// \details
/// This class is a composite class, which means it holds multiple objects like:
/// a string, sf::Keyboard::Key and a Text object.
class KeyBinding{
private:
	const std::array< std::string, 107 > keyboardKeys = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Num0",
  		"Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "Escape", "LControl", "LShift", "LAlt", "LSystem", "RControl", "RShift", "RAlt", "RSystem", "Menu", "LBracket",
  		"RBracket", "Semicolon", "Comma", "Period", "Quote", "Slash", "Backslash", "Tilde", "Equal", "Hyphen", "Space", "Enter", "Backspace", "Tab", "PageUp", "PageDown",
  		"End", "Home", "Insert", "Delete", "Add", "Subtract", "Multiply", "Divide", "Left", "Right", "Up", "Down", "Numpad0", "Numpad1", "Numpad2", "Numpad3", "Numpad4", "Numpad5", "Numpad6", "Numpad7",
  		"Numpad8", "Numpad9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12", "F13", "F14", "F15", "Pause", "KeyCount", "Dash", "BackSpace", "BackSlash", "SemiColon", "Enter" 
	};

	std::string keyName;
	sf::Keyboard::Key key;
	Text text;

public:

	/// \brief
	/// Default constructor
	/// \details
	/// This is the default constructor.
	/// @param keyName This is a string that tells what the key is for.
	/// @param key This is a sfml object that tells us which key we use.
	/// @param text This is a text object, this is used to be able to display what the key is for and the key it self.
	KeyBinding( std::string keyName, sf::Keyboard::Key key, Text text );

	/// \brief
	/// This changes the keyName string
	/// \details
	/// This function is for when you need to change what the key does describtion for some reason,
	/// this will also change the string in the text object
	/// @param newKeyName The new string object that describes what the key does.
	void setString( std::string newKeyName );

	/// \brief
	/// Gets the name of the string
	/// \details
	/// This function will return a string that describes what the key does
	/// \return string object that describes the key functionality
	std::string getString();

	/// \brief
	/// Sets a new key
	/// \details
	/// This function will change the key we use.
	/// @param newKey changes the key we use in this class
	void setKey( sf::Keyboard::Key newKey );

	/// \brief
	/// Gets the key
	/// \details
	/// This function will return the key.
	/// \return gives back a sf::Keyboard::Key object.
	sf::Keyboard::Key getKey();

	/// \brief
	/// function to check for collision
	/// \details
	/// This function returns if there is a collision between 
	/// two objects.
	/// \return a bool if there is a collision
	bool contains( const sf::Vector2f& object ) const;

	/// \brief
	/// 
	/// \details
	/// 
	bool contains( const sf::Vector2i& object );

	/// \brief
	/// 
	/// \details
	/// 
	sf::Vector2f castToF( sf::Vector2i target );

	/// \brief
	/// 
	/// \details
	/// 
	void setText( std::string newName );

	/// \brief
	/// 
	/// \details
	/// 
	std::string getText();

	/// \brief
	/// 
	/// \details
	/// 
	void setColor(sf::Color color);

	/// \brief
	/// 
	/// \details
	/// 
	void draw( sf::RenderWindow & window );

};

#endif
