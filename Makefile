CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
LFLAGS=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)

FILES=src/s21_smart_calc.c src/s21_depos_calc.c src/s21_credit_calc.c

all: install clean

s21_smart_calc.a: obj
	@ar rcs s21_smart_calc.a s21_smart_calc.o s21_depos_calc.o s21_credit_calc.o
	@ranlib s21_smart_calc.a

obj: $(FILES)
	@$(CC) $(CFLAGS) -c $(FILES)

install:
	@mkdir -p build
	@cd build && qmake6 ../Calc\ v1.0.pro && $(MAKE) install -j6
	@cd build && $(MAKE) clean
	@mv ${HOME}/Calculator/Calculator.app ~/Desktop/
	@rm -r ${HOME}/Calculator

uninstall:
	rm -rf ~/Desktop/Calculator.app

test: s21_smart_calc.a
ifeq ($(OS), Darwin)
	@$(CC) $(CFLAGS) src/s21_test.c s21_smart_calc.a -o s21_test.out $(LIBS)
	@./s21_test.out
else
	@$(CC) $(CFLAGS) src/s21_test.c s21_smart_calc.a -o s21_test.out $(LIBS) $(LINUX)
	@./s21_test.out
endif

gcov_report:
ifeq ($(OS), Darwin)
	@$(CC) $(CFLAGS) $(LFLAGS) src/s21_test.c $(FILES) -o s21_test.out $(LIBS)
else
	@$(CC) $(CFLAGS) $(LFLAGS) src/s21_test.c $(FILES) -o s21_test.out $(LIBS) $(LINUX)
endif
	@./s21_test.out
	@lcov -t "test" -o s21_test.info -c -d .
	@genhtml -o report s21_test.info
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info

check:
	@clang-format --style=Google --dump-config > .clang-format
	@echo "==========================================="
	@echo "======= Clang-format test started.. ======="
	@clang-format -n */*.c */*.h
	@echo "==========================================="
	@echo "========= Cppcheck test started.. ========="
	@cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config */*.c
	@echo "=========== All tests finished. ==========="
	@echo "==========================================="
	@rm -r .clang-format

open:
	open ~/Desktop/Calculator\ 1.0.app

open_report:
ifeq ($(OS), Darwin)
	@open report/index.html
else
	@xdg-open report/index.html
endif

dvi:
	@open info.md -a Visual\ Studio\ Code

dist:
	@mkdir -p SmartCalc-1.0
	@mkdir -p SmartCalc-1.0/include
	@mkdir -p SmartCalc-1.0/src
	@mkdir -p SmartCalc-1.0/ui
	@mkdir -p SmartCalc-1.0/resource
	@cp src/* SmartCalc-1.0/src/
	@cp include/* SmartCalc-1.0/include/
	@cp ui/* SmartCalc-1.0/ui/
	@cp resource/* SmartCalc-1.0/resource/
	@cp Makefile SmartCalc-1.0/
	@cp Calc\ v1.0.pro SmartCalc-1.0/
	@cp resource.qrc SmartCalc-1.0/
	@tar -cf SmartCalc-1.0.tar SmartCalc-1.0
	@rm -rf SmartCalc-1.0

rebuild: clean all

clean:
	@rm -rf *.o *.a *.out s21_test.out *.dSYM ./report ./build/*
