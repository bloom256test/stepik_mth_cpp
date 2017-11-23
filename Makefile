all:
	g++ -std=c++11 -o app main.cpp

hw_mutex:
	g++ -std=c++11 -o app hw_mutex.cpp -pthread

run_hw_mutex: hw_mutex
	./app