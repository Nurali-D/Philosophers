NAME		=	philo
HEAD		=	includes/
OBJS_FOLD	=	objects/
SRCS_FOLD	=	sources/
SRCS_FILES	=	main.c
SRCS		=	$(addprefix $(SRCS_FOLD), $(SRCS_FILES))
OBJS_FILES	=	$(patsubst %.c, %.o, $(SRCS_FILES))
OBJS		=	$(addprefix $(OBJS_FOLD),$(OBJS_FILES))
RM			=	rm -rf
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror  -I $(HEAD)

all: $(NAME)

$(NAME): $(OBJS_FOLD) $(OBJS) $(HEAD)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

$(OBJS_FOLD):
	mkdir -p $(OBJS_FOLD)

$(OBJS_FOLD)%.o : $(SRCS_FOLD)%.c  $(HEAD)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_FOLD)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norme:
	norminette -R CheckForbiddenSourceHeader $(SRCS) $(HEAD)*.h

.PHONY:	all clean fclean re norme