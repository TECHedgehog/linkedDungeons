NAME := bin/linkedDungeons

CC := gcc
RM := rm -rf
CFLAGS := -Wall -Werror -Wextra
DFLAGS := -g
LFLAGS := -fsanitize=address
ASAND_OPT := ASAN_OPTIONS=abort_on_error=1
ASAN_OPT := ASAN_OPTIONS=detect_leaks=1

BUILD_DIR := ./build

SRC_DIR := ./src
INC_DIR := ./includes
LIB_DIR := -Ilib/
HDDIRS := -I$(INC_DIR) $(LIB_DIR)
OSX_OPT = -Llib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a


SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(HDDIRS) -o $(NAME) $(OSX_OPT)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(DFLAGS) $(HDDIRS) -c $< -o $@

all: $(NAME)

clean: 
	@$(RM) $(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

debug: clean $(OBJS)
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) $(HDDIRS) -o $(NAME)

.PHONY: all clean fclean re debug