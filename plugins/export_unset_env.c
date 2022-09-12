/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:25:50 by euyi              #+#    #+#             */
/*   Updated: 2022/09/11 16:31:20 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

void	export_unset_env(t_mini *shell)
{
	if (shell->exec_type_flag == 2
		&& !ft_memcmp(shell->exec_args[0], "unset\0", 6)
		&& !shell->pipe_count && !shell->cycle)
		call_run_unset(shell);
	else if (shell->exec_type_flag == 2
		&& !ft_memcmp(shell->exec_args[0], "export\0", 7)
		&& !shell->pipe_count && !shell->cycle)
		call_run_export(shell);
	else if (!shell->exec_type_flag && !shell->pipe_count
		&& !shell->cycle && valid_scalar_var(shell->cmd[0], 0))
		scalar_var_assignor(shell, 0);
}

// ******************************************************
// This runs the "unset" builtin command				*
// The technique used is to overwrite the				*
// first two array of an unset-ed path with				*
// {' ', '0'} without freeing the memory.				*
// HINT: scalar variable assignor checks for unset-ed	*
// array spaces while assigning a new scalar var		*
// to envp												*
// ******************************************************
void	call_run_unset(t_mini *shell)
{
	int	i;
	int	j;

	i = 0;
	while (shell->envp[i])
	{
		j = 1;
		while (shell->exec_args[j])
		{
			if (!ft_memcmp(shell->envp[i], shell->exec_args[j], ft_strlen(
						shell->exec_args[j])) && *(shell->envp[i]
					+ ft_strlen(shell->exec_args[j])) == '=')
			{
				shell->envp[i][0] = ' ';
				shell->envp[i][1] = 0;
			}
			j++;
		}
		i++;
	}
}

// Just a helper function for call_run_export() below
static int	print_export(t_mini *shell)
{
	int		j;
	char	c;

	c = 'A';
	while (c <= 'z')
	{
		j = 0;
		while (shell->envp[j])
		{
			if (*(shell->envp[j]) == c)
				printf("declare -x %s\n", shell->envp[j]);
			j++;
		}
		c++;
		if (c == 91)
			c = 'a';
	}
	return (0);
}

// **********************************************
// Function to run the "export" builtin command	*
// **********************************************
void	call_run_export(t_mini *shell)
{
	int		i;

	i = 1;
	if (!shell->exec_args[i] && !print_export(shell))
		return ;
	while (shell->exec_args[i])
	{
		if (valid_scalar_var(shell->exec_args[i], 0))
			run_export(shell, shell->exec_args[i], 1);
		else
			run_export(shell, shell->exec_args[i], 0);
		i++;
	}
}

// **************************************************
// stores a scalar variable that will be tracked	*
// by our minishell									*
// **************************************************
void	scalar_var_assignor(t_mini *shell, int i)
{
	char	name[100];

	copy_envp_name(name, shell->cmd[0]);
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], name, ft_strlen(name))
			&& !ft_memcmp(shell->envp[i] + ft_strlen(shell->envp[i]), "\0DF\0", 4)
			&& copy_var_to_env(shell->envp[i], shell->cmd[0], name, 1))
			return ;
		else if (!ft_strncmp(shell->envp[i], name, ft_strlen(name))
			&& copy_var_to_env(shell->envp[i], shell->cmd[0], name, 0))
			return ;
		i++;
	}
	i = 0;
	while (shell->envp[i])
	{
		if (!ft_memcmp(shell->envp[i], " \0", 2)
			&& copy_var_to_env(shell->envp[i], shell->cmd[0], name, 0))
			return ;
		i++;
	}
	shell->envp[i] = (char *) malloc(MAX_LINE_LEN * sizeof(char));
	shell->envp[i + 1] = NULL;
	copy_var_to_env(shell->envp[i], shell->cmd[0], name, 0);
}
