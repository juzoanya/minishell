/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_execve_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 16:22:41 by euyi              #+#    #+#             */
/*   Updated: 2022/09/11 16:40:18 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

void	copy_one_path(char *exec_args, char **path)
{
	int	i;

	i = 0;
	while (path[0][i] && path[0][i] != ':')
	{
		exec_args[i] = path[0][i];
		i++;
	}
	exec_args[i] = '/';
	exec_args[i + 1] = 0;
	if (path[0][i] == ':')
		path[0] += (i + 1);
	else if (!path[0][i])
		path[0] += i;
}

void	copy_path(char *dest, char **src)
{
	int	i;

	i = 0;
	while (ft_strncmp(src[i], "PATH=", 5))
		i++;
	if (!ft_strncmp(src[i], "PATH=", 5))
		ft_strlcpy(dest, src[i] + 5, ft_strlen(src[i] + 5) + 1);
}
