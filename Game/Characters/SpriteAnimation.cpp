/// @file
#include "SpriteAnimation.hpp"
#include <iostream>
#include<exception>
#include <string>
#include "FactoryFunction.hpp"
#include "Character.hpp"


/// \brief
/// Create instance.
/// \details
/// This function creates a SpriteAnimation.
/// @param sprite This is the sprite.
/// @param texture This has the spritesheet as texture for the sprite.
/// @param dimensions This has the width(dimension.x) and height(dimension.y) of the spritesheet.
/// @param spriteRowColumn This has the amount of horizontal sprites(row) and the amount of vertical sprites(column).
/// @param scale This has the scale the sprite has to be.
/// @param missingRow This is how many sprites are missing at the end.
/// @param animationSpeed This is the animationSpeed.
SpriteAnimation::SpriteAnimation( sf::Sprite& sprite, sf::Texture& texture, const sf::Vector2i dimensions, sf::Vector2i spriteRowColumn, 
								  sf::Vector2i scale, sf::Vector2i missingRowCollom, sf::Vector2i startpos,  float animationSpeed ):
	sprite(sprite),	
	texture(texture),
	dimensions(dimensions),
	spriteRowColumn(spriteRowColumn),
	scale(scale),
	missingRow(missingRowCollom.x),
	animationSpeed(animationSpeed)

	

{	
	pixelRow = dimensions.x / spriteRowColumn.x;					// Length divided by row, these are the horizontal steps a frame
	pixelColumn = dimensions.y / spriteRowColumn.y;					// Height divided by column, these are the vertical steps a frame
	rectSourceSprite = sf::IntRect( 0, 0, pixelRow, pixelColumn ); 	// First 2 numbers will iterate trough frames, second 2 are the width and height of a single frame
	sprite = sf::Sprite(texture, rectSourceSprite);					// Give the sprite
	sprite.setScale(static_cast<sf::Vector2f>(scale));				// Set the scale
	sprite.setOrigin(pixelRow/2, pixelColumn/2);						// Set the origin to the middle
	changeStartEndFrame(startpos,missingRowCollom,0);
	std::cout<<"----------------VERKEERDE CONSTRUCTOR-------------"<<'\n';
}
void SpriteAnimation::sethitboxscale(float newscale){
	hitboxscale=newscale;
}

