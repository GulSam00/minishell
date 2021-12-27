/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:17:39 by sham              #+#    #+#             */
/*   Updated: 2021/12/27 21:45:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// # define MAX_PATH 4096
// # define OPEN_MAX 10240
// # define PIPE_READ 0
// # define PIPE_WRITE 1

# include <stdio.h>			   // <readline/readline.h>보다 먼저 선언되야 함.
# include <readline/readline.h> // 프롬프트 헤더
# include <readline/history.h>  // 프롬프트 헤더
# include <stdlib.h>			   // malloc
# include <unistd.h>			   // write
# include <fcntl.h>
# include <termios.h> // 터미널 헤더

# include <sys/types.h> // stat 헤더
# include <sys/stat.h>  // stat 헤더
# include <string.h>	   // strerror
# include <errno.h>	   // errno 에러 전역 변수
# include <signal.h>
# include <limits.h> // exit 최소값 처리

// enum e_bulit_in_code
// {
// 	CD = 1,
// 	ECHO,
// 	ENV,
// 	EXIT,
// 	EXPORT,
// 	PWD,
// 	UNSET
// };

enum e_cmd_type
{
	CMD = 0,
	ARG,
	DISCRIPTOR,
	OPTION,
	CMD_TYPE_MAX,
	PIPE
};

enum e_discriptor_type
{
	IN,
	OUT,
	DOUBLE_IN,
	DOUBLE_OUT
};

typedef struct s_data
{
	void			*contents;
	struct s_data	*next;
}	t_data;

typedef struct s_list
{
	void	*front;
	int		size;
}	t_list;

typedef struct s_cmd
{
	char			*cmd;
	char			**arg;
	struct s_list	arg_list;
	struct s_list	discriptor;
}	t_cmd;

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_discriptor
{
	char					*file_name;
	enum e_discriptor_type	type;
}	t_discriptor;

typedef struct heredoc_list
{
	char				*str;
	struct heredoc_list	*next;
}	t_h_list;

/* list */
void					init_list(t_list *list);
void					init_cmd(t_cmd *cmd);
int						add_data(t_list *list, void *new_contents);
int						free_cmd_list(t_list *list);
int						free_str_list(t_list *list);
void					print_cmd_list(t_list *list);
void					print_str_list(t_list *list);
void					print_env_list(t_list *list);
void					pop_env_with_key(t_list *list, char *key);
void					init_env(t_env *env, char *key, char *value);
char					*get_value(t_list *list, char *find_key);
int						free_env_list(t_list *list);
char					**env_to_char(t_list *env_list);
void					init_discriptor(t_discriptor *discriptor, \
						char *file_name, enum e_discriptor_type type);
int						free_discriptor_list(t_list *list);
void					print_discriptor_list(t_list *list);
enum e_discriptor_type	get_discriptor_type(char *word);
int						ft_parser(t_list *cmd_list, \
						char *input, t_list *env_list);
int						ft_env_parser(t_list *env_list, char **envp);
enum e_cmd_type			get_type(char *word);

char					*ft_quotes(char *str, \
						t_list *env_list, int first_quotes);
int						ft_div_input(t_list *word_list, \
						char *input, t_list *env_list);

/* libft */
char					*ft_strdup(const char *str);
char					*ft_strndup(const char *str, int size);
char					*ft_strjoin(const char *str1, const char *str2);
char					*ft_strjoin_path(const char *str1, const char *str2);
char					*ft_strjoin_with_char(const char *str1, \
						const char *str2, const char c);
int						ft_strlen(const char *str);
int						ft_strncmp(const char *str1, const char *str2, int len);
int						ft_cmpstr(char *str1, char *str2);
char					**ft_split(char const *s, char c);
size_t					ft_strlcpy(char *destination, \
						const char *source, size_t n);
char					*ft_itoa(long n);
int						ft_isdigit(int c);

/* install */
void					fork_cmd(t_list *cmd_list, t_list *env_list);
int						check_bulit_in(t_cmd *cmd, int range);
void					parse_cmd(t_cmd *cmd, t_list *env_list, int is_forked);
void					execve_cmd_sing_env(char *cmd_name, \
						t_cmd *cmd, t_list *env_list);
void					execve_cmd_bult_in(char *cmd_name, \
						t_cmd *cmd, t_list *env_list, int is_forked);
void					execve_cmd_normal(char *cmd_name, t_cmd *cmd, \
						t_list *env_list);

/* dis */
int						handle_dis(t_cmd *cmd);
int						ft_d_left_heredoc(char *dst);

/* bulit_in */
int						ft_cd(char *path, t_list *env_list);
int						ft_pwd(void);
int						ft_echo(char *argv[]);
int						ft_exit(char *argv[], int is_forked);
int						ft_env(char *argv[], t_list *env_list);
int						ft_export(t_list *env_list, char *argv[]);
int						ft_unset(t_list *env_list, char *argv[]);

/* error */
void					ft_error(char *cmd, char *arg, char *message);
void					ft_error_sing_dot(char *cmd, char *arg, char *message);

/* signal */
void					main_sig_handler(int signal);
void					heredoc_sig_handler(int signal);
void					execve_sig_handler(int signal);

#endif
