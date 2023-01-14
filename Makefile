main:
	gcc main.cpp -lstdc++ -lwiringPi -lpthread -o exec 
	./exec

test:
	gcc test.cpp -lstdc++ -o test
	./test

clean: 
	rm test
	rm exec