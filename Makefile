CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror

NAME		=	so_long

LD_FLAGS		=	-L mlx

MLX_FLAGS		=	-lm -lmlx -lXext -lX11

SRCS		=	srcs/clean_structs_first.c srcs/first_inits.c \
				srcs/ft_split_hard_separator.c \
				srcs/map_related.c \
				srcs/moves.c \
				srcs/parser.c \
				srcs/so_long.c

HEADERS		=	-I include -I libft -I mlx

LIB			=	-lft -L libft

LIBFT_PATH	=	libft

LIBFT		=	${LIBFT_PATH}/libft.a

OBJECTS		=	${SRCS:.c=.o}

all:			$(NAME)

.c.o:
				${CC} ${CFLAGS} ${HEADERS} -c $< -o ${<:.c=.o}

$(NAME) :		${OBJECTS}
				@make -C libft
				@make -C mlx
				@${CC} ${CFLAGS} ${OBJECTS} ${HEADERS} ${LIB} ${LIBFT} -o ${NAME} ${LD_FLAGS} ${MLX_FLAGS}


clean:
				@make clean -C ${LIBFT_PATH}
				@make clean -C mlx
				@rm -rf ${OBJECTS}

fclean:			clean
				@make fclean -C ${LIBFT_PATH}
				@rm -rf $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
