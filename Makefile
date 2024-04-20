all: program

program:
	@g++ *.cpp -I . -o exe
	@rm -rf *.o
run: program
	@./exe
debug:
	@g++ *.cpp -I . -o exe -g
	@rm -rf *.o

clean:
	@rm -f exe