/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 19:05:08 by juzoanya          #+#    #+#             */
/*   Updated: 2022/09/13 11:57:38 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

int	count_args(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
		i++;
	return (i);
}

void	call_run_echo(t_mini *shell, int n_flag, int i)
{
	int	n;

	if (count_args(shell->exec_args) > 1)
	{
		while (shell->exec_args[i] != NULL
			&& (ft_strncmp(shell->exec_args[i], "-n", 2) == 0
				|| (ft_strncmp(shell->exec_args[i], "-n", 2) == 0
					&& count_args(shell->exec_args) > 2)))
		{
			n_flag = 1;
			i++;
		}
		while (shell->exec_args[i] != NULL)
		{
			n = -1;
			while (shell->exec_args[i][++n] != '\0')
				write(1, &shell->exec_args[i][n], 1);
			if (shell->exec_args[i + 1] != NULL)
				write(1, " ", 1);
			i++;
		}
	}
	if (n_flag == 0)
		printf("\n");
}

void	run_echo(t_mini *shell)
{
	if (shell->exec_type_flag == 2
		&& !ft_memcmp(shell->exec_args[0], "echo\0", 5))
	{
		call_run_echo(shell, 0, 1);
		write_exit_status(0);
	}
}
