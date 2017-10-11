/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 12:35:22 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 12:35:27 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include <signal.h>

# include "../libft/libft.h"

/*
** waitpid
*/
# include <sys/types.h>
# include <sys/wait.h>

/*
** getcwd MAXPATHLEN
*/
# include <sys/param.h>

/*
** lstat
*/
# include <sys/stat.h>

# include <termios.h>

/*
** ioctl
*/
# include <sys/ioctl.h>

# include <fcntl.h>

# define EOF	(-1)
# define BUF_SIZE 32
# define BUF_ENV 256
# define DELIM " "

/*
** 0 -> flag
** 1 -> '
** 2 -> "
** 3 -> `
** 4 -> \
*/
# define IS_FLAG(param_quote) (((param_quote) >> 0) & 1)
# define IS_QUOTE(param_quote) (((param_quote) >> 1) & 1)
# define IS_DQUOTE(param_quote) (((param_quote) >> 2) & 1)
# define IS_BACKSLASH(param_quote) (((param_quote) >> 4) & 1)

# define QUOTE "quote> "
# define DQUOTE "dquote> "
# define HEREDOC "heredoc> "

# define KEY_UP		'A'
# define KEY_DOWN	'B'
# define KEY_RIGHT	'C'
# define KEY_LEFT	'D'
# define KEY_HOME	'H'
# define KEY_END	'F'
# define KEY_DELETE	51

/*
** code errors
*/
# define ERR_PD		1
# define ERR_NSFOD	2
# define ERR_NAD	3
# define ERR_CNF	4
# define ERR_SNIPWD	5
# define ERR_TMA	6
# define ERR_NVITC	7
# define ERR_IA		8
# define ERR_ERROR	9
# define ERR_ILLOP	10
# define ERR_PE     11

pid_t				g_pid;

struct termios		g_saved_attributes;

typedef struct		s_mov
{
	int				pos_column;
}					t_mov;

typedef struct		s_string
{
	size_t			total_size;
	int				curent_size;
	char			*str;
	t_mov			*mov;
	struct s_string	*next;
	struct s_string	*prev;
}					t_string;

typedef struct		s_pipe
{
	char			*cmd_full_path;
	char			**arg;
	int				fd_in;
	int				fd_out;
	int				fd_err;
	struct s_pipe	*next;
}					t_pipe;

int					ft_echo(char **argv);
int					ft_cd(char **args, char **env);
int					ft_env(t_pipe *pipes, char **env);
int					ft_setenv(char *name, char *value, int ov, char **env);
int					ft_unsetenv(char *name, char **env);
int					ft_exit(char **args);

/*
** launch
*/
int					execute(t_pipe *pipes, char **env);
void				ft_shell(char **env);

/*
** env
*/
char				*ft_getenv(char *name, char **env);
char				**copy_arr_str(char **env, size_t size);
int					make_unsetenv(char **args, char **env);
int					make_setenv(char **args, char **env);
int					is_env(char *name, char **env);
void				print_env(char **env);
char				*get_value_env(char **str, char **env);

/*
** util
*/
int					len_arr_string(t_string **arr);
int					len_arr_str(char **arr);
void				del_arr_str(char **env);
char				*get_full_path_lokal(char *str);
char				*get_pwd(void);
int					hangling_dquote(int *f_q_dq, int c);
int					ft_strequ_case_insen(char const *s1, char const *s2);
char				*ft_del_strstr(char *str, char *str2);
void				move_char(char **str_ptr);
void				ft_print_error(char *name, char *arg, int code);
char				*make_str(char *str, char **env);
int					is_file_or_directory(t_pipe *pipe_node, char **env);
char				*read_command(char **env);
char				*ft_strtok_quote(char *str, char *del);
void				*ft_realoc(void *ptr, size_t size);
char				**ft_split_del(char *str, char *delim);
char				**delite_q(char **args);
void				sighandler(int num);

/*
** util_mode_terminal
*/
void				save_attributes(void);
void				set_input_mode(void);
void				reset_input_mode(void);

/*
** move_cursor
*/
void				move_cursor(t_string **s, int prompt);
void				move_home_end(t_string **s, int c, int *i, int prompt);
void				move_left_right(t_string **s, int c, int *i, int prompt);
void				move_up_down(t_string **s, int c, int *i, int prompt);
void				print_esc(int number, char ch);
void				set_cursor(int cur_pos, int new_pos);
void				mov_word(t_string **s, int c, int *index, int prompt);
int					get_end_pos(t_string *s, int prompt);

/*
** history_command
*/
t_string			*history(t_string *buf, int key);

/*
** util_read
*/
int					ft_get_char(void);
void				print_dquote(int *f_q_dq, char **env);
void				search_quote(char *str, int *f_q_dq);
char				*only_str(t_string *head);
void				print_string(t_string *tail, int prompt);

/*
** util_struct
*/
t_pipe				*create_t_pipe(void);
void				add_list_t_pipe(t_pipe **head, t_pipe *new_node);
void				del_t_pipe(t_pipe **pipes);
void				insert_d_list(t_string **head, t_string *new_node);

/*
** util_struct_string
*/
t_string			*new_string(size_t size);
void				del_t_string(t_string **string);
void				del_string_command(t_string **string);
void				copy_string(t_string *dest, t_string *s);
void				del_string_wish_cur_pos(t_string **string);

/*
** launch
*/
t_pipe				*split_pipe(char **args_pipe);
int					handling_pipe(t_pipe *pipe_node, char **env);

/*
** util_heredoc
*/
int					ft_heredoc(char *s);

/*
** read
*/
t_string			*read_line_n(int prompt);

/*
** util_read_bufer
*/
int					add_to_buff(t_string **s, int c, int prompt);
int					len_prompt(char **env, int f_q_dq);
void				util_print_set(t_string **s, int prompt);

/*
** move_cursor
*/
void				mov_last_row(t_string *s, int prompt);

/*
** move_util
*/
void				move_cursore_new_line(int pos, int prompt);
int					get_cur_pos(t_string *s, int prompt);
int					get_new_pos(t_string *s, int c, int prompt);

/*
** util_delete_char
*/
void				delete_char(t_string **s, int *index, int prompt);

/*
** util_error
*/
void				error_redir(t_pipe *new_pipe, int i);

/*
** redirections
*/
void				check_redirections(t_pipe *new_pipe);

/*
** move_home_end
*/
void				home(t_string **s, int *index, int prompt);
void				end(t_string **s, int *index, int prompt);

/*
** util_backspace
*/
void				backspace(t_string **s, int prompt);

#endif
