/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-ready_stdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 17:23:36 by euyi              #+#    #+#             */
/*   Updated: 2022/09/12 14:44:08 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

void	stdin_from_heredoc(t_mini *shell);
void	stdin_from_file(t_mini *shell);

// **************************************************
// ready_stdin() prepares stdin to retrieve data	*
// from the right place (pipe, heredoc, file)		*
// under all circumstances							*
// **************************************************
void	ready_stdin(t_mini *shell)
{
	pipe(shell->pipe_fd[shell->cycle]);
	stdin_from_heredoc(shell);
	stdin_from_file(shell);
}

// **************************************************
// read_multi_lines() checks the user minishell		*
// command input stored in shell->cmd[x] to see			*
// if the user is requesting to feed their input	*
// to the stdin(); meaning they have used the 		*
// "<< DELIMITER" in their command. 					*
// If yes, read_multi_lines() creates a temp file 		*
// named "input_tmp", then it requests and stores	*
// the users' stdin input there, then it stores the	*
// file descriptor of "input_tmp" to shell->stdin	*
// In the end, we have the shell->stdin ready to	* 
// be fed upon any data requests call to stdin.		*
// IT IS WORTH REMEMBERING THAT THIS FUNCTION ONLY	*
// WORKS WHEN shell->cycle is still == 0, meaning	*
// we're executing the first cmd sentence before 	*
// any pipe.										*
// **************************************************
void	stdin_from_heredoc(t_mini *shell)
{
	char	*ptr;
	char	line[MAX_LINE_LEN];
	char	delim[MAX_WORD_LEN];
	int		line_len;

	if (shell->cycle > 0 && (stdin_fd_switch(shell, 2), 1))
		return ;
	ptr = shell->cmd[shell->cycle];
	if (find_heredoc_delim(ptr))
	{
		copy_one_word(delim, ptr + find_heredoc_delim(ptr));
		shell->stdin = open(
				"heredoc", O_RDWR | O_APPEND | O_CREAT | O_TRUNC, 0644);
		while (ft_strlen(delim))
		{
			line_len = read(DEF_STDIN, line, MAX_LINE_LEN);
			line[line_len] = 0;
			if (!ft_strncmp(line, delim, ft_strlen(delim)))
				break ;
			expand_env(shell, line);
			write (shell->stdin, line, ft_strlen(line));
		}
		shell->stdin = open("heredoc", O_RDONLY);
		stdin_fd_switch(shell, 1);
	}
}

// **************************************************
// stdin_from_file() checks the user minishell		*
// command input stored in shell->cmd[x] to see			*
// if the user is requesting to feed a file as input	*
// to the stdin(); meaning they have used the 		*
// "< FILE_NAME" in their command. 					*
// If yes, stdin_from_file() opens and stores the	*
// file descriptor of FILE_NAME to shell->stdin	*
// In the end, we have the shell->stdin ready to	* 
// be fed upon any data requests call to stdin.		*
// IT IS WORTH REMEMBERING THAT THIS FUNCTION ONLY	*
// WORKS WHEN shell->cycle is still == 0, meaning	*
// we're executing the first cmd sentence before 	*
// any pipe.										*
// **************************************************
void	stdin_from_file(t_mini *shell)
{
	char	*ptr;
	char	file_name[100];

	if (shell->stdin != -1 || shell->cycle)
		return ;
	ptr = shell->cmd[shell->cycle];
	if (find_file_delim(ptr))
	{
		copy_one_word(file_name, ptr + find_file_delim(ptr));
		shell->stdin = open(file_name, O_RDONLY);
		stdin_fd_switch(shell, 1);
	}
}
