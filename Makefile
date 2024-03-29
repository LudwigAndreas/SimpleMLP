# Application name
NAME = SimpleMLP

OS = $(shell uname)

# Project Version
VERSION = 1.0

# Make and cmake settings
CMAKE = cmake
CMAKE_FLAGS = -DCMAKE_PREFIX_PATH=$(QT_PATH) -DCMAKE_OUT_DIR=$(BIN_DIR) -DCMAKE_BUILD_TYPE=Release #Release / Debug
ifeq ($(OS), Linux)
  OPEN=xdg-open
else
  OPEN=open
endif

# Directories
# To create the folders and structure of the project more correctly, put the Makefile in the root of the project and change the SRC variable from '.' to 'src'
INSTALL_PATH = ~/Applications
ROOT_DIR = $(shell pwd)
SRC_DIR = $(ROOT_DIR)/src
TEST_DIR = $(SRC_DIR)/tests
BUILD_DIR = $(ROOT_DIR)/build
TEST_BUILD_DIR = $(BUILD_DIR)/tests
BIN_DIR = $(ROOT_DIR)/bin
DIST_PATH = $(ROOT_DIR)/dist
DOC_DIR = $(ROOT_DIR)/docs
RES_DIR = $(SRC_DIR)/resources

SRC_FILES = $(shell find $(SRC_DIR) -type f -name "*.h" -o -name "*.cc")
SCRIPT_PATH = src/generate_constants.sh

# Static library
LIB_POSTFIX = s21
LIB_NAME = lib$(LIB_POSTFIX)
LIB_DIR = $(SRC_DIR)/libs21
LIB_PATH = $(LIB_DIR)/lib
LIB = $(LIB_PATH)/$(LIB_NAME)

# Documentation build
TEXI2DVI = texi2dvi
TEXI2PDF = texi2pdf
TEX_FILES = $(RES_DIR)/tex/SimpleMLP.tex

DVIS = $(patsubst $(SRC_DIR)/%.tex,$(DOC_DIR)/%.dvi,$(TEX_FILES))
PDFS = $(patsubst $(SRC_DIR)/%.tex,$(DOC_DIR)/%.pdf,$(TEX_FILES))

all: $(BIN_DIR)/$(NAME)

$(BIN_DIR)/$(NAME): $(SRC_FILES) $(ROOT_DIR)/src/gui/utils/const.h
	@make -C $(LIB_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@cmake -S $(SRC_DIR) -DPROJECT_NAME=$(NAME) $(CMAKE_FLAGS) -B $(BUILD_DIR)
	@cmake --build $(BUILD_DIR)
	@rm -f SimpleMLP
	@ln -s bin/SimpleMLP SimpleMLP

$(ROOT_DIR)/src/gui/utils/const.h: $(SCRIPT_PATH)
	@bash $(SCRIPT_PATH) $(ROOT_DIR)

install: $(BIN_DIR)/$(NAME)
ifeq ($(OS),Darwin)
	@cp -rf $(BIN_DIR)/$(NAME).app $(INSTALL_PATH)
else
	@cp -rf $(BIN_DIR)/$(NAME) $(INSTALL_PATH)
endif
	
uninstall:
ifeq ($(OS),Darwin)
	@rm -rf $(BIN_DIR)/$(NAME).app $(INSTALL_PATH)
else
	@rm -rf $(BIN_DIR)/$(NAME) $(INSTALL_PATH)
endif

dist:
	@mkdir -p $(DIST_PATH)
	@tar czf $(DIST_PATH)/$(NAME)-$(VERSION).tar.gz $(shell basename $(SRC_DIR)) Makefile README.md LICENSE 

tests:
	@make -C $(LIB_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@cmake -S $(TEST_DIR) -DPROJECT_NAME=$(NAME)-tests -DSRC_DIR=$(SRC_DIR) $(CMAKE_FLAGS) -B $(TEST_BUILD_DIR)
	@cmake --build $(TEST_BUILD_DIR)
	@$(BIN_DIR)/$(NAME)-tests

leaks: tests
ifeq ($(OS), Darwin)
	@leaks -atExit -- $(BIN_DIR)/$(NAME)-tests
else
	@echo "I do not know how to run leaks test on linux"
endif

dvi: github $(DVIS) 

$(DOC_DIR)/%.dvi: $(SRC_DIR)/%.tex
	@mkdir -p $(DOC_DIR)
	@cd $(DOC_DIR) && $(TEXI2DVI) $<

pdf: github $(PDFS) 

$(DOC_DIR)/%.pdf: $(SRC_DIR)/%.tex
	@mkdir -p $(DOC_DIR)
	@cd $(DOC_DIR) && $(TEXI2PDF) $<

github:
	@$(OPEN) "https://github.com/LudwigAndreas/SimpleMLP"

style:
	@cp $(ROOT_DIR)/materials/linters/.clang-format .clang-format
	@clang-format -style=Google -i $(SRC_FILES)
	@clang-format -style=Google --verbose -n $(SRC_FILES)
	@rm .clang-format

clean:
	@make -C $(LIB_DIR) clean
	@rm -rf $(BUILD_DIR)
	@rm -f SimpleMLP

fclean: clean
	@make -C $(LIB_DIR) fclean
	@rm -rf $(ROOT_DIR)/src/gui/utils/const.h
	@rm -rf $(BIN_DIR) $(DOC_DIR) $(DIST_PATH) $(BUILD_DIR)/autosave*

re: fclean all

.PHONY: all clean fclean re tests leaks dvi pdf github dist uninstall install