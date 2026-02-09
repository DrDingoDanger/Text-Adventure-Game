# Revision History -- at the bottom of the document
################################################################################
# The targets in this file are used in .gitlab-ci.yml and  the files created
# are found in the .gitignore
################################################################################
# Changing any names below can change the target names which will require that
# you update .gitlab_ci.yml and .gitignore
################################################################################

################################################################################
# Variable definitions
################################################################################

# Executable names
PROJECT = game
COMPILE= play_${PROJECT}
GTEST = test_${PROJECT}

# Compilation command and flags
CXX=g++
CXXVERSION= -std=c++14
CXXFLAGS= ${CXXVERSION} -g
CXXWITHCOVERAGEFLAGS = ${CXXFLAGS} -fprofile-arcs -ftest-coverage
LINKFLAGS= -lgtest

# Directories
SRC_DIR = src
PROJECT_SRC_DIR = src/project
GTEST_DIR = test
SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

# Tool variables
GCOV = gcov
LCOV = lcov
COVERAGE_RESULTS = results.coverage
COVERAGE_DIR = coverage
STATIC_ANALYSIS = cppcheck
STYLE_CHECK = cpplint
DESIGN_DIR = docs/design
DOXY_DIR = docs/code

################################################################################
# Targets
################################################################################

# Default goal
.DEFAULT_GOAL := compileProject

################################################################################
# Clean-up targets
################################################################################

.PHONY: clean-cov
clean-cov:
	rm -rf *.gcov *.gcda *.gcno ${COVERAGE_RESULTS} ${COVERAGE_DIR}

.PHONY: clean-docs
clean-docs:
	rm -rf docs/code/src/ docs/code/*.bak

.PHONY: clean-exec
clean-exec:
	rm -rf ${PROJECT} ${GTEST} ${PROJECT}.exe ${GTEST}.exe

.PHONY: clean-obj
clean-obj:
	rm -rf ${SRC}/*.o

.PHONY: clean-temp
clean-temp:
	rm -rf *~ \#* .\#* \
	${SRC_DIR}/*~ ${SRC_DIR}/\#* ${SRC_DIR}/.\#* \
	${GTEST_DIR}/*~ ${GTEST_DIR}/\#* ${GTEST_DIR}/.\#* \
	${SRC_INCLUDE}/*~ ${SRC_INCLUDE}/\#* ${SRC_INCLUDE}/.\#* \
	${PROJECT_SRC_DIR}/*~ ${PROJECT_SRC_DIR}/\#* ${PROJECT_SRC_DIR}/.\#* \
	${DESIGN_DIR}/*~ ${DESIGN_DIR}/\#* ${DESIGN_DIR}/.\#* \
	static.rpt *.gcov *.gcda *.gcno 

.PHONY: clean
clean: clean-cov clean-docs clean-exec clean-obj clean-temp

################################################################################
# Compilaton targets
################################################################################

# default rule for compiling .cc to .o
%.o: %.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

# Compilation targets

# compilation for performing testing - used by .gitlab-ci.yml
# using the files in include, src, and test, but not src/project
${GTEST}: ${GTEST_DIR} ${SRC_DIR} clean-exec
	${CXX} ${CXXFLAGS} -o ./${GTEST} ${INCLUDE} \
	${GTEST_DIR}/*.cpp ${SRC_DIR}/*.cpp ${LINKFLAGS}

# compilation for making the project
# using the files in include, src, and src/project, but not test
${COMPILE}: ${SRC_DIR} ${PROJECT_SRC_DIR} clean-exec
	${CXX} ${CXXVERSION} -o ${PROJECT} ${INCLUDE} \
	${SRC_DIR}/*.cpp ${PROJECT_SRC_DIR}/*.cpp

compileProject: ${COMPILE}

################################################################################
# Test targets
################################################################################

# To perform all tests
all: ${GTEST} memcheck coverage docs static style

# To perform the memory checks - used by .gitlab-ci.yml
memcheck: ${GTEST}
	valgrind --tool=memcheck --leak-check=yes --error-exitcode=1 ./${GTEST}

# To perform the memory checks, reports more details that memcheck
fullmemcheck: ${GTEST}
	valgrind --tool=memcheck --leak-check=full --error-exitcode=1 ./${GTEST}

# To perform the code coverage checks - used by .gitlab-ci.yml
coverage: clean-exec clean-cov
	${CXX} ${CXXWITHCOVERAGEFLAGS} -o ./${GTEST} ${INCLUDE} \
	${GTEST_DIR}/*.cpp ${SRC_DIR}/*.cpp ${LINKFLAGS}
	./${GTEST}
	# Determine code coverage
	${LCOV} --capture --ignore-errors mismatch --gcov-tool ${GCOV} --directory . --output-file ${COVERAGE_RESULTS} --rc branch_coverage=1
	# Only show code coverage for the source code files (not library files)
	${LCOV} --extract ${COVERAGE_RESULTS} */*/*/${SRC_DIR}/* -o \
	${COVERAGE_RESULTS}
	#Generate the HTML reports
	genhtml ${COVERAGE_RESULTS} --output-directory ${COVERAGE_DIR}
	#Remove all of the generated files from gcov
	make clean-temp

# To perform the static check - used by .gitlab-ci.yml
static: ${SRC_DIR}
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR} \
	${SRC_INCLUDE} --suppress=missingInclude --suppress=missingIncludeSystem --error-exitcode=1

# To perform the static check and creates detailed report called static.rpt
staticRpt: ${SRC_DIR}
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR} --checkers-report=static.rpt \
	${SRC_INCLUDE} --suppress=missingInclude --suppress=missingIncludeSystem --error-exitcode=1

# To perform the style check - used by .gitlab-ci.yml
style: ${SRC_DIR} ${GTEST_DIR} ${SRC_INCLUDE} ${PROJECT_SRC_DIR}
	${STYLE_CHECK} ${SRC_DIR}/* ${GTEST_DIR}/* ${SRC_INCLUDE}/* \
	${PROJECT_SRC_DIR}/*

################################################################################
# Documentation target
################################################################################

# To produce the documentation - used by .gitlab-ci.yml
.PHONY: docs
docs: ${SRC_INCLUDE}
	doxygen ${DOXY_DIR}/doxyfile

# To produce version report - used by .gitlab-ci.yml
.PHONY: version
version:
	doxygen --version
	cppcheck --version
	cpplint --version
	gcc --version
	${CXXVERSION}
	gcov --version
	lcov --version
	valgrind --version

################################################################################
# Revision History
################################################################################
# Updated: 2026-01-08 Nicole wilson <n.wilson@uleth.ca>
#  Changed static checker to not check any files in test/
#  Added notes indicating which targets are used by .gitlab-ci.yml
#  Added fullmemcheck and staticRpt targets
################################################################################
# Updated: 2026-01-07 Nicole wilson <n.wilson@uleth.ca>
#  Added --suppress=missingIncludeSystem to the static check command
#  Updated the code coverage command
################################################################################
# Updated: 2022-12-15 Nicole Wilson <n.wilson@uleth.ca>
#  Removed all references to OS as the pipelines are now running on Ubuntu
################################################################################
# Updated: 2022-10-19 Dr. J. Anvik <john.anvik@uleth.ca>
#  Changed the static command to make the pipeline fail on exit with errors.
################################################################################
# Updated: 2022-09-11 Nicole Wilson <n.wilson@uleth.ca>
#  Added reference to OS in setting of STYLE_CHECK.
#  This is a temporary measure until the pipelines are running on Ubuntu
################################################################################
