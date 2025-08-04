INPUT := $(shell find . -name '*.cc')
COMPILE := $(patsubst %.cc, %.compile, $(INPUT))

.PHONY: compile
compile: $(COMPILE) std_testcase.compile

%.compile: %.cc std_testcase.h
	gcc -c $< -o /dev/null -I.
