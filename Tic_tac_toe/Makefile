tic_tac_toe: main.o settings.o graphics.o win.o logic.o
	g++ -o tic_tac_toe main.o settings.o graphics.o win.o logic.o -std=c++14 -lsfml-window -lsfml-graphics -lsfml-system -O3

main.o: main.cpp
	g++ -c main.cpp -std=c++14 -lsfml-window -lsfml-graphics -lsfml-system

settings.o: settings.cpp
	g++ -c settings.cpp -std=c++14 -lsfml-window -lsfml-graphics -lsfml-system 

graphics.o: graphics.cpp
	g++ -c graphics.cpp -std=c++14 -lsfml-window -lsfml-graphics -lsfml-system

win.o: win.cpp
	g++ -c win.cpp -std=c++14 -lsfml-window -lsfml-graphics -lsfml-system

logic.o: logic.cpp
	g++ -c logic.cpp -std=c++14

clean:
	rm -rf tic_tac_toe
	rm -rf *.o
