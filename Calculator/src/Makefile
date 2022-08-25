CC=gcc
CFLAGS=-c -std=c11 -Wall -Werror -Wextra -lm
CFLAGS2=-fprofile-arcs -ftest-coverage
WASH=rm -rf *.o *.a *.out *.log *.aux *.dvi *.toc *css *gcno *gcda CPPLINT.cfg *tgz *.html man_ru
OS=$(shell uname)

ifeq ($(OS), Linux)
	LFLAGS = -lcheck -lm -pthread -lgcov --coverage -lrt -lsubunit
	LEAKS=CK_FORK=no valgrind --leak-check=full --track-origins=yes -s ./test.out
else
	LFLAGS = -lcheck -pthread -lgcov --coverage
	LEAKS=CK_FORK=no leaks --atExit -- ./test.out
endif

all: clean calculate.a tests gcov_report

install:
	mkdir build
	cp Calculator.pro ./build
	cp *.c *.h *.cpp *.ui ./build
	cd build; qmake Calculator.pro
	make -C build
	cd build; rm -rf *.c *.h *.cpp *.ui *.o
	mkdir $(HOME)/Desktop/SmartCalc/
	cp -rf build/Calculator.app $(HOME)/Desktop/SmartCalc/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/SmartCalc/
	rm -rf build

dvi:
	makeinfo --html --no-warn --no-validate --force ./man_ru.texi

dist:
	rm -rf MyCalc
	mkdir MyCalc
	cp Makefile *.c *.h *.pro *.texi *.cpp *.ui *.user MyCalc/
	tar -zcvf ./MyCalc.tar.tgz ./MyCalc
	rm -rf MyCalc/

calculate.a: calculate.o stack.o pars.o rpn.o
	ar rc calculate.a calculate.o stack.o pars.o rpn.o
	ranlib calculate.a

main: main.o stack.o pars.o rpn.o calculate.o
	$(CC) $^ -lm -o main.out && ./main.out

main.o: main.c
	$(CC) $(CFLAGS) $^

stack.o: stack.c
	$(CC) -c $^

pars.o: pars.c
	$(CC) -c $^

rpn.o: rpn.c
	$(CC) -c $^

calculate.o: calculate.c
	$(CC) -lm -c $^

gcov_report: tests
	gcovr -r . --html --html-details -o gcov_report.html
	open gcov_report.html

tests: stack_test.o pars_test.o rpn_test.o calculate_test.o test.o
	$(CC) $^ -o test.out $(LFLAGS) && ./test.out

stack_test.o: stack.c
	$(CC) $(CFLAGS) $(CFLAGS2) -c $^ -o $@

pars_test.o: pars.c
	$(CC) $(CFLAGS) $(CFLAGS2) -c $^ -o $@

rpn_test.o: rpn.c
	$(CC) $(CFLAGS) $(CFLAGS2) -c $^ -o $@

calculate_test.o: calculate.c
	$(CC) $(CFLAGS) $(CFLAGS2) -c $^ -o $@

tests.o: test.c
	$(CC) $(CFLAGS2) -c $^ -o $@

check_python: main.c stack.c pars.c rpn.c calculate.c stack.h pars.h rpn.h calculate.h test.c
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c $^
	python3 ../materials/linters/cpplint.py --extensions=cpp mainwindow.cpp mainwindow.h input_x.cpp input_x.h graph.cpp graph.h depositcalc.cpp depositcalc.h creditcalc.cpp creditcalc.h

check_leaks:
	$(LEAKS)

check_cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem main.c stack.c pars.c rpn.c calculate.c test.c

clean:
	$(WASH)