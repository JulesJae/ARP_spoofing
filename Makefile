NAME = ft_malcolm

PATH_SRC = ./srcs/

PATH_INC = ./includes/

INCLUDES = -I $(PATH_INC)

GCC = gcc
FLAGS = -Wall -Wextra -Werror $(INCLUDES) -g

SRC =   main.c \
		arg.c \
		bool.c \
		conf.c \
		print.c \
		spoofing.c \
		tools.c \

OBJ = $(addprefix $(PATH_SRC), $(SRC:.c=.o))

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(PATH_INC)mitm.h
	$(GCC) $(OBJ) -o $(NAME)

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all