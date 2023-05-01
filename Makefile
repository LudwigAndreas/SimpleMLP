# Application name
NAME = SimpleMLP
TEST_NAME = $(BUILD_DIR)/SimpleMLP_tests

# Project Version
VERSION = 1.0

# Compiler and linker settings
OS = $(shell uname)
CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++17 -Ofast -march=native 
LDFLAGS = -L./$(LIB_PATH) -l$(LIB_POSTFIX)
INCDIRS = -I./ 
QT_LIBS = -framework QtWidgets -framework QtGui -framework QtCore
ifeq ($(OS), Darwin)
	LDFLAGS += -mmacosx-version-min=12.6 -lm -lgtest -lstdc++ 
	LDFLAGS += -lQt6Gui -lQt6Widgets -lQt6Charts
else
	LDFLAGS += 
endif

# Directories
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
TEST_BUILD_DIR = $(BUILD_DIR)/tests
BIN_DIR = bin
INSTALL_PATH = /usr/bin
DIST_PATH = dist

# Source files
SRC_FILES =		gui/main.cc\
				core/matrix/MLPMatrixLayer.cc\
				core/matrix/MLPMatrixModel.cc\
				core/DatasetReading.cc\
				core/LetterRecognitionMlpModelBuilder.cc\
				core/graph/MLPGraphLayer.cc\
				core/graph/MLPGraphModel.cc\
				core/graph/MLPGraphNode.cc\
				core/utils/ActivationFunction.cc\
				gui/utils/ModelTestWorker.cc\
				gui/utils/ModelTrainWorker.cc\
				gui/utils/ModelWorker.cc\
				gui/utils/importfileitem.cc\
				gui/utils/paintview.cc\
				gui/view/ConfigureModulePage.cc\
				gui/view/TestModelPage.cc\
				gui/view/TrainModelPage.cc\
				gui/view/mainwindow.cc\
				gui/view/testdatainfodialog.cc

SRCS = $(addprefix $(SRC_DIR)/,$(SRC_FILES))

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cc,$(BUILD_DIR)/%.o,$(SRCS))

# Static library
LIB_POSTFIX = s21
LIB_NAME = lib$(LIB_POSTFIX)
LIB_DIR = $(SRC_DIR)/libs21
LIB_PATH = $(LIB_DIR)/lib
LIB = $(LIB_PATH)/$(LIB_NAME)

# Test source files
TEST_FILES =	tests/main.cc\
				tests/core/matrix/MatrixTest.cc\
				tests/core/utils/ActivationFunctionTest.cc\
				tests/core/utils/BMPReaderTest.cc\
				tests/core/DatasetReadingTest.cc\
				tests/core/MLPBuilderTest.cc\
				tests/core/graph/GraphLayerTest.cc\
				tests/core/graph/GraphModelTest.cc\
				tests/core/graph/GraphTest.cc\
				tests/core/matrix/MatrixModelTest.cc

TESTS = $(addprefix $(TEST_DIR)/,$(notdir $(TEST_FILES)))

all: $(BIN_DIR)/$(NAME)

$(BIN_DIR)/$(NAME): $(OBJS)
	echo
	echo -e "\033[1;33m"$(NAME) "objs are up to date."'\033[0m'
	make -C $(LIB_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCDIRS) $(QT_LIBS) $(OBJS) -o $(NAME)
	echo -e "\033[1;43m"$(NAME) "is up to date."'\033[0m'

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	mkdir -p $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c -o $@ $<
	printf "\033[1;36m/\033[0m"

install: $(BIN_DIR)/$(NAME)
	cp $(BIN_DIR)/$(NAME) $(INSTALL_PATH)
	
	
uninstall:
	rm -f $(INSTALL_PATH)/$(NAME)

dist:
	mkdir -p $(DIST_PATH)
	tar czf $(DIST_PATH)/$(NAME)-$(VERSION).tar.gz $(SRC_DIR) Makefile README.md LICENSE 

# dvi:

tests: $(OBJS)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCDIRS) $(TEST) -o $(TEST_NAME)
	./$(TEST_NAME)

leaks: tests
ifeq ($(OS), Darwin)
	leaks -atExit -- ./$(TEST_NAME)
else
	@echo "I do not know how to run leaks test on linux"
endif

clean:
	@make -C $(LIB_DIR) clean
	@rm -f $(OBJS)
	@rm -f $(BUILD_DIR)
	@echo '\033[1;31m'"$(LIB) deleted."'\033[0m'

fclean: clean
	@make -C $(LIB_DIR) fclean
	@rm -f $(NAME)
	@echo -e '\033[1;31m'$(NAME) "deleted."'\033[0m'

re: fclean all

.PHONY: all clean fclean re test leaks