/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2-check_exec_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:16:34 by euyi              #+#    #+#             */
/*   Updated: 2022/09/11 18:31:38 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

static int	beginning_array(t_mini *shell);
static int	known_commands(char *src);
static void	check_exec_type_2(t_mini *shell, char *cmd);

// **********************************************************
// check_exec_type() checks if the program we are executing	*
// requires execve() or it is a custom command.				*
// It filters the data of the current command segment from	*
// shell->cmd[shell->cycle] and stores the data and flags	*
// (if any) of what we need to execute to shell->exec_args	*
// in a way that can be passed as pathname arg to execve()	*
// If what we're executing begins with ./, then it sets		*
// shell->exec_type_flag to 1 (meaning we need execve),		*
// but if we're executing a known command, (cd, echo, etc),	*
// it sets shell->exec_type_flag to 2 (meaning we dont need	*
// execve)													*
// **********************************************************
void	check_exec_type(t_mini *shell, char *cmd, int i)
{
	shell->exec_args = (char **) malloc(MAX_ARR_CNT * sizeof(char *));
	i = -1;
	while (shell->exec_args[++i])
		shell->exec_args[i] = NULL;
	shell->exec_type_flag = 0;
	cmd = shell->cmd[shell->cycle];
	if (beginning_array(shell))
		return ;
	i = 1;
	while (cmd[i])
	{
		if (!within_quote(cmd, i) && cmd[i - 1] == ' '
			&& (!ft_strncmp(cmd + i, "~/", 2) || !ft_strncmp(cmd + i, "../", 3)
				|| !ft_strncmp(cmd + i, "./", 2) || !ft_strncmp(cmd + i, "/", 1)
				|| known_s_commands(cmd + i)) && copy_exec_arg(shell, cmd + i))
			shell->exec_type_flag = 1;
		else if (!within_quote(cmd, i) && cmd[i - 1] == ' '
			&& known_commands(cmd + i) && copy_exec_arg(shell, cmd + i))
			shell->exec_type_flag = 2;
		if (shell->exec_type_flag)
			return ;
		i++;
	}
	check_exec_type_2(shell, cmd);
}

// Just an extension of check_exec_type() above
static void	check_exec_type_2(t_mini *shell, char *cmd)
{
	if (!shell->exec_type_flag && shell->cycle == 0)
	{
		while (*cmd && ((*cmd >= 9 && *cmd <= 13) || (*cmd == 32)))
			cmd++;
		if (ft_strlen(cmd) && !valid_scalar_var(cmd, 0))
		{
			printf("Input Error!\n");
			g_exit_status = 1;
		}
	}
}

// **************************************************************
// beginning_array() is an attachment function to avoid 		*
// catching ./ or its other known executable identifiers in 	*
// cases where they appears inside a word (eg hello./me).		*
// beginning_array() does the check_exec_type() job but it		*
// only checks the arr[0] and stops if it doesn't find known	*
// commands. thus, check_exec_type() can begin from arr[1]		*
// ************************************************************** 
static int	beginning_array(t_mini *shell)
{
	char	*cmd;

	cmd = shell->cmd[shell->cycle];
	if ((!ft_strncmp(cmd, "~/", 2) || !ft_strncmp(cmd, "/", 1)
			|| !ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "../", 3)
			|| known_s_commands(cmd)) && copy_exec_arg(shell, cmd))
		shell->exec_type_flag = 1;
	else if (known_commands(cmd) && copy_exec_arg(shell, cmd))
		shell->exec_type_flag = 2;
	if (shell->exec_type_flag)
		return (1);
	return (0);
}

// **************************************************************
// known_commands() returns true if the src string contains any	*
// of the known commands specified in the minishell project		*
// **************************************************************
static int	known_commands(char *src)
{
	if (!ft_strncmp(src, "echo ", 5) || !ft_strncmp(src, "echo\0", 5)
		|| (!ft_strncmp(src, "cd ", 3) || !ft_memcmp(src, "cd\0", 3))
		|| (!ft_strncmp(src, "pwd ", 4) || !ft_memcmp(src, "pwd\0", 4))
		|| (!ft_strncmp(src, "export ", 7) || !ft_memcmp(src, "export\0", 7))
		|| !ft_strncmp(src, "unset ", 6)
		|| (!ft_strncmp(src, "env ", 4) || !ft_memcmp(src, "env\0", 4))
		|| (!ft_strncmp(src, "exit ", 5) || !ft_memcmp(src, "exit\0", 5)))
		return (1);
	return (0);
}

// **********************************************
// checks if a command is a known shell command	*
// **********************************************
int	known_s_commands(char *src)
{
	if ((!ft_strncmp(src, "ls ", 3) || !ft_memcmp(src, "ls\0", 3))
		|| (!ft_strncmp(src, "cat ", 4) || !ft_memcmp(src, "cat\0", 4))
		|| (!ft_strncmp(src, "grep ", 5) || !ft_memcmp(src, "grep\0", 5))
		|| (!ft_strncmp(src, "wc ", 3) || !ft_memcmp(src, "wc\0", 3))
		|| (!ft_strncmp(src, "expr ", 5) || !ft_memcmp(src, "expr\0", 5))
		|| (!ft_strncmp(src, "awk ", 4) || !ft_memcmp(src, "awk\0", 4)))
		return (1);
	return (0);
}
