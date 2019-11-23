flags = -std=c++11 -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

Rocket: menu.o Market.o Help.o Level.o Rocket.o
	g++ -o Rocket menu.o Market.o Help.o Level.o Rocket.o $(flags)

menu.o: menu.cpp
	g++ -c menu.cpp $(flags)

Market.o: Market.cpp Market.h
	g++ -c Market.cpp $(flags)

Help.o: Help.cpp Help.h
	g++ -c Help.cpp $(flags)

Level.o: Level.cpp Level.h
	g++ -c Level.cpp $(flags)

Rocket.o: Rocket.cpp Rocket.h
	g++ -c Rocket.cpp $(flags)

clean:
	rm -rf *.o
	rm -rf Rocket
