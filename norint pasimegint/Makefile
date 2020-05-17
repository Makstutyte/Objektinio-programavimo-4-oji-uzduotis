main: funkcijos.o funkcijos_vector.o  oj.o
	g++ -o test main.cpp funkcijos.o funkcijos_vector.o  oj.o
funkcijos:
	g++ -c funkcijos.cpp 
funkcijos_vector:
	g++ -c funkcijos_vector.cpp
oj:
	g++ -c oj.cpp
clean:
	del *.o main
