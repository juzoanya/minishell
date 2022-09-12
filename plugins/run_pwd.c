/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 23:04:34 by juzoanya          #+#    #+#             */
/*   Updated: 2022/09/12 11:56:36 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

void	run_pwd(t_mini *shell)
{
	char	pwd[512];

	if (shell->exec_type_flag == 2
		&& !ft_memcmp(shell->exec_args[0], "pwd\0", 4))
	{
		if (count_args(shell->exec_args) == 1)
		{
			printf("%s\n", getcwd(pwd, 512));
			write_exit_status(0);
		}
		else
		{
			printf("pwd: %s: invalid option\n", shell->exec_args[1]);
			write_exit_status(2);
		}
	}
}
