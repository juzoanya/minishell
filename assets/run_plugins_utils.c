/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_plugins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 20:26:39 by euyi              #+#    #+#             */
/*   Updated: 2022/09/09 20:53:27 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// *************************************************************
// stdin_fd_switch() is called with flag == true when command	*
// that is about to be executed by execve() requires custom		*
// stdin data due to the presence of either '<<', '<', or '|'.	*
// Before calling stdin_fd_switch() with flag == true, the 		*
// the program must have stored	the FD for the file or pipe 	*
// holding the custom data to the shell->stdin variable.		*
// In this case, it will force the default stdin FD to now 		*
// be answering in the FD stored in shell->stdin
//
// stdin_fd_switch() is called with flag == false in the line 	*
// imediately after execve has executed.
// that is about to be executed by execve() requires custom		*
// stdin data due to the presence of either '<<', '<', or '|'.	*
// ************************************************************* 
void	stdin_fd_switch(t_mini *shell, int flag)
{
	if (flag == 1 && !shell->cycle)
		dup2(shell->stdin, DEF_STDIN);
	if (flag == 2 && shell->cycle)
		dup2(shell->pipe_fd[shell->cycle - 1][0], DEF_STDIN);
	if (!flag)
	{
		dup2(shell->stdin_tmp, DEF_STDIN);
		shell->stdin = -1;
	}
}

// **************************************
// Needed by runplugins() for closing	*
// the other sides of pipes before		*
// exiting child processes				*
// **************************************
void	close_pipe_ends(t_mini *shell)
{
	close(shell->pipe_fd[shell->cycle - 1][0]);
	close(shell->pipe_fd[shell->cycle][1]);
}

// Needed by ready_stdout() Plugin for
// checking and resolving > and >> redirections
int	output_to_file(t_mini *shell, char *filename)
{
	char	*ptr;
	int		i;

	ptr = shell->cmd[shell->cycle];
	i = 0;
	while (ptr[i])
	{
		if (!ft_strncmp(ptr + i, ">>", 2) && !within_quote(ptr, i))
		{
			copy_one_word(filename, ptr + (i + 2));
			return (2);
		}
		else if (!ft_strncmp(ptr + i, ">", 1) && !within_quote(ptr, i))
		{
			copy_one_word(filename, ptr + (i + 1));
			return (1);
		}
		i++;
	}
	return (0);
}

// Just to support copy_one_word() function below
int	find_closing_quote(const char *src, char c)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (src[i] == c)
			return (1);
		i++;
	}
	return (0);
}

// **************************************************
// copy_one_word() simply copys one word from		*
// its SRC to DEST params. It ignores empty spaces	*
// at the beginning of the word. If the word found 	*
// is/are within valid quotes, it copies all the 	*
// words within the quotes, else if there are none 	*
// it copies only the								*
// non-space characters and stops once it either	*
// reaches the end of SRC string or it encounters	*
// a space character.								*
// **************************************************
void	copy_one_word(char *dest, const char *src)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (*src && ((*src >= 9 && *src <= 13) || (*src == 32)))
		src++;
	if (*src == '\'' && find_closing_quote(src + 1, '\''))
		flag = 39;
	else if (*src == '"' && find_closing_quote(src + 1, '"'))
		flag = 34;
	if (flag)
		src++;
	while (src[i] && (src[i] < 9 || (src[i] > 13 && src[i] != 32)))
	{
		dest[i] = src[i];
		i++;
	}
	while (src[i] && flag && src[i] != flag)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
}
