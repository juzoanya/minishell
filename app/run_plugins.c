/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_plugins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:55:19 by euyi              #+#    #+#             */
/*   Updated: 2022/09/12 15:37:51 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

// ***************************************************************
// run plugins() calls each of the command functions to action *
// ***************************************************************
void	run_plugins(t_mini *shell)
{
	ready_stdin(shell);
	dollar_processor(shell);
	check_exec_type(shell, NULL, 0);
	export_unset_env(shell);
	run_cd(shell);
	if (fork() == 0)
	{
		ready_stdout(shell);
		run_echo(shell);
		run_pwd(shell);
		run_env(shell);
		run_execve(shell);
		close_pipe_ends(shell);
		exit (0);
	}
	else
	{
		wait(NULL);
		close(shell->pipe_fd[shell->cycle][1]);
		read_parse_exit(shell);
	}
	reset_segment_memory(shell);
}
