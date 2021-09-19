SRCS = expr.c fatal.c main.c match.c scan.c stmt.c tree.c
NAME = abacusCompiler

comp1: $(SRCS)
	gcc -o $(NAME) -g $(SRCS)

clean:
	rm -f comp1 *-o *.s out


# Tests
#
# File Names
F_TEST01 = ./testing/test01.abc
#First step is to compile the program
# Then Execute the compiled program (WHich doesnt exist yet, we building itermediete code rep first)


test01: $(NAME).exe $(F_TEST01)
	@echo ">>Starting Test 01"
	./$(abacusCompiler).exe  $(F_TEST01)
	@echo ">>Finished Test 01"


# This tests all tests in order to ensure everything still passes when features are added
RegressionTest: test01
	@echo "Completed RegressionTest"
