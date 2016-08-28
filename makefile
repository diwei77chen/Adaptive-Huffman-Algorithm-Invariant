all: ahencode ahdecode

ahencode: ahencode.o main_encode.o
	g++ ahencode.o main_encode.o -o ahencode

ahdecode: ahdecode.o main_decode.o
	g++ ahdecode.o main_decode.o -o ahdecode

main_encode.o: main_encode.cpp ahencode.h
	g++ -std=c++11 -Wall -Werror -O2 -c main_encode.cpp

main_decode.o: main_decode.cpp ahdecode.h
	g++ -std=c++11 -Wall -Werror -O2 -c main_decode.cpp
	
ahencode.o: ahencode.cpp ahencode.h
	g++ -std=c++11 -Wall -Werror -O2 -c ahencode.cpp

ahdecode.o: ahdecode.cpp ahdecode.h
	g++ -std=c++11 -Wall -Werror -O2 -c ahdecode.cpp
