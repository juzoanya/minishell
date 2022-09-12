/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:23:55 by juzoanya          #+#    #+#             */
/*   Updated: 2022/09/11 16:20:05 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

void	join_paths(t_mini *shell, char *str, char *pwd)
{
	free(shell->exec_args[1]);
	if (pwd[0] == '\0')
		shell->exec_args[1] = ft_strjoin(str, pwd);
	else if (pwd != NULL && ft_strcmp(str, "/") != 0)
		shell->exec_args[1] = ft_strjoin(pwd, str);
	else if (pwd != NULL && ft_strcmp(str, "/") == 0)
		shell->exec_args[1] = pwd;
}

/************************************************************/
/* This function is called in the update_oldpwd() function	*/
/* and updated the PWD env variable using the executed cd	*/
/* command argv.											*/
/************************************************************/
void	update_pwd(t_mini *shell, char *arg)
{
	int		i;
	int		len;
	char	*pwd;

	i = 0;
	len = 0;
	while (shell->envp[i++] != NULL)
		if (ft_strncmp(shell->envp[i], "PWD", 3) == 0)
			break ;
	len = get_len(shell->envp[i], arg);
	pwd = (char *)malloc(sizeof(char) * len + 4);
	ft_strcpy_ms(pwd, shell->envp[i], arg);
	shell->envp[i] = pwd;
}
