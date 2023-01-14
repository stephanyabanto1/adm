main:
	gcc main.cpp -o exec -lwiringPi -lpthread

test:
	gcc test.cpp -o test