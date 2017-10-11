NAME = 21sh

CC = gcc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = includes/

SRCS =         main.c\
			   read.c\
			   history_command.c\
			   move_cursor.c\
			   split_comand.c\
			   launch.c\
			   ft_echo.c\
			   ft_env.c\
			   ft_setenv.c\
			   ft_unsetenv.c\
			   ft_cd.c\
			   ft_exit.c\
			   util_error.c\
			   util_search_path.c\
			   util.c\
			   util_env.c\
			   util_make_str.c\
			   util_ft_strtok.c\
			   util_path.c\
			   util_read.c\
			   util_read_bufer.c\
			   util_mode_terminal.c\
			   util_struct.c\
			   util_hredoc.c\
			   redirections.c\
			   util_ft_function.c\
			   move_word.c\
			   move_home_end.c\
			   move_up_down.c\
			   move_util.c\
			   util_quote.c\
			   util_struct_string.c\
			   util_delete_char.c\
			   util_backspace.c

OBJ = $(SRCS:.c=.o)

LIBFTDIR = libft/

all: $(NAME)

$(NAME) : $(OBJ) $(LIBFTDIR)libft.a
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L./$(LIBFTDIR) -lft

%.o: srcs/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDES) -I $(LIBFTDIR)

$(LIBFTDIR)libft.a: libft/Makefile
	make -C libft/

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)

re: clean all

norm:
	norminette srcs/ includes/*.h
