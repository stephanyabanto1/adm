servo:
	gcc servo.cpp -lstdc++ -lwiringPi -lpthread -o exec 
	./exec

gyro:
	gcc gyro.cpp -lstdc++ -lwiringPi -lpthread -o exec -lm
	./exec

test:
	gcc test.cpp -lstdc++ -o test
	./test
	rm test

clean: 
	rm exec