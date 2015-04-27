
all:
	gcc -Wall -Wshadow -g -lm -Wno-unused-variable  project3.c  -o project3 && ./project3 inputTxt>output.txt
	gcc -Wall -Wshadow -g -lm -Wno-unused-variable  project3.c  -o project3 && ./project3 inputTxt1>output1.txt
	gcc -Wall -Wshadow -g -lm -Wno-unused-variable  project3.c  -o project3 && ./project3 inputTxt2>output2.txt
	gcc -Wall -Wshadow -g -lm -Wno-unused-variable  project3.c  -o project3 && ./project3 inputTxt3>output3.txt
	gcc -Wall -Wshadow -g -lm -Wno-unused-variable  project3.c  -o project3 && ./project3 inputTxt4>output4.txt
	gcc -Wall -Wshadow -g -lm -Wno-unused-variable  project3.c  -o project3 && ./project3 inputTxt5>output5.txt
	gcc -Wall -Wshadow -g -lm -Wno-unused-variable  project3.c  -o project3 && ./project3 inputTxt6>output6.txt

valgrind: valgrind --tool=memcheck --leak-check=full --verbose --log-file=memcheck.log ./project3 inputTxt5>output5.txt && cat memcheck.log | tail -n 1 
