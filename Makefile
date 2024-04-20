all: program

program:
	@g++ main.cpp participant.cpp activity.cpp -I . -o exe
	@rm -rf *.o
binary:
	@g++ LabBinWrite.cpp -I . -o exe
run: program
	@./exe
debug:
	@g++ main.cpp participant.cpp activity.cpp -I . -o exe -g
	@rm -rf *.o

clean:
	@rm -f exe