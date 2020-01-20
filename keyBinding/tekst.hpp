#ifndef _TEKST_HPP
#define _TEKST_HPP

#include <SFML/Graphics.hpp>
#include <string>

// this file contains Doxygen lines
/// @file

/// \brief
/// sfml object that displays text
/// \details
/// This object will display a string of text on a window screen
class Text {
private:
	std::string input;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Color color;
	bool centered;				//decides if objects position should be used as center(true) or as left upper corner (false)
	sf::Text text;
	sf::Font font;
	bool calculated = true;		//dirty flag to stop recalculations at the draw function

public:


	/// \brief
    /// default constructor
    /// \details
    /// This constructor does initialize the default attributes.
    /// input is the string we will display, position is the location of the object (left upper corner), size is the size of the text itself,
    /// color is in what color the text will be displayed and centered is a bool that decides if the position is the center of the object
    /// or the left upper corner of the object (usefull if you want to center a text object in the middle of the screen with changable size)
	Text( std::string input, sf::Vector2f position, float size = 1.0, sf::Color color = sf::Color::Black, bool centered = false );

	/// \brief
    /// draws the object on a window
    /// \details
    /// uses a reference to a renderwindow to draw the object on it.
	void draw( sf::RenderWindow & window );

	/// \brief
    /// sets a new text
    /// \details
    /// using this function allows you to put a new text in the object.
	void setText( std::string newText );

	/// \brief
    /// gets the text
    /// \details
    /// returns the text objects text as string.
	std::string getText();

	/// \brief
    /// checks if object intersects
    /// \details
    /// requires another object as Vector2f as parameter and return if the objects are intersecting.
	bool contains( const sf::Vector2f& object ) const;

	/// \brief
    /// checks if object intersects
    /// \details
    /// requires another object as Vector2i as parameter and return if the objects are intersecting.
    /// best use for a mouse
	bool contains( const sf::Vector2i& object );

	/// \brief
    /// casts Vector2i to Vector2f
    /// \details
    /// casts Vector2i to Vector2f
	sf::Vector2f castToF( sf::Vector2i target ){
		return sf::Vector2f(
			static_cast<float>( target.x ),
			static_cast<float>( target.y )
		);
	}

	/// \brief
    /// sets a new color
    /// \details
    /// sets a new color
	void setColor(sf::Color color);

	/// \brief
    /// make the object centered or not
    /// \details
    /// makes the position of the object as center of the object
    /// if the bool is true and if the bool is false make the position
    /// as upper left of the object.
	void makeCentered(bool check);

};

#endif