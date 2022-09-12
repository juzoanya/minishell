/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:03:32 by euyi              #+#    #+#             */
/*   Updated: 2022/09/10 21:18:35 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

/************************************************************/
/* This function is called in the call_run_cd() function and*/
/* updates OLDPWD env variable using the current PWD env	*/
/* variable.												*/
/************************************************************/
void	update_oldpwd(t_mini *shell, char *cmd_arg)
{
	int		i;
	int		len;
	char	*path;
	char	*oldpwd;

	i = 0;
	len = 0;
	while (shell->envp[i++] != NULL)
		if (ft_strncmp(shell->envp[i], "OLDPWD", 6) == 0)
			break ;
	path = get_path(shell, "PWD");
	len = get_len(shell->envp[i], path);
	oldpwd = (char *)malloc(sizeof(char) * len + 4);
	ft_strcpy_ms(oldpwd, shell->envp[i], path);
	shell->envp[i] = oldpwd;
	update_pwd(shell, cmd_arg);
}

/************************************************************/
/* This function is called in the call_run_cd() function if	*/
/* cd argv leads with a tilda '~' Function expands the HOME	*/
/* env variable and appends any subdirectories from argv	*/
/* using ft_strjoin().										*/
/************************************************************/
void	get_home_dir(t_mini *shell)
{
	int		i;
	char	*path;
	char	*str;

	i = -1;
	while (shell->envp[++i] != NULL)
		if (ft_strncmp(shell->envp[i], "HOME", 4) == 0)
			break ;
	path = get_path(shell, "HOME");
	str = (char *)malloc(sizeof(char) * \
		(ft_strlen(shell->exec_args[1]) + ft_strlen(path)));
	strip_append(&str, shell);
	if (ft_strcmp(str, "/") == 0)
		shell->exec_args[1] = path;
	else
		shell->exec_args[1] = ft_strjoin(path, str);
	free(str);
}

/************************************************************/
/* This function is called in the call_run_cd() function if	*/
/* cd argv leads with a '..' Function iterate through argv &*/
/* for every '../' encountered, sets trailing directory name*/
/* to '\0'.													*/
/************************************************************/
void	get_dir_path(t_mini *shell)
{
	int		i;
	char	*str;
	char	*pwd;
	int		len;

	i = -1;
	pwd = get_path(shell, "PWD");
	len = ft_strlen(pwd) + 1;
	while (shell->exec_args[1][++i] != '\0')
	{
		if (shell->exec_args[1][i] == '.' && shell->exec_args[1][i + 1] == '.')
		{
			while (pwd[--len] != '/' && len >= 0)
				pwd[len] = '\0';
			pwd[len] = '\0';
			i += 2;
		}
	}
	str = (char *)malloc(sizeof(char) * ft_strlen(shell->exec_args[1]) + 2);
	strip_append(&str, shell);
	join_paths(shell, str, pwd);
	free(str);
}

/************************************************************/
/* This is the parent function for the 'cd' command. It		*/
/* calls the set_cd_flags() function in cd_utils.c file and	*/
/* processes the cd argv into an executable directory path	*/
/* for the chdir() if it's neither a move up director (in	*/
/* which case it calls the get_dir_path() function) nor a	*/
/* home directory path (in which case it calls the			*/
/* get_home_dir() function). Processed path is parsed to	*/
/* chdir() and the update_oldpwd() function is called to	*/
/* update the OLPWD and PWD environment variables.			*/
/************************************************************/
int	call_run_cd(t_mini *shell)
{
	char	*str;
	int		flags;

	flags = 0;
	if (shell->exec_args[1] == NULL)
		return (0);
	set_cd_flags(shell, &flags);
	if (!flags)
	{
		str = (char *)malloc(sizeof(char) * ft_strlen(shell->exec_args[1]) + 2);
		strip_append(&str, shell);
		shell->exec_args[1] = ft_strjoin(get_path(shell, "PWD"), str);
		free(str);
	}
	else if (flags == 2)
		get_dir_path(shell);
	else if (flags == 3)
		get_home_dir(shell);
	if (chdir(shell->exec_args[1]) != 0)
	{
		printf("cd: No such file or directory\n");
		return (1);
	}
	update_oldpwd(shell, shell->exec_args[1]);
	return (0);
}

//This is just a sample of how run_ functions/plugin will look like
void	run_cd(t_mini *shell)
{
	int	i;

	i = -1;
	if (shell->exec_type_flag == 2 && !ft_memcmp(shell->exec_args[0], "cd\0", 3))
	{
		if (count_args(shell->exec_args) > 2)
		{
			printf("cd: too many arguments\n");
			while (shell->exec_args[++i] != NULL)
				printf("%s\n", shell->exec_args[i]);
			g_exit_status = 1;
			return ;
		}
		g_exit_status = call_run_cd(shell);
	}
}
