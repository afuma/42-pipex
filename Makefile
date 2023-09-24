CC = cc
NAME = pipex

RM = rm -f
AR = ar
ARFLAGS = crs

# /* ~~~~~~ SOURCES ~~~~~~ */
SRCS_DIR = srcs/
SRCS_FILES = 	main.c \
		ft_pipex.c \
		ft_path.c \
		ft_free.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS = ${SRCS:.c=.o}

# /* ~~~~~~~ INCLUDING LIBFT ~~~~~~~ */
LIBFT_DIR = libft
LIBFT_MAKE = Makefile
LIBFT_PATH = ${LIBFT_DIR}/libft.a

# /* ~~~~~~~ COMPILING INFO ~~~~~~~ */
CFLAGS = -Wall -Werror -Wextra -g
IFLAGS:= -I ./includes
LFLAGS:= -L $(LIBFT_DIR) -lft $(LIBFT_PATH)

all:	${NAME}		

$(NAME): $(OBJS)
	cd $(LIBFT_DIR) && $(MAKE)
	$(CC) $(CFLAGS) $(OBJS) $(IFLAGS) $(LFLAGS) -o $(NAME)

clean:
		${RM} ${OBJS}
		make -C ${LIBFT_DIR} -f ${LIBFT_MAKE} clean

fclean: clean
		${RM} ${OBJS} ${NAME}

re: 	fclean all

.PHONY: all clean fclean re