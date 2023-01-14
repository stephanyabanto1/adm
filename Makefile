main:
	gcc main.cpp -lstdc++ -lwiringPi -lpthread -o exec 

test:
	gcc test.cpp -lstdc++ -o test