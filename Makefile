all: program

program:
	@g++ *.cpp -I . -o exe
	@rm -rf *.o
run: program
	@./exe
clean:
	@rm -f exe