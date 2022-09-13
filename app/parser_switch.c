/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_switch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:44:29 by euyi              #+#    #+#             */
/*   Updated: 2022/09/13 12:47:42 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

static int	exit_true(const char *tmp);

// **********************************************
// Just an extension of parser_switch() below	*
// **********************************************
static void	parser_switch_2(t_mini *shell)
{
	int		i;

	i = 0;
	dup2(shell->stdin_tmp, DEF_STDIN);
	while (shell->cmd && shell->cmd[i] && (free(shell->cmd[i]), 1))
	{
		shell->cmd[i] = NULL;
		i++;
	}
	if (shell->cmd)
		free(shell->cmd);
	shell->cmd = NULL;
	if (!access("heredoc", F_OK))
		unlink("heredoc");
	if (!access("ex_", F_OK))
		unlink("ex_");
}

// ******************************************************
// When param 2 (flag) is true,							*
// parser_switch() takes first line command inputs		*
// from the minishell, segment and stores these inputs	*
// in shell->cmd and then sends the input to 			*
// exec_commands() for processing. 					*
// But if flag is false, parser_switch() simply			*
// frees the memory used for storing the commands		*
// and also deletes the heredoc file if need be.		*
// ******************************************************
void	parser_switch(t_mini *shell, int flag)
{
	char	*tmp;

	if (flag)
	{
		shell->stdin = -1;
		shell->stdin_tmp = dup(DEF_STDIN);
		tmp = readline ("~$ ");
		if ((!tmp || exit_true(tmp)) && (free(tmp), 1))
		{
			shell->exit = 2;
			return ;
		}
		if (ft_strlen(tmp) != 0)
			add_history(tmp);
		else if (!ft_strlen(tmp) && (free(tmp), 1))
			return ;
		shell->cmd = (char **)malloc(count_seg(shell, tmp, '|')
				* sizeof(char *));
		segment_cmd(shell->cmd, tmp, 0);
		free(tmp);
	}
	if (!access("ex_", F_OK))
		unlink("ex_");
	if (!flag)
		parser_switch_2(shell);
}

// ***************************************************************
// This function copies the DEFAULT ENV to our custom			*
// env declared within the t_mini structure.					*
// So as to enable read, write, and update on the 				*
// env data by export, unset, and scalar variable assignments	*
// If param 2(envp) receives the pointer to the default ENV as 	*
// argument, it will alloc memory to shell->env and copy all 	*
// the default data from default ENV to shell->env, appending	*
// "\0DF\0" at the end of each string to identify the default	*
// ENVs from future modifications to shell->env by export, 		*
// unset, and scalar variable assignments
// ***************************************************************
void	shell_env_switch(t_mini *shell, char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		g_exit_status = 0;
		shell->exit = 0;
		shell->cmd = NULL;
		shell->envp = (char **) malloc(MAX_ARR_CNT * sizeof(char *));
		while (envp[i])
		{
			shell->envp[i] = (char *) malloc(MAX_LINE_LEN * sizeof(char));
			ft_strlcpy(shell->envp[i], envp[i], ft_strlen(envp[i]) + 1);
			ft_memcpy(shell->envp[i] + ft_strlen(envp[i]), "\0DF\0", 4);
			i++;
			shell->envp[i] = NULL;
		}
	}
	else if (!envp)
	{
		while (shell->envp && shell->envp[i] && (free(shell->envp[i]), 1))
			i++;
		if (shell->envp)
			free(shell->envp);
	}
}

// **********************************
// Simply checks if we received		*
// exit as cmd argument 			*
// if yes, it returns true, else	*
// it returns false					*
// **********************************
static int	exit_true(const char *tmp)
{
	while (*tmp && ((*tmp >= 9 && *tmp <= 13) || (*tmp == 32)))
		tmp++;
	if (!ft_memcmp(tmp, "exit\0", 5) || !ft_memcmp(tmp, "exit ", 5))
		return (1);
	return (0);
}

// **************************************************
// Just a function to ensure our minishell checks	*
// that PATH, PWD and HOME are present in			*
// envp before running								*
// ***************************************************
int	envp_validator(t_mini *shell)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], "PATH=", 5)
			|| !ft_strncmp(shell->envp[i], "PWD=", 4)
			|| !ft_strncmp(shell->envp[i], "HOME=", 5))
			flag += 1;
		i++;
	}
	if (flag == 3)
		return (1);
	printf("HOME, PATH or PWD environment path missing or corrupted!\n");
	g_exit_status = 127;
	return (0);
}
