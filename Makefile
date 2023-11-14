NAME := pipex

CC := cc
CFLAGS :=  -Wextra -Wall -Werror
INCS := -I ./includes

SRCS := $(shell find ./src -iname "*.c")
OBJS := $(SRCS:.c=.o)

RM := rm -rf

DEP := ./includes/pipex.h


%.o: %.c $(DEP)
	@$(CC) $(CFLAGS) $< -c -o $@ $(INCS)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
