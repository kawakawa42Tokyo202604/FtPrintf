EXAMPLE = printf_example

NAME    = libftprintf.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
SRCS    = ft_printf.c ft_handle_1.c ft_handle_2.c ft_strlen.c
OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(EXAMPLE)

re: fclean all

.PHONY: all clean fclean re

example: $(EXAMPLE)

$(EXAMPLE): main.c $(NAME)
	$(CC) $(CFLAGS) $(CPPFLAGS) main.c $(NAME) $(LDFLAGS) $(LDLIBS) -o $@

run: $(EXAMPLE)
	./$(EXAMPLE)

.PHONY: example run

test: $(NAME)
	@set -eu; test_dir=$$(mktemp -d); trap 'rm -rf "$$test_dir"' EXIT; \
	$(CC) $(CPPFLAGS) $(CFLAGS) -I. tests/test_printf.c $(NAME) $(LDFLAGS) $(LDLIBS) -o "$$test_dir/test"; \
	"$$test_dir/test"

.PHONY: test
