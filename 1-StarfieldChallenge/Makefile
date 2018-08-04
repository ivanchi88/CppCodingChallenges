output=.\\dist\\game

SFML=D:\Programacion\C++\BookBeginingC++Games\SFML
SFMLLIBS = -L$(SFML)\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE= -I$(SFML)\include

all: compiled
	echo Build success, running aplication... && $(output)
compiled: main.o star.o
	g++ main.o star.o -o  $(output) $(SFMLLIBS)

main.o : main.cpp Star.cpp Star.hpp
	g++ -c main.cpp $(SFML_INCLUDE)

star.o : Star.cpp Star.hpp
	g++ -c Star.cpp $(SFML_INCLUDE) -o star.o