SpriteAnimation::SpriteAnimation(AssetManager &assets,sf::Sprite &sprite, std::string movename, std::string filename):
sprite(sprite),
texture(assets.getTexture(filename))
{
	std::ifstream charactersFile("Characters/characters.txt");
	if(!charactersFile){
		throw fileNotFound("Characters/characters.txt");
	}
	//std::string carname="player";
	std::vector<sf::Vector2i> spritePlayerData;
	std::vector<sf::Vector2i> spritePlayerAction;
	std::vector<std::string> spritePlayerNames;
	SpriteCharacter characterData(spritePlayerData, spritePlayerAction, spritePlayerNames);
	std::string prevstring="";
	sf::Vector2i position;
	sf::Vector2f scaled;
	//std::string filename="";
	while (!isEmpty(charactersFile)){
		//bool data, action, names, textureName;

		std::string currstring = "";


		charactersFile>>currstring;

		//std::cout<<readName<<'\n';
		if((currstring.find("size")!= std::string::npos)){
			std::cout<<"offset  "<<position.x<<"  "<<position.y<<'\n';
			charactersFile>>position;
			dimensions=position;
			
			std::cout<<"pos    "<<position.x<<"     "<<position.y<<'\n';
		}

		if((currstring.find("grid")!= std::string::npos)){

			charactersFile>>position;
			spriteRowColumn= position;
			std::cout<<"rc    "<<position.x<<"     "<<position.y<<'\n';
			//std::cout<<position.x<<'\n';
		}
		if((currstring.find("action")!= std::string::npos)){

			charactersFile>>position;
			spritePlayerAction.push_back(position);
			//std::cout<<position.x<<'\n';
		}
		if((currstring.find("scale")!= std::string::npos)){

			charactersFile>>position;
			scale=sf::Vector2f(position);
			std::cout<<"scale    "<<position.x<<"     "<<position.y<<'\n';
			spritePlayerData.push_back(position);
			
			//std::cout<<position.x<<'\n';
		}
		
		if((currstring.find("state")!= std::string::npos)){

			charactersFile>>currstring;
			spritePlayerNames.push_back(currstring);
			//std::cout<<position.x<<'\n';
		}
		if((currstring.find("filename")!= std::string::npos)){

			charactersFile>>currstring;
			filename=currstring;
			std::cout<<"filename    |"<<filename<<'\n';
			//std::cout<<position.x<<'\n';
		}

		if((currstring.find("missing")!= std::string::npos)){

			charactersFile>>position;
			missingRowCollom=position;
			std::cout<<"missingpos    "<<position.x<<"     "<<position.y<<'\n';
			std::cout<<"missing    "<<missingRowCollom.x<<"     "<<missingRowCollom.y<<'\n';
			//std::cout<<position.x<<'\n';
		}
		if((currstring.find("start")!= std::string::npos)){

			charactersFile>>position;
			startFrame=position;
			//std::cout<<"missingpos    "<<position.x<<"     "<<position.y<<'\n';
			//std::cout<<"missing    "<<missingRowCollom.x<<"     "<<missingRowCollom.y<<'\n';
			//std::cout<<position.x<<'\n';
		}
		if((currstring.find("offset")!= std::string::npos)){

			charactersFile>>position;

			offset=position;
			//std::cout<<position.x<<'\n';
		}
		//std::cout<<currstring<<'\n';
		if((currstring.find("hitfac")!= std::string::npos)){

			std::cout<<"HITFACTOR"<<'\n';
			charactersFile>>scaled;
			//std::cout<<"hiscale    "<<currstring<<'\n';
			//std::cout<<"hiscale    "<<position.x<<'\n';
			hitboxscale=scaled.x;
			std::cout<<"hiscale    "<<hitboxscale<<'\n';
			//std::cout<<position.x<<'\n';
		}
		
		prevstring=currstring;
		// characterData = SpriteCharacter(spritePlayerData, spritePlayerAction, spritePlayerNames);
		if(currstring == movename){
				std::cout<<"filenamefound    |"<<currstring<<'\n';
				//sstd::cout<<spritePlayerData[2].x<<"   "<<spritePlayerData[0].y<<'\n';				std::cout<<"jawoel"<<'\n';
		 		//characters.push_back(Character(sf::Vector2f(500,350), std::make_shared<PlayerInput>(), std::make_shared<PlayerPhysics>(), std::make_shared<PlayerGraphics>(filename, assets, characterData)));
		 		texture=assets.getTexture(filename);
				 std::cout<<"ehmconstructor"<<'\n';
				 break;
			 } 
		if((currstring.find("eind")!= std::string::npos)){
			currstring="";
			spritePlayerData.clear();
			spritePlayerNames.clear();
			spritePlayerAction.clear();
			std::cout<<"CLEAAAAAREDconst"<<'\n';
			//std::cout<<position.x<<'\n';
		}



		// try{
		// 	if(data | action){
		// 		charactersFile >> position;
		// 	} else {
		// 		charactersFile >> readName;
		// 	}
		// } catch (...){
		// 	//std::cout<<"caught"<<'\n';
		// 	if(data){
		// 		action = true;
		// 		data = false;
		// 	} else if (action){
		// 		names = true;
		// 		action = false;
		// 	}
		// }
		// if(readName.find("|") != std::string::npos&&0){
		// 	charactersFile >> readName;
		// 	names = false;
		// 	textureName = true;

		// }		if(readName.find("/") != std::string::npos&&0){
		// 	std::string testvar;
		// 	charactersFile >> testvar;
		// 	std::cout<<testvar<<'\n';
		// 	//names = false;
		// 	//textureName = true;

		// }
		// //std::cout<<readName<<'\n';
		// //std::cout << position.x << ", " << position.y << ", " << readName << std::endl;
		// if(data){
		// 	spritePlayerData.push_back(position);
		// 	//std::cout<<position.x<<'\n';
		// } else if (action){
		// 	spritePlayerAction.push_back(position);
		// } else if (names){
		// 	//std::cout<<"names   "<<readName<<'\n';
		// 	spritePlayerNames.push_back(readName);
		// } else if (textureName){
		// 	//readName contains the textureName.
		// 	// spritePlayerData = {sf::Vector2i{350,592},sf::Vector2i{7,16}, sf::Vector2i{5,5}, sf::Vector2i{3,0}};
		// 	spritePlayerAction.erase(spritePlayerAction.begin());
		// 	spritePlayerNames.erase(spritePlayerNames.begin());
		// 	// for(const auto & vector : spritePlayerData){
		// 	// 	std::cout << '(' << vector.x << ',' << vector.y << ')' << std::endl;
		// 	// }
		// 	// for(const auto & vector : spritePlayerAction){
		// 	// 	std::cout << '(' << vector.x << ',' << vector.y << ')' << std::endl;
		// 	// }
		// 	// for(const auto & vector : spritePlayerNames){
		// 	// 	std::cout << vector << std::endl;
		// 	// }
		// 	// std::cout << readName << std::endl;
		// 	// spritePlayerAction = { sf::Vector2i{0,0}, sf::Vector2i{3,0}, sf::Vector2i{3,3}, sf::Vector2i{0,0}, sf::Vector2i{1,1},sf::Vector2i{0,0}, sf::Vector2i{2,2}, sf::Vector2i{6,1}};
		// 	// spritePlayerNames = {"idle","slide", "walk", "jump"};
		// 	characterData = SpriteCharacter(spritePlayerData, spritePlayerAction, spritePlayerNames);
		// 	//std::cout<<spritePlayerNames[0]<<'\n';
		// 	data = true;
		// 	textureName = false;
		// 	if(readName == "waterBubble"){
		// 		characters.push_back(Character(sf::Vector2f(500,350), std::make_shared<PlayerInput>(), std::make_shared<PlayerPhysics>(), std::make_shared<PlayerGraphics>(readName, assets, characterData)));
		// 	} else
		// 	{
		// 		spritePlayerNames.clear();
		// 		spritePlayerData.clear();
		// 		spritePlayerAction.clear();
		// 	}
			
		// 	//if(readName != "player"){
		// 	//	type = ArtificalInput() oid.
		// 	//}
		// }
		std::cout<<"missingloop    "<<missingRowCollom.x<<"     "<<missingRowCollom.y<<'\n';
		std::cout<<'\n'<<'\n';
	}
	pixelRow = dimensions.x / spriteRowColumn.x;					// Length divided by row, these are the horizontal steps a frame
	pixelColumn = dimensions.y / spriteRowColumn.y;					// Height divided by column, these are the vertical steps a frame
	rectSourceSprite = sf::IntRect( 0, 0, pixelRow, pixelColumn ); 	// First 2 numbers will iterate trough frames, second 2 are the width and height of a single frame
	sprite = sf::Sprite(texture, rectSourceSprite);					// Give the sprite
	sprite.setScale(static_cast<sf::Vector2f>(scale));				// Set the scale
	sprite.setOrigin(pixelRow/2, pixelColumn/2);
	std::cout<<"missingtest    "<<missingRowCollom.x<<"     "<<missingRowCollom.y<<'\n';						// Set the origin to the middle
	changeStartEndFrame(startFrame,missingRowCollom,0);
	animationSpeed=0.1;
	//sethitboxscale(0.2);
	std::cout<<"rowcol    "<<spriteRowColumn.x<<"     "<<spriteRowColumn.y<<'\n';

}




