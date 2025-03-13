# Default flags (optional)
CXXFLAGS += -g -Wall -Wextra

# Flags required by the source code
override CXXFLAGS += -std=c++14

# Flags required by the Makefile
override CPPFLAGS += -MMD -MP

# Source files
SRCS := $(wildcard *.cc)
EXE_SRCS := scrambler.cc
TEST_SRCS := $(wildcard test_*.cc)

# Substitution references used by the Makefile
OBJS = $(SRCS:%.cc=%.o)
DEPS = $(SRCS:%.cc=%.d)

EXES = $(EXE_SRCS:%.cc=%)
TESTS = $(TEST_SRCS:%.cc=%)
NON_EXE_OBJS = $(filter-out $(EXE_SRCS:%.cc=%.o) $(TEST_SRCS:%.cc=%.o),$(OBJS))

.PHONY: all

all: scrambler

scrambler: scrambler.o $(NON_EXE_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

test_CipherString: test_CipherString.o $(NON_EXE_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.PHONY: test clean

test: $(TESTS)
	./test_CipherString

clean:
	$(RM) $(OBJS) $(DEPS) $(EXES)

# Include rules for source code dependencies
-include $(DEPS)
