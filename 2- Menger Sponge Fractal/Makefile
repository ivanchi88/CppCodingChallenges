output=.\\dist\\game

SFML=..\SFML
SFMLLIBS = -L$(SFML)\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lopengl32 -lglu32
SFML_INCLUDE= -I$(SFML)\include

all: compiled
	echo Build success, running aplication... && $(output)
compiled: main.o box.o
	g++ main.o box.o -o  $(output) $(SFMLLIBS)

main.o : main.cpp Box.cpp Box.hpp
	g++ -c main.cpp $(SFML_INCLUDE)

box.o : Box.cpp Box.hpp
	g++ -c Box.cpp $(SFML_INCLUDE) -o box.o