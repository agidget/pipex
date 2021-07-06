NAME	= pipex
CC		= gcc
HEADER	= pipex.h
SRCS	= pipex.c for_path.c utils1.c utils2.c
SRCS_B	= pipex_bonus.c bonus_2nd_part.c bonus_utils.c for_path.c utils1.c utils2.c
RM		= rm -rf
CFLAGS	= -Wall -Werror -Wextra
OBJS	= pipex.o for_path.o utils1.o utils2.o
OBJS_B	= pipex_bonus.o bonus_2nd_part.o bonus_utils.o for_path.o utils1.o utils2.o

all:		${NAME}

$(NAME):	$(SRCS) $(HEADER)
			$(CC) $(CFLAGS) -c $(SRCS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus:		$(SRCS_B) $(HEADER)
			@$(MAKE) SRCS="$(SRCS_B)" OBJS="$(OBJS_B)"

clean:
			${RM} ${OBJS} ${OBJS_B}
fclean:		clean
			${RM} ${NAME}
re:			clean all
.PHONY:		all clean fclean re