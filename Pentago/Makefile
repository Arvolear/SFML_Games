pentago: main.o menu.o frontend.o winscreen.o boardpart.o bot.o backend.o
	g++ -o pentago main.o menu.o frontend.o winscreen.o boardpart.o bot.o backend.o -lsfml-window -lsfml-system -lsfml-graphics -pthread -std=c++14

main.o: main.cpp
	g++ -c main.cpp -std=c++14

menu.o: menu.cpp menu.hpp
	g++ -c menu.cpp -std=c++14

frontend.o: frontend.cpp frontend.hpp
	g++ -c frontend.cpp -std=c++14

winscreen.o: winscreen.cpp winscreen.hpp
	g++ -c winscreen.cpp -std=c++14

boardpart.o: boardpart.cpp boardpart.hpp
	g++ -c boardpart.cpp -std=c++14

bot.o: bot.cpp bot.hpp
	g++ -c bot.cpp -std=c++14

backend.o: backend.cpp backend.hpp
	g++ -c backend.cpp -std=c++14

clean:
	rm -rf pentago
	rm -rf *.o
