/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:33:32 by euyi              #+#    #+#             */
/*   Updated: 2022/09/12 12:31:03 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>

extern int	g_exit_status;

# define MAX_WORD_LEN 10000
# define MAX_ARR_CNT 10000
# define MAX_LINE_LEN 100000
# define DEF_STDIN 0
# define DEF_STDOUT 1
# define DEF_STDERR 2
# define DEF_PIPE_CNT 100

typedef struct s_mini
{
	char		**cmd;
	char		**exec_args;
	char		**envp;
	int			cycle;
	int			stdin;
	int			stdin_tmp;
	int			pipe_count;
	int			exec_type_flag;
	int			pipe_fd[DEF_PIPE_CNT][2];
	int			exit;
}				t_mini;

// Functions in "libft_tools.c"
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// Functions for parser_switch.c
void	parser_switch(t_mini *shell, int flag);
void	segment_cmd(char **cmd, char *tmp, int i);
int		count_seg(t_mini *shell, char *src, char c);
int		find_closing_quote(const char *src, char c);
void	copy_one_word(char *dest, const char *src);
int		within_quote(const char *ptr, int arr_point);
int		within_quote_2(const char *ptr, int one_q, int two_q, int fl);
int		check_closing_quote(const char *ptr, char c);
void	shell_env_switch(t_mini *shell, char **envp);
int		envp_validator(t_mini *shell);

// Functions for run_plugins.c
void	run_plugins(t_mini *shell);
void	stdin_fd_switch(t_mini *shell, int flag);
void	close_pipe_ends(t_mini *shell);
int		output_to_file(t_mini *shell, char *filename);

// Plugin functions in the "plugins" directory
void	ready_stdin(t_mini *shell);
void	dollar_processor(t_mini *shell);
void	check_exec_type(t_mini *shell, char *cmd, int i);
void	run_cd(t_mini *shell);
void	export_unset_env(t_mini *shell);
void	ready_stdout(t_mini *shell);
void	run_env(t_mini *shell);
void	run_execve(t_mini *shell);
void	reset_segment_memory(t_mini *shell);

// Functions in "0-ready_stdin_utils.c" file in plugins_assets dir
int		find_heredoc_delim(char *ptr);
void	expand_env(t_mini *shell, char *line);
int		find_file_delim(char *ptr);

// Functions in "check_exec_type_utils.c" file in plugins_assets dir
int		copy_exec_arg(t_mini *shell, char *cmd);
int		forbidden_word(char *src, int n);
int		copy_valid_arg(char *exec_args, char *src);
int		copy_valid_quote(char *dest, char *src);
int		copy_next_word(char *dest, char *src);
int		known_s_commands(char *src);

// Functions in "utils4dollar_processor.c" file in plugins_assets dir
int		len_b4_eq_sign(const char *ptr);
int		cpy_envp_val(char *dest, char *envp, char *src);
void	overwrite_dest_to_src(char *src, char *dest);
void	shift_back_element(char *src);
void	remove_dollar_attr(char *src);

//Functions in "cd_utils.c" file in "plugins_assets" dir
int		get_len(char *str_env, char *pwd);
void	strip_append(char **str, t_mini *shell);
char	*get_path(t_mini *shell, char *var);
void	ft_strcpy_ms(char *dest, char *s1, char *s2);
void	set_cd_flags(t_mini *shell, int *flag);
void	join_paths(t_mini *shell, char *str, char *pwd);
void	update_pwd(t_mini *shell, char *arg);

//Functions in "export_unset_env_utils.c" file in plugins_assets dir
void	call_run_unset(t_mini *shell);
void	call_run_export(t_mini *shell);
void	scalar_var_assignor(t_mini *shell, int i);
void	run_export(t_mini *shell, char *src, int flag);
void	copy_envp_name(char *dest, const char *src);
int		valid_scalar_var(const char *src, int flag);
int		copy_var_to_env(char *dest, const char *src2, char *src1, int flag);

//Functions in "run_execve_utils.c" file in plugins_assets dir
void	copy_one_path(char *exec_args, char **path);
void	copy_path(char *dest, char **src);

//Functions in "run_signal.c" file in the "plugins" directory
void	init_signal(t_mini *shell);
void	init_child_sig(t_mini *shell);
void	sig_handler(int sig, siginfo_t *info, void *context);

//Functions in "run_echo.c" file in the "plugins" directory
void	run_echo(t_mini *shell);
int		count_args(char **cmd);

//Functions in "run_pwd.c" file in the "plugins" directory
void	run_pwd(t_mini *shell);

void	write_exit_status(int code);
void	read_parse_exit(t_mini *shell);

#endif
