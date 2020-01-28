
HEADERS := AssetManager.hpp Editor.hpp World.hpp ScreenObject.hpp FactoryFunction.hpp LootDrop.hpp Character.hpp Game.hpp Items.hpp Player.hpp SpriteAnimation.hpp Enemy.hpp Interface.hpp Settings.hpp StateMachine.hpp keybinding.hpp tekst.hpp Audio.hpp Exceptions.hpp States.hpp InterfaceElement.hpp Action.hpp
SOURCES := AssetManager.cpp Editor.cpp World.cpp ScreenObject.cpp FactoryFunction.cpp LootDrop.cpp Character.cpp Game.cpp Player.cpp Items.cpp SpriteAnimation.cpp Enemy.cpp Interface.cpp StateMachine.cpp Settings.cpp keybinding.cpp tekst.cpp Audio.cpp States.cpp InterfaceElement.cpp 

LINKER_FLAGS += `pkg-config opencv --cflags --libs` -lpthread -lsfml-graphics -lsfml-audio
COMPILER_FLAGS += -O3

SEARCH  := AI Assets Editor Entities Physics World Characters Game Interface Items State Settings Audio ..

RELATIVE := ..
include $(RELATIVE)/Makefile.native
