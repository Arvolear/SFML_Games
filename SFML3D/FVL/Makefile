libFVL.a: transform.o mat4functions.o vec4functions.o vec3functions.o mat4.o vec4.o vec3.o
	ar rcs libFVL.a transform.o mat4functions.o vec4functions.o vec3functions.o mat4.o vec4.o vec3.o

transform.o: cpp/transform.cpp
	g++ -c cpp/transform.cpp -std=c++14

mat4functions.o: cpp/mat4functions.cpp
	g++ -c cpp/mat4functions.cpp -std=c++14

vec4functions.o: cpp/vec4functions.cpp
	g++ -c cpp/vec4functions.cpp -std=c++14
	
vec3functions.o: cpp/vec3functions.cpp
	g++ -c cpp/vec3functions.cpp -std=c++14

mat4.o: cpp/mat4.cpp
	g++ -c cpp/mat4.cpp -std=c++14

vec4.o: cpp/vec4.cpp
	g++ -c cpp/vec4.cpp -std=c++14

vec3.o: cpp/vec3.cpp
	g++ -c cpp/vec3.cpp -std=c++14

clean:
	rm -rf *.o
