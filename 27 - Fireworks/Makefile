output=.\\dist\\game

SFML=..\SFML
SFMLLIBS = -L$(SFML)\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_INCLUDE= -I$(SFML)\include

all: compiled
	echo Build success, running aplication... && $(output)
compiled: main.o cell.o spark.o
	g++ main.o cell.o spark.o -o  $(output) $(SFMLLIBS)

main.o : main.cpp 
	g++ -c main.cpp $(SFML_INCLUDE)

cell.o : Firework.cpp Firework.hpp
	g++ -c Firework.cpp $(SFML_INCLUDE) -o cell.o
spark.o : Spark.cpp Spark.hpp
	g++ -c Spark.cpp $(SFML_INCLUDE) -o spark.o