/// \brief
/// Enable left side of sprite.
/// \details
/// This function multiplies scale.x by -1 to flip the sprite.
/// @param left This decides whether the scale has to be left.
void SpriteAnimation::leftSprite(bool left){
	if(left&&scale.x>0){
		scale.x = scale.x*-1;
		sprite.setScale(scale.x,scale.y);
	}else if(!left&&scale.x<0){		
		scale.x = scale.x*-1;
		sprite.setScale(scale.x,scale.y);
	}
}

/// \brief
/// Set the specified start and end frame to loop trough.
/// \details
/// This function will set the specified start and end frame, the missingRow, the specifiedColumnsHeight and enables the specifiedFrameLoop().
/// @param rowColumn This has a row and a column, The row is on which sprite to begin. The column is on which column to begin.
/// @param missingRowColumn This has a missing row and a columnHeight, The missing row is how many sprites there are left in a row. The columnHeight is to specify if the amount of frames is longer than one row.
/// @param left This enables the leftside of a sprite.
void SpriteAnimation::changeStartEndFrame( sf::Vector2i rowColumn, sf::Vector2i missingRowColumn, bool left ){
	std::cout<<"frameschanged   "<<rowColumn.x<<"   "<<rowColumn.y<<"  "<<missingRowColumn.x<<"  "<<missingRowColumn.y<<'\n';
	startFrameLoop = true;
	spriteRowColumn = rowColumn;
	missingRow = missingRowColumn.x; // If there are still sprites after the desired frames, assign them as missing(+1 for a missing frame)
	specifiedColumnsHeight = missingRowColumn.y; 
	leftSprite(left);
	//Specify start frame
	rectSourceSprite = sf::IntRect( pixelRow*spriteRowColumn.x, pixelColumn*spriteRowColumn.y, pixelRow, pixelColumn );

}

