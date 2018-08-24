output=.\\dist\\game

SFML=..\SFML
SFMLLIBS = -L$(SFML)\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE= -I$(SFML)\include

all: compiled
	echo Build success, running aplication... && $(output)
compiled: main.o blob.o
	g++ main.o blob.o -o  $(output) $(SFMLLIBS)

main.o : main.cpp Blob.cpp Blob.hpp
	g++ -c main.cpp $(SFML_INCLUDE)

blob.o : Blob.cpp Blob.hpp
	g++ -c Blob.cpp $(SFML_INCLUDE) -o blob.o