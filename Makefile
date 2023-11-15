NAME := pipex

CC := cc
CFLAGS :=  -Wextra -Wall -Werror
INCS := -I ./includes

SRCS := $(shell find ./src -iname "*.c")
OBJS := $(SRCS:.c=.o)

RM := rm -rf

DEP := ./includes/pipex.h

LIB := libft_all/libft_all.a

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $< -c -o $@ $(INCS)

$(NAME): $(OBJS) 
	$(MAKE) -C libft_all
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(LIB) -o $(NAME)

clean:
	$(MAKE) clean -C libft_all
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C libft_all
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
