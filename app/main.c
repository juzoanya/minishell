/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:14:30 by euyi              #+#    #+#             */
/*   Updated: 2022/09/10 20:31:58 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

int	g_exit_status;

int	main(int i, char *argv[], char *envp[])
{
	t_mini	shell;

	(void)argv;
	g_exit_status = 0;
	shell_env_switch(&shell, envp);
	init_signal(&shell);
	if (!envp_validator(&shell))
		return (0);
	while (!shell.exit)
	{
		parser_switch(&shell, 1);
		if (shell.exit == 2 && (shell_env_switch(&shell, NULL), 1))
			kill(0, SIGTERM);
		i = -1;
		while (shell.cmd && shell.cmd[++i])
		{
			shell.cycle = i;
			run_plugins(&shell);
		}
		while (wait(NULL) != -1)
			;
		parser_switch(&shell, 0);
	}
	shell_env_switch(&shell, NULL);
	return (0);
}
