# CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11 -g
# TST_LIBS = -lcheck

######################################################################

LIB = s21_string.a
TEST_LIB = $(addprefix test_, $(LIB))

CC = gcc
GCOV = gcov

#Изменение компилятора под gcc-12 на M1
ifeq ($(shell uname -p), arm)
		CC = gcc-12
		GCOV = gcov-12
endif

TEST_FLAGS = -lcheck
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
    TEST_FLAGS = -lcheck
else
 TEST_FLAGS = -lcheck -lpthread -pthread -lrt -lm -lsubunit
endif

TEST_DIR = tests
BUILD_DIR = build
BUILD_TEST_DIR = build_tests
TEST_BUILD_DIR = test_build
GCOV_DIR = gcov_report

S21_SOURCES = $(wildcard s21_*.c s21_specs/s21_*.c)
TESTS = $(wildcard $(TEST_DIR)/*.c)
S21_OBJECTS=$(addprefix $(BUILD_DIR)/, $(S21_SOURCES:.c=.o))
TEST_S21_OBJECTS=$(addprefix $(TEST_BUILD_DIR)/, $(S21_SOURCES:.c=.o))
TEST_OBJECTS=$(addprefix $(BUILD_TEST_DIR)/, $(notdir $(TESTS:.c=.o)))


test: $(TEST_OBJECTS) $(TEST_LIB)
	$(CC) $(FLAGS) $^ -o $@ $(CHFLAGS) $(GOFLAGS) $(TEST_FLAGS)

$(TEST_OBJECTS) : $(BUILD_TEST_DIR)/%.o : $(TEST_DIR)/%.c $(TEST_DIR)/test_me.h
	@mkdir -p $(BUILD_TEST_DIR)/s21_specs
	$(CC) $(FLAGS) $(IN_FLAGS) $(TEST_FLAGS)  -c $< -o $@

$(TEST_LIB): $(TEST_S21_OBJECTS)
	ar -rcs $@ $^

$(TEST_S21_OBJECTS): $(TEST_BUILD_DIR)/%.o : %.c $(LIB:.a=.h) 
	@mkdir -p $(TEST_BUILD_DIR)/s21_specs
	$(CC) $(FLAGS) $(OPTFLAGS) $(GFLAGS) -c $< -o $@

$(LIB): $(S21_OBJECTS)
	ar -rcs $@ $^

#формируем обьектные файлы для библиотеки
$(S21_OBJECTS): $(BUILD_DIR)/%.o : %.c $(LIB:.a=.h)  
	@mkdir -p $(BUILD_DIR)/s21_specs
	$(CC) $(FLAGS) -c $< -o $@

# ######################################################################

SRCS=$(wildcard s21_*.c s21_specs/s21_*.c)

OBJS=$(SRCS:.c=.o)

LIB_NAME=s21_string

all: clean $(LIB_NAME).a 

clean:
	@echo Cleaning...
	@rm -rf $(GCOV_DIR) $(BUILD_DIR) $(BUILD_TEST_DIR) $(TEST_BUILD_DIR)
	@rm -rf s21_specs/*.o
	@rm -rf *.o
	@rm -rf *.html
	@rm -rf a.out test
	@rm -rf *.a
	@rm -rf *.css
	@rm -rf *.gch $(TEST_DIR)/*.gch
	@rm -rf ./external/external
	@echo "\033[42m DONE \033[0m"

# clean:
# 	rm -rf *.o test *.a *.gcno *.gcda *.gcov *.html *.css
# 	rm -rf s21_specs/*.o s21_specs/*.a s21_specs/*.gcno s21_specs/*.gcda s21_specs/*.gcov s21_specs/*.html s21_specs/*.css
# 	rm -rf html/

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

# $(LIB_NAME).a: $(OBJS)
# 	ar rc $(LIB_NAME).a $^
# 	ranlib $(LIB_NAME).a

# test: clean $(LIB_NAME).a
# 	$(CC) $(FLAGS) test*.c -L. $(LIB_NAME).a $(TST_LIBS) -o test
# 	./test

add_coverage_flag:
	$(CC) $(FLAGS) $(SRCS) test*.c -o test --coverage

gcov_report: add_coverage_flag 
	./test
	mkdir -p html
	gcov -b -l -p -c s21_*.gcno 
	gcovr -o html/gcov_report.html --html --html-details
	open html/gcov_report.html


style: 
	@echo Style...
	@mv ../materials/linters/.clang-format ./
	@clang-format -i *.c
	@clang-format -i *.h
	@clang-format -i s21_specs/*.c
	@clang-format -i tests/*.c
	@mv .clang-format ../materials/linters
	@echo "\033[42m DONE \033[0m"
