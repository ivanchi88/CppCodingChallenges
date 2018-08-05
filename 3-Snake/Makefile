output=.\\dist\\game

SFML=D:\Programacion\C++\BookBeginingC++Games\SFML
SFMLLIBS = -L$(SFML)\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE= -I$(SFML)\include

all: compiled
	echo Build success, running aplication... && $(output)
compiled: main.o snake.o
	g++ main.o snake.o -o  $(output) $(SFMLLIBS)

main.o : main.cpp Snake.cpp Snake.hpp
	g++ -c main.cpp $(SFML_INCLUDE)

snake.o : Snake.cpp Snake.hpp
	g++ -c Snake.cpp $(SFML_INCLUDE) -o snake.o