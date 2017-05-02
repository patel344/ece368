
#all:
#	gcc -Wall -Wshadow -g -lm -lc  test2.c  -o test 
#	valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log ./test input.txt  && cat memcheck.log | tail -n 1 && cat proj1_output
all:
	gcc -Wall -Wshadow -g -lm -lc  test2.c  -o test
	valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log ./test .24 .56 .2 10000  && cat memcheck.log | tail -n 1 && cat proj1_output
 #-Wno-unused-variable
