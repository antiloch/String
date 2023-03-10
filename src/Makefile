CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TST_LIBS = -lcheck

SRCS=$(wildcard s21_*.c s21_specs/s21_*.c)

OBJS=$(SRCS:.c=.o)

LIB_NAME=s21_string

all: clean $(LIB_NAME).a 

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(LIB_NAME).a: $(OBJS)
	ar rc $(LIB_NAME).a $^
	ranlib $(LIB_NAME).a

test: clean $(LIB_NAME).a
	$(CC) $(FLAGS) tests/*.c -L. $(LIB_NAME).a $(TST_LIBS) -o test
	./test

add_coverage_flag:
	$(eval FLAGS += --coverage)	

gcov_report: add_coverage_flag test 
	./test
	mkdir -p html
	gcov -b -l -p -c s21_*.gcno 
	gcovr -o html/gcov_report.html --html --html-details
	open html/gcov_report.html

clean:
	@echo Cleaning...
	@rm -rf build/
	@rm -rf html/
	@rm -rf s21_specs/*.o s21_specs/*.gcno s21_specs/*.gcda s21_specs/*.gcov
	@rm -rf tests/*.o
	@rm -rf *.o *.gcno *.gcda *.gcov
	@rm -rf *.html
	@rm -rf a.out test
	@rm -rf *.a
	@rm -rf *.css
	@rm -rf *.gch $(TEST_DIR)/*.gch
	@rm -rf ./external/external
	@echo "\033[1;42m DONE \033[0m"

style: 
	@echo Style...
	@mv ../materials/linters/.clang-format ./
	@clang-format -i *.c
	@clang-format -i *.h
	@clang-format -i s21_specs/*.c
	@clang-format -i tests/*.c
	@mv .clang-format ../materials/linters
	@echo "\033[1;42m DONE \033[0m"
