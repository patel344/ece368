
all:
	gcc -Wall -Wshadow -g -lm -Wno-unused-variable  project3.c  -o project3
	valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log ./project3 inputTxt>output.txt && cat memcheck.log | tail -n 1 
