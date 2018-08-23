output=.\\dist\\game

SFML=..\SFML
SFMLLIBS = -L$(SFML)\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE= -I$(SFML)\include

all: compiled
	echo Build success, running aplication... && $(output)
compiled: main.o planet.o
	g++ main.o planet.o -o  $(output) $(SFMLLIBS)

main.o : main.cpp Planet.cpp Planet.hpp
	g++ -c main.cpp $(SFML_INCLUDE)

planet.o : Planet.cpp Planet.hpp
	g++ -c Planet.cpp $(SFML_INCLUDE) -o planet.o