project 			 := march23

# ==============================
# Folder Paths
# ==============================
# These variables store where things are located in the project

inc_dir 			 := ./include
src_dir 			 := ./src
test_dir 			 := ./test
unit_test_dir 		 := ${test_dir}/unit
integration_test_dir := ${test_dir}/integration

# ==============================
# File Paths
# ==============================
# `wildcard` finds all files that match a pattern

sources 			 := $(wildcard ${src_dir}/*.c)
unit_tests 			 := $(wildcard ${unit_test_dir}/*.cpp)
integration_tests 	 := $(wildcard ${integration_test_dir}/*.bats)

# ==============================
# Build Output Folders
# ==============================

build_dir   		 := ./build
obj_dir 			 := ${build_dir}/obj
bin_dir 			 := ${build_dir}/bin
unit_test_build_dir  := ${build_dir}/test/unit
integration_build_dir:= ${build_dir}/test/integration

# ==============================
# Required Build Folders
# ==============================
# These must exist before compiling

build_dirs 			 := ${obj_dir} ${bin_dir} ${unit_test_build_dir}

# ==============================
# Final Executable
# ==============================
# This is the path to the final program we create

executable 			 := ${bin_dir}/${project}

# ==============================
# Object Files
# ==============================
objects 			 := $(subst .c,.o,$(subst ${src_dir},${obj_dir},${sources}))

# ==============================
# Unit Test Target
# ==============================
# This is the compiled unit test program

all_unit_tests 	     := ${unit_test_build_dir}/all_tests

# ==============================
# Compiler Settings
# ==============================

CC      			 := gcc 
CFLAGS				 := -I${inc_dir} -g -Wall -std=c11 -O0

# CFLAGS options:
# -g 			Compile with debug symbols in binary files
# -Wall 		Warnings: all - display every single warning
# -std=c11  	Use the C2011 feature set
# -I${inc_dir}  Look in the include directory for include files
# -O0 			Disable compilation optimizations

# ==============================
# Phony Targets
# ==============================
# These are commands, not actual files

.PHONY: all run test unit-test integration-test debug lint clean 
.PHONY: leak-check help variables path-to-bin

# ==============================
# Default Target
# ==============================
# Running just "make" will build the project

all: ${executable}

# ==============================
# Help Command
# ==============================
# Shows available commands

help:
	@echo "Available make commands:"
	@echo "  make all              Build the project"
	@echo "  make run              Run the program"
	@echo "  make test             Run all tests"
	@echo "  make unit-test        Run unit tests"
	@echo "  make integration-test Run integration tests"
	@echo "  make clean            Delete build files"

# ==============================
# Run the Program
# ==============================
# Build first, then run it

run: ${executable}
	@${^}

# ==============================
# Link Step (Final Build Step)
# ==============================
# Combine all object files into one executable

${executable}: ${objects} | ${bin_dir}
	${CC} ${CFLAGS} -o ${@} ${^}

# $@ = name of the target (the executable)
# $^ = all dependencies (object files)

# ==============================
# Compile Step
# ==============================
# Turn each .c file into a .o file

${obj_dir}/%.o: ${src_dir}/%.c | ${obj_dir}
	${CC} ${CFLAGS} -c -o ${@} ${<}

# $< = first dependency (the .c file)

# ==============================
# Create Folders
# ==============================
# The build directories should be recreated when prerequisite
# mkdir -p creates folders if they don’t exist

${build_dirs}:
	mkdir -p ${@}


# ==============================
# Testing
# ==============================
# Run all tests

test: unit-test integration-test

# ------------------------------
# Unit Tests
# ------------------------------
# Run the unit testing of the project 

unit-test: ${all_unit_tests}
	@echo "=== UNIT TESTS ==="
	${^}

# Run specific groups of tests

test-array: ${all_unit_tests}
	@echo "=== RUNNING ONLY array TESTS ==="
	${all_unit_tests} --gtest_filter=array_utils*

# Run only the tests whose names match "math.add*"
test-add: ${all_unit_tests}
	@echo "=== RUNNING ONLY add TESTS ==="
	${all_unit_tests} --gtest_filter=math.add*

# Run only the tests whose names match "math.subtract*"
test-sub: ${all_unit_tests}
	@echo "=== RUNNING ONLY sub TESTS ==="
	${all_unit_tests} --gtest_filter=math.subtract*

# Build unit tests using script

${all_unit_tests}: ${unit_tests} ${sources}
	bash support/test/unit/make.sh

${unit_test_build_dir}/%_tests: ${unit_test_dir}/%.cpp
	bash support/test/unit/make.sh

# ------------------------------
# Integration Tests
# ------------------------------
integration-test: ${executable} ${integration_tests}
	@echo "=== INTEGRATION TESTS ==="
	bash support/test/integration/make.sh

${integration_build_dir}/%.bats: ${integration_test_dir}/%.bats
	bash support/test/integration/make.sh

# ==============================
# Memory Leak Check
# ==============================
# Use valgrind to find memory issues

leak-check: ${executable}
	valgrind --leak-check=full ${^}

# ==============================
# Clean
# ==============================
# Delete all artifacts produced in the build process
# (Delete everything in build/)
clean:
	rm -rf ${build_dir}

# ==============================
# Print Variables
# ==============================
# Useful for debugging the Makefile itself
variables:
	@echo "Sources: ${sources}"
	@echo "Unit Tests: ${unit_tests}"
	@echo "Executable: ${executable}"
	@echo "Build Dirs: ${build_dirs}"
	@echo "Objects: ${objects}"
	@echo "C Compiler: ${CC}"
	@echo "C Compiler Flags: ${CFLAGS}"

# ==============================
# Show Executable Path
# ==============================
path-to-bin:
	@echo ${executable}