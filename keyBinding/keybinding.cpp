#include <SFML/Graphics.hpp>
#include <string>
#include "tekst.hpp"
#include "block.hpp"
#include "keybinding.hpp"


KeyBinding::KeyBinding( std::string keyName, sf::Keyboard::Key key, Block keyBlock, Text text ):
	keyName{ keyName },
	key{ key },
	keyBlock{ keyBlock },
	text{ text }
{}

void KeyBinding::setString( std::string newKeyName ){
	keyName = newKeyName;
}

std::string KeyBinding::getString(){
	return keyName;
}

void KeyBinding::setKey( sf::Keyboard::Key newKey ){
	text.setText(std::string{keyName + " : " + keyboardKeys[newKey]} );
	key = newKey;
}

sf::Keyboard::Key KeyBinding::getKey(){
	return key;
}

bool KeyBinding::contains( const sf::Vector2f& object ) const {
	return keyBlock.contains( object );
}

sf::Vector2f KeyBinding::castToF( sf::Vector2i target ){
	return keyBlock.castToF( target );
}

void KeyBinding::setText( std::string newName ){
	text.setText( newName );
}

std::string KeyBinding::getText(){
	return text.getText();
}

void KeyBinding::draw( sf::RenderWindow & window ){
	keyBlock.draw( window );
	text.draw( window );
}