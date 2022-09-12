/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:14:59 by euyi              #+#    #+#             */
/*   Updated: 2022/09/11 18:18:05 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

static void	call_execve(t_mini *shell);

// This function runs execve
void	run_execve(t_mini *shell)
{
	if (shell->exec_type_flag == 1 && ft_strlen(shell->exec_args[0]))
		call_execve(shell);
}

// *************************************************************
// call_execve() is a util function for run_execve()			*
// that is located in run_execve.c inside the plugins			*
// directory.													*
// It runs execve() to execute						*
// the commands stored in shell->exec_args.						*
// *************************************************************
static void	call_execve(t_mini *shell)
{
	char	*tmp;
	char	*path;

	if (known_s_commands(shell->exec_args[0]) && envp_validator(shell))
	{
		path = (char *) malloc(MAX_LINE_LEN * sizeof(char));
		copy_path(path, shell->envp);
		tmp = (char *) malloc(MAX_LINE_LEN * sizeof(char));
		ft_strlcpy(tmp, shell->exec_args[0],
			ft_strlen(shell->exec_args[0]) + 1);
		while (*path)
		{
			copy_one_path(shell->exec_args[0], &path);
			ft_strlcpy(shell->exec_args[0] + ft_strlen(shell->exec_args[0]),
				tmp, ft_strlen(tmp) + 1);
			if (!access(shell->exec_args[0], X_OK))
				execve(shell->exec_args[0], shell->exec_args, shell->envp);
		}
		free (tmp);
	}
	else
		execve(shell->exec_args[0], shell->exec_args, shell->envp);
}
