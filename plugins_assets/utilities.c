/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:46:31 by juzoanya          #+#    #+#             */
/*   Updated: 2022/09/13 12:44:24 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

void	write_exit_status(int code)
{
	int	fd;

	fd = open("ex_", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_putnbr_fd(code, fd);
	if (close(fd) == -1)
		printf("File close error\n");
}

void	read_parse_exit(t_mini *shell)
{
	int		fd;
	int		i;
	char	*buf;

	(void)shell;
	if (!access("ex_", R_OK))
	{
		fd = open("ex_", O_RDONLY);
		buf = (char *)malloc(sizeof(char) * 10);
		i = read(fd, buf, 10);
		unlink("ex_");
		close(fd);
		if (i == -1 && (free(buf), 1))
			return ;
		buf[i] = 0;
		g_exit_status = ft_atoi(buf);
		free(buf);
	}
}

// **************************************************************
// This function is used by valid_scalar_var() to check if the	*
// char arg received qualifies as a variable name character.	*
// It returns 2 if the char C qualifies to either be			*
// at the beginning of the var name or exist within the			*
// names. else it returns 1 if C doesnt qualify to be			*
// at the beginning of the var name but C qualifies to exist	*
// within the var names.										*
// else it returns 0 if the char C doesn't qualify at all.		*
// **************************************************************
static int	valid_var_name(char c)
{
	char	*begin;
	char	*exist;
	int		flag;

	begin = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";
	exist = "0123456789";
	flag = 0;
	while (*begin)
	{
		if (c == *begin)
			flag = 2;
		begin++;
	}
	while (*exist)
	{
		if (c == *exist)
			flag = 1;
		exist++;
	}
	return (flag);
}

// **************************************************************
// This function scrutinizes the argument received to see		*
// if the string's content are a valid scalar var assignment	*
// request.														*
// value is 1 for a valid scalar var assignment, else it 		*
// returns 0 for an invalid scalar var assignment				*
// **************************************************************
int	valid_scalar_var(const char *src, int flag)
{
	int	i;

	i = 0;
	while (src[i] && ((src[i] >= 9 && src[i] <= 13) || (src[i] == 32)))
		i++;
	if (valid_var_name(src[i]) == 2)
		flag += 1;
	while (src[i] && valid_var_name(src[i]) && src[i] != '=')
		i++;
	if (src[i] == '=' && ++i)
		flag += 1;
	else if ((src[i] == '*' || src[i] == '$' || src[i] == '#')
		&& printf("Export error!\n"))
		return (0);
	if (src[i] == '\'' || src[i] == '"')
		i++;
	while (src[i] && within_quote(src, i))
		i++;
	while (src[i] && (src[i] < 9 || (src[i] > 13 && src[i] != 32)))
		i++;
	while (src[i] && ((src[i] >= 9 && src[i] <= 13) || (src[i] == 32)))
		i++;
	if (flag == 2 && !src[i])
		return (1);
	return (0);
}

// *****************************************************************
// free_exec_args() frees all heap memories used by current segment	*
// **************************************************************
void	reset_segment_memory(t_mini *shell)
{
	int	i;

	i = 0;
	while (shell->exec_args && shell->exec_args[i])
	{
		free(shell->exec_args[i]);
		shell->exec_args[i] = NULL;
		i++;
	}
	if (shell->exec_args)
		free(shell->exec_args);
	shell->exec_args = NULL;
	shell->exec_type_flag = 0;
	shell->pipe_count--;
}
