/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec_type_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:34:22 by euyi              #+#    #+#             */
/*   Updated: 2022/09/11 16:23:04 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

// **********************************************************
// copy_exec_arg() is a util function for check_exec_type()	*
// that is located in check_exec_type.c inside the plugins	*
// directory.												*
// It allocates malloc to each array in exec_args			*
// before copying individual words to each arrays from src.	*
// Then it sets the last array in exec_args to NULL and 	*
// returns true												*
// **********************************************************
int	copy_exec_arg(t_mini *shell, char *cmd)
{
	int	i;
	int	n;
	int	tmp;

	i = 0;
	n = 0;
	while (cmd[n] && !forbidden_word(cmd, n))
	{
		tmp = n;
		shell->exec_args[i] = (char *) malloc(MAX_WORD_LEN * sizeof(char *));
		n += copy_valid_arg(shell->exec_args[i], cmd + n);
		if (n == tmp && (free(shell->exec_args[i]), 1))
		{
			shell->exec_args[i] = NULL;
			break ;
		}
		i++;
		while (cmd[n] && ((cmd[n] >= 9 && cmd[n] <= 13) || (cmd[n] == 32)))
			n++;
	}
	shell->exec_args[i] = NULL;
	return (1);
}

// **********************************************************
// forbidden_word() is a util function for check_exec_type()	*
// that is located in check_exec_type.c inside the plugins		*
// directory.			
// forbidden_word() returns true if the src string		*
// begins with any of the list of known words			*
// that shouldn't be a part of cmd flags for the		*
// file or command we want to execute.					*
// ******************************************************
int	forbidden_word(char *src, int n)
{
	if ((!ft_strncmp(src + n, "<", 1) || !ft_strncmp(src + n, ">", 1))
		&& !within_quote(src, n))
		return (1);
	return (0);
}

// **********************************************************
// copy_valid_arg() is a util function for check_exec_type()*
// that is located in check_exec_type.c inside the plugins	*
// directory.	
// It checks if the word at the beginning of src is within	*
// quotes or not, so it can copy that word without the 		*
// quotes.
// Return value is the strlen of the initial word (along 	*
// with quotes if quotes present).							*
// **********************************************************
int	copy_valid_arg(char *exec_args, char *src)
{
	int	i;

	i = 0;
	if (src[0] == '"' || src[0] == '\'')
	{
		i = copy_valid_quote(exec_args, src);
		if (i > 0)
			return (i);
	}
	i = copy_next_word(exec_args, src);
	return (i);
}

// **********************************************************
// copy_valid_quote() is a util function for check_exec_type()
// that is located in check_exec_type.c inside the plugins	
// directory.	
// It helps copy_valid_arg() with processing the copying 	*
// of quoted words from scr to dest.						*
// Return value is the strlen of the word + surrounding		*
// quotes													*
// **********************************************************
int	copy_valid_quote(char *dest, char *src)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (src[i])
	{
		if (src[i] == src[0])
			flag = 1;
		i++;
	}
	if (flag == 0)
		return (0);
	i = 1;
	while (src[i] != src[0])
	{
		dest[i - 1] = src[i];
		i++;
	}
	dest[i - 1] = 0;
	return (i + 1);
}

// **********************************************************
// copy_next_word() is a util function for check_exec_type()*
// that is located in check_exec_type.c inside the plugins	*
// directory.												*
// it copies the first word at the beginning of src to dest	*
// then it returns the strlen of characters copied.			*
// **********************************************************
int	copy_next_word(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] && (src[i] < 9 || (src[i] > 13 && src[i] != 32)))
	{
		dest[i] = src[i];
		dest[i + 1] = 0;
		i++;
	}
	return (i);
}
