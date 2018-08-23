output=.\\dist\\game

SFML=..\SFML
SFMLLIBS = -L$(SFML)\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE= -I$(SFML)\include

all: compiled
	echo Build success, running aplication... && $(output)
compiled: main.o 
	g++ main.o -o  $(output) $(SFMLLIBS)

main.o : main.cpp 
	g++ -c main.cpp $(SFML_INCLUDE)
