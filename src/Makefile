# Application name
NAME = SimpleMLP

# Project Version
VERSION = 1.0

# Make and cmake settings
CMAKE = cmake
CMAKE_FLAGS = -DCMAKE_PREFIX_PATH=$(QT_PATH) -DCMAKE_BUILD_TYPE=Release
OS = $(shell uname)
ifeq ($(OS), Linux)
  OPEN=xdg-open
else
  OPEN=open
endif

# Directories
# To create the folders and structure of the project more correctly, put the Makefile in the root of the project and change the SRC variable from '.' to 'src'
SRC_DIR = .
TEST_DIR = tests
BUILD_DIR = build
TEST_BUILD_DIR = $(BUILD_DIR)/tests
BIN_DIR = bin
INSTALL_PATH = /usr/bin
DIST_PATH = dist
DOC_DIR = docs

# Static library
LIB_POSTFIX = s21
LIB_NAME = lib$(LIB_POSTFIX)
LIB_DIR = $(SRC_DIR)/libs21
LIB_PATH = $(LIB_DIR)/lib
LIB = $(LIB_PATH)/$(LIB_NAME)

# Documentation build
TEXI2DVI = texi2dvi
TEXI2PDF = texi2pdf
TEX_FILES = tex/SimpleMLP.tex

DVIS = $(patsubst $(SRC_DIR)/%.tex,$(DOC_DIR)/%.dvi,$(addprefix $(SRC_DIR)/, $(TEX_FILES)))
PDFS = $(patsubst $(SRC_DIR)/%.tex,$(DOC_DIR)/%.pdf,$(addprefix $(SRC_DIR)/, $(TEX_FILES)))

all: $(BIN_DIR)/$(NAME)

$(BIN_DIR)/$(NAME):
	@make -C $(LIB_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@cmake -S . -DPROJECT_NAME=$(NAME) -B build
	@cmake --build build
	@./$(BIN_DIR)/$(NAME)

install: $(BIN_DIR)/$(NAME)
	@cp $(BIN_DIR)/$(NAME) $(INSTALL_PATH)
	
uninstall:
	@rm -f $(INSTALL_PATH)/$(NAME)

dist:
	@mkdir -p $(DIST_PATH)
	@tar czf $(DIST_PATH)/$(NAME)-$(VERSION).tar.gz $(SRC_DIR) Makefile README.md LICENSE 

tests:
	@make -C $(LIB_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@cmake -S ./$(TEST_DIR) -DPROJECT_NAME=$(NAME)-tests -B $(TEST_BUILD_DIR)
	@cmake --build $(TEST_BUILD_DIR)
	@./$(BIN_DIR)/$(NAME)-tests

leaks: tests
ifeq ($(OS), Darwin)
	@leaks -atExit -- ./$(BIN_DIR)/$(NAME)-tests
else
	@echo "I do not know how to run leaks test on linux"
endif

dvi: $(DVIS) github

$(DOC_DIR)/%.dvi: $(SRC_DIR)/%.tex
	@mkdir -p $(DOC_DIR)
	@cd $(DOC_DIR) && $(TEXI2DVI) ../$<

pdf: $(PDFS) github

$(DOC_DIR)/%.pdf: $(SRC_DIR)/%.tex
	@mkdir -p $(DOC_DIR)
	@cd $(DOC_DIR) && $(TEXI2PDF) ../$<

github:
	@$(OPEN) "https://github.com/LudwigAndreas/SimpleMLP"

style:
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -style=Google -i **/*.cc **/*.h
	@clang-format -style=Google -n **/*.cc **/*.h
	@rm .clang-format

clean:
	@make -C $(LIB_DIR) clean
	@rm -rf $(BUILD_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean
	@rm -rf $(BIN_DIR) $(DOC_DIR)

re: fclean all

.PHONY: all clean fclean re tests leaks