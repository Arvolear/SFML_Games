3danimation: main.o graphics.o zbuffer.o camera.o fpstracker.o generate.o stuff.o
	g++ -o 3danimation main.o graphics.o zbuffer.o camera.o fpstracker.o generate.o stuff.o -std=c++14 -lsfml-system -lsfml-window -lsfml-graphics -lFVL -fopenmp -pthread -std=c++14 -O3
	
main.o: main.cpp
	g++ -c main.cpp -std=c++14

graphics.o: graphics.cpp
	g++ -c graphics.cpp -fopenmp -pthread -std=c++14

zbuffer.o: zbuffer.cpp
	g++ -c zbuffer.cpp -fopenmp -std=c++14

camera.o: camera.cpp
	g++ -c camera.cpp -fopenmp -std=c++14

fpstracker.o: fpstracker.cpp
	g++ -c fpstracker.cpp -pthread -std=c++14

generate.o: generate.cpp
	g++ -c generate.cpp -fopenmp -std=c++14

stuff.o: stuff.cpp
	g++ -c stuff.cpp -fopenmp -std=c++14

clean:
	rm -rf *.o
	rm -rf 3danimation