/// \brief
/// This loops trough the entire spritesheet.
/// \details
/// This function will go from frame to frame and goes back to the beginning when it reaches the end.
void SpriteAnimation::normalFrameLoop(){
	if(rectSourceSprite.left == dimensions.x-pixelRow){  		// If you're at the end of the row, begin at he first row and go one column down	
		rectSourceSprite.left = 0;								// 
		rectSourceSprite.top += pixelColumn; 		 			// Go one column down	
			// If width and column are at the end of the spritesheet, start over from the beginning
	}else if( rectSourceSprite.left == dimensions.x-pixelRow*(spriteRowColumn.x-missingRow) && rectSourceSprite.top == pixelColumn*(spriteRowColumn.y -1)){ 	
		rectSourceSprite.left = 0;	 							// Go back to the specified start frame
		rectSourceSprite.top = 0; 								// Go back to the specified start frame
		// Go to the next frame
	}else{ 
		rectSourceSprite.left += pixelRow;
	}
}

/// \brief
/// This loops trough the specified parts of the spritesheet.
/// \details
/// This function will start from the specified frame to the specified end frame and goes back to the specified start frame when it reaches the end.
void SpriteAnimation::specifiedFrameLoop(){
	if(rectSourceSprite.left == dimensions.x-pixelRow){ 		// If you're at the end of the row, begin at he first row and go one column down	
		rectSourceSprite.left = 0;
		rectSourceSprite.top += pixelColumn; 					// Go one column down
	}else{ 
		rectSourceSprite.left += pixelRow;
	}
	if( ( rectSourceSprite.left == dimensions.x-pixelRow*missingRow ||rectSourceSprite.left == dimensions.x-pixelRow ) && rectSourceSprite.top == pixelColumn*(spriteRowColumn.y+specifiedColumnsHeight) ){
		rectSourceSprite.left = pixelRow * spriteRowColumn.x; 	// Go back to the specified start frame
		rectSourceSprite.top = pixelColumn * spriteRowColumn.y; // Go back to the specified start frame
	}
}

/// \brief
/// This draws the sprite.
/// \details
/// This function will draw the sprite.
/// @param window The RenderWindow to draw the sprite in.
void SpriteAnimation::draw( sf::RenderWindow & window ){
	//std::cout<<dimensions.x<<'\n';
	if(spriteClock.getElapsedTime().asSeconds() > animationSpeed){
		if(!startFrameLoop){
			normalFrameLoop();
		}else{ 
			specifiedFrameLoop(); 
		}	
		sprite.setTextureRect(rectSourceSprite); 				// Set the texture of the sprite to the next frame.
		spriteClock.restart();
	}
				sf::RectangleShape hit(sf::Vector2f(rectSourceSprite.height,rectSourceSprite.width));
				hit.setPosition(sf::Vector2f(rectSourceSprite.left,rectSourceSprite.top));
	 			hit.setFillColor(sf::Color(0,255,0,128));
	 			window.draw(hit);
	window.draw(sprite);
	std::cout<<"drawing  "<<missingRowCollom.x<<'\n';
}


