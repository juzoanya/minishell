/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:42:08 by euyi              #+#    #+#             */
/*   Updated: 2022/09/12 11:55:34 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

static int	call_run_env(t_mini *shell);

void	run_env(t_mini *shell)
{
	int	exit_code;

	if (shell->exec_type_flag == 2
		&& !ft_memcmp(shell->exec_args[0], "env\0", 4))
	{
		if (count_args(shell->exec_args) == 1)
		{
			exit_code = call_run_env(shell);
			write_exit_status(exit_code);
		}
		else
		{
			printf("\'env --help\' for more information\n");
			write_exit_status(125);
		}
	}
}

static int	call_run_env(t_mini *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (!ft_memcmp(shell->envp[i] + ft_strlen(shell->envp[i]), "\0DF\0", 4))
			printf("%s\n", shell->envp[i]);
		i++;
	}
	return (0);
}
