#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "tekst.hpp"
#include "keybinding.hpp"


KeyBinding::KeyBinding( std::string keyName, sf::Keyboard::Key key, Text text ):
	keyName{ keyName },
	key{ key },
	text{ text }
{}

void KeyBinding::setString( std::string newKeyName ){
	keyName = newKeyName;
}

std::string KeyBinding::getString(){
	return keyName;
}

void KeyBinding::setKey( sf::Keyboard::Key newKey ){
	if(newKey == sf::Keyboard::A){
		text.setText(std::string{keyName + " : " + keyboardKeys[0]} );
		key = sf::Keyboard::A;
	}else{
		text.setText(std::string{keyName + " : " + keyboardKeys[newKey]} );
		key = newKey;
	}
}

sf::Keyboard::Key KeyBinding::getKey(){
	return key;
}

bool KeyBinding::contains( const sf::Vector2f& object ) const {
	return text.contains( object );
}

bool KeyBinding::contains( const sf::Vector2i& object ){
	return text.contains( object );
}

sf::Vector2f KeyBinding::castToF( sf::Vector2i target ){
	return text.castToF( target );
}

void KeyBinding::setText( std::string newName ){
	text.setText( newName );
}

std::string KeyBinding::getText(){
	return text.getText();
}

void KeyBinding::draw( sf::RenderWindow & window ){
	text.draw( window );
}