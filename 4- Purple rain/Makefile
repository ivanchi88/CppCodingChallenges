output=.\\dist\\game

SFML=..\SFML
SFMLLIBS = -L$(SFML)\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE= -I$(SFML)\include

all: compiled
	echo Build success, running aplication... && $(output)
compiled: main.o drop.o
	g++ main.o drop.o -o  $(output) $(SFMLLIBS)

main.o : main.cpp Drop.cpp Drop.hpp
	g++ -c main.cpp $(SFML_INCLUDE)

drop.o : Drop.cpp Drop.hpp
	g++ -c Drop.cpp $(SFML_INCLUDE) -o drop.o