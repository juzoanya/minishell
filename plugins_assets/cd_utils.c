/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 09:03:01 by juzoanya          #+#    #+#             */
/*   Updated: 2022/09/11 16:20:45 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

/*****************************************************************/
/* get_len() functions counts the length of a given env variable */
/* name until the '=' sign & adds the length of the env variable */
/* path returned by calling get_path() function.				 */
/*****************************************************************/
int	get_len(char *str_env, char *pwd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str_env[i++] != '=')
		len++;
	len++;
	len += ft_strlen(pwd);
	return (len);
}

/********************************************************************/
/* set_cd_flags() sets the a_path & cd_flag variable values			*/
/* declared in call_run_cd() by examining the cd command argv		*/
/* path, flag = cd_flag. Flag is set to '1' if argv is an			*/
/* absolute path, else it's set to '2' if argv begins				*/
/* with '..' indicating a move up one or more directory, it's set to*/
/* '3' if argv begins with a tilda, a move to home directory		*/
/********************************************************************/
void	set_cd_flags(t_mini *shell, int *flag)
{
	if (shell->exec_args[1][0] == '/')
		*flag = 1;
	else if (ft_strncmp(shell->exec_args[1], "..", 2) == 0)
		*flag = 2;
	else if (ft_strncmp(shell->exec_args[1], "~", 1) == 0)
		*flag = 3;
}

/************************************************************/
/* ft_strcpy_ms() concatenates the variable name of the env	*/
/* variable until the '=' sign with the new path of the		*/
/* variable.												*/
/************************************************************/
void	ft_strcpy_ms(char *dest, char *s1, char *s2)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = -1;
	while (s1[++i] != '=')
		dest[++j] = s1[i];
	dest[++j] = '=';
	while (s2[++k] != '\0')
		dest[++j] = s2[k];
	dest[++j] = '\0';
	dest[++j] = 'D';
	dest[++j] = 'F';
	dest[++j] = '\0';
}

/************************************************************/
/* strip_append() remove all leading '.', '/' and '~' as	*/
/* well as the trailing '/' and writes the remaining content*/
/* of user inputed cd argv to null-terminated string 'str'	*/
/************************************************************/
void	strip_append(char **str, t_mini *shell)
{
	int	i;
	int	n;
	int	len;

	i = 0;
	n = 0;
	len = ft_strlen(shell->exec_args[1]);
	while (shell->exec_args[1][i] == '.' || shell->exec_args[1][i] == '/'
		|| shell->exec_args[1][i] == '~')
		i++;
	str[0][n] = '/';
	while (shell->exec_args[1][i] != '\0')
	{
		if (i == len -1 && shell->exec_args[1][i] == '/')
			i++;
		else
			str[0][++n] = shell->exec_args[1][i++];
	}
	str[0][++n] = '\0';
}

/************************************************************/
/* get_path() function is a util function used to obtain a	*/
/* null-terminated path (the part after the '=' sign) of a	*/
/* given env variable and returns it.						*/
/************************************************************/
char	*get_path(t_mini *shell, char *var)
{
	int		i;
	int		n;
	char	*path;
	char	*ret;

	i = -1;
	n = 0;
	while (shell->envp[++i] != NULL)
		if (ft_strncmp(shell->envp[i], var, ft_strlen(var)) == 0)
			break ;
	path = ft_strchr(shell->envp[i], '=');
	ret = (char *)malloc(sizeof(char) * ft_strlen(path));
	i = 0;
	while (path[++i] != '\0')
		ret[n++] = path[i];
	ret[n] = '\0';
	return (ret);
}
