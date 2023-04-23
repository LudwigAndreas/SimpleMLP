# Compiler settings
CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -Ofast -march=native -pedantic

# Directories
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Source files
SRCS_FILES = s21_to_lower.cc\
		s21_to_upper.cc\
		s21_split.cc\
		s21_load_bmp.cc

SRCS = $(addprefix $(SRC_DIR)/,$(notdir $(SRCS_FILES)))

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cc,$(BUILD_DIR)/%.o,$(SRCS))

# Library settings
LIB_NAME = s21
LIB_DIR = lib
LIB = $(LIB_DIR)/lib$(LIB_NAME).a

all: $(LIB)

$(LIB): $(OBJS)
	@echo
	@mkdir -p $(LIB_DIR)
	@ar rcs $(LIB) $(OBJS)
	@echo "\033[1;33m""$(LIB) is up to date."'\033[0m'

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c -o $@ $<
	@printf "\033[1;36m/\033[0m"

clean:
	@$(RM) $(OBJS)
	@echo '\033[1;31m'"$(LIB) deleted."'\033[0m'

fclean: clean
	@$(RM) $(LIB)
	@echo '\033[1;31m'"$(LIB) objs deleted."'\033[0m'

re: fclean all

.PHONY: all clean fclean re bonus
