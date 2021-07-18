NAME = philo

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror -I includes/

SRC = src/Philosophers.c \
	src/init.c \
	src/eat.c \
	src/print.c \
	src/freed.c \
	src/monitor.c \
	utils/ft_atoi.c \
	utils/get_time.c \
	utils/ft_isdigit.c \

SRCS = $(SRC) 

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n"
	@echo "\033[0;32mCompiling philo..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\n\033[0mDone !"

%.o: %.c
	@printf "\033[0;33mGenerating philo objects... %-33.33s\r" $@
	@${CC} -g ${CFLAGS} -c $< -o $@

clean:
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31m\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\nDeleting trash..."
	@rm -f *.txt
	@rm -f *.out
	@echo "\033[0m"

re: fclean all

test: all
	./$(NAME)

norm:
	norminette $(SRC) includes/$(HEADER)

git:
	git add *
	git commit -m "add"
	git push

.PHONY: clean fclean re test norm
