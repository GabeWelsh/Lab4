all: program

program:
	@g++ main.cpp activity.cpp participant.cpp -I . -o exe -O2
	@rm -rf *.o
run: program
	@./exe
debug:
	@g++ *.cpp -I . -o exe -g
	@rm -rf *.o
file:
	@g++ file.cpp participant.cpp activity.cpp -I . -o exe
	@./exe
	@rm -rf *.o exe
clean:
	@rm -f exe