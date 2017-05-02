
all:
	gcc -Wall -Wshadow -g -lm -Wno-unused-variable  test.c  -o test 
	valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log ./test .5 .4 1.2 10000  && cat memcheck.log | tail -n 1 && cat proj1-a_output
