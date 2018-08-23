output=.\\dist\\game

SFML=..\SFML
SFMLLIBS = -L$(SFML)\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE= -I$(SFML)\include

all: compiled
	echo Build success, running aplication... && $(output)
compiled: main.o alien.o player.o bullet.o 
	g++ main.o alien.o player.o bullet.o -o  $(output) $(SFMLLIBS)

main.o : main.cpp Alien.hpp Bullet.hpp Player.hpp
	g++ -c main.cpp $(SFML_INCLUDE)

alien.o : Alien.cpp Alien.hpp
	g++ -c Alien.cpp $(SFML_INCLUDE) -o alien.o

player.o : Player.cpp Player.hpp Bullet.hpp
	g++ -c Player.cpp $(SFML_INCLUDE) -o player.o

bullet.o : Bullet.cpp Bullet.hpp
	g++ -c Bullet.cpp $(SFML_INCLUDE) -o bullet.o