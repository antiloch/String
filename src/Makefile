CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TEST_FLAGS = -lcheck

BUILD_DIR=build
BUILD_TEST_DIR=$(BUILD_DIR)/tests
BUILD_SPECS_DIR=$(BUILD_DIR)/s21_specs
SRCS=$(wildcard s21_*.c s21_specs/s21_*.c)
OBJS=$(SRCS:%.c=$(BUILD_DIR)/%.o)
TEST_SRCS=$(wildcard tests/*.c)

LIB_NAME=s21_string.a

all: clean $(LIB_NAME) 

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_SPECS_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

$(LIB_NAME): $(OBJS)
	@echo Creating $(LIB_NAME) library...
	@ar rc $(LIB_NAME) $^
	@ranlib $(LIB_NAME)
	@echo "\033[1;42m DONE \033[0m"

test: $(LIB_NAME)
	@echo Creating tests...
	@$(CC) $(FLAGS) $(TEST_SRCS) -L. $(LIB_NAME) $(TEST_FLAGS) -o test
	@./test

add_coverage_flag:
	$(eval FLAGS += --coverage)	

# add_coverage_flag:
# 	$(CC) $(FLAGS) $(SRCS) $(TEST_SRCS) -o test --coverage

# gcov_report: add_coverage_flag test
# 	# ./test
# 	@rm -rf *.gcno *gcda *.gcov
# 	gcov $(BUILD_DIR)/*.gcno
# 	geninfo $(BUILD_DIR)/ -b ./ -o report.info
# 	genhtml -o report report.info;
# # lcov --c --directory . --output-file coverage.info
# # genhtml coverage.info --output-directory gcov_report
# 	# rm -rf *.info *.gcda *.gcno
# 	# open report/index.html

gcov_report: clean add_coverage_flag test
	@mkdir -p html
	@gcov -b -l -p -c $(BUILD_DIR)/*.gcno
	@rm -rf *.gcno *gcda *.gcov
	lcov --c --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	@gcovr -o html/gcov_report.html --html --html-details
	@open html/gcov_report.html

clean:
	@echo Cleaning...
	@rm -rf build/
	@rm -rf s21_specs/*.o s21_specs/*.gcno s21_specs/*.gcda
	@rm -rf tests/*.o tests/*.gcno tests/*.gcda
	@rm -rf *.o *.a *.gcno *.gcda *.gcov
	@rm -rf html/
	@rm -rf a.out test
	@rm -rf *.css
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