/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ready_stdout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:57:18 by euyi              #+#    #+#             */
/*   Updated: 2022/09/11 15:59:31 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

// This plugin function is called only from child process
// it sets redirection request for stdin and stdout
// accordingly
void	ready_stdout(t_mini *shell)
{
	char	filename[MAX_WORD_LEN];
	int		i;

	if (shell->cycle > 0)
		close(shell->pipe_fd[shell->cycle - 1][1]);
	if (shell->pipe_count > 0)
	{
		close(shell->pipe_fd[shell->cycle][0]);
		dup2(shell->pipe_fd[shell->cycle][1], DEF_STDOUT);
		dup2(shell->pipe_fd[shell->cycle][1], DEF_STDERR);
	}
	else if (output_to_file(shell, filename))
	{
		if (output_to_file(shell, filename) == 1)
			i = open(filename, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0644);
		else if (output_to_file(shell, filename) == 2)
		{
			i = open(filename, O_WRONLY | O_APPEND | O_CREAT | O_EXCL, 0644);
			if (i == -1)
				i = open(filename, O_WRONLY | O_APPEND);
		}
		dup2(i, DEF_STDOUT);
		dup2(i, DEF_STDERR);
	}
}
