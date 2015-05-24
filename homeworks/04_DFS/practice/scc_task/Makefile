all: solution validator brute

solution: sol.cpp
	g++ -g sol.cpp -o sol --std=c++11 

validator: validator.cpp
	g++ -g validator.cpp -o validator --std=c++11

brute: brute.cpp
	g++ -g brute.cpp -o brute --std=c++11

clean:
	rm sol brute validator
