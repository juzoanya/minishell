/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-ready_stdin_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:54:49 by euyi              #+#    #+#             */
/*   Updated: 2022/09/11 16:19:51 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

// **************************************************************
// find_heredoc_delim() searches before and after the file being*
// executed for the occurence of "<<". If found, the function	*
// returns the array number immediately after the second		*
// occurence of the angle bracket, else, it returns 0.			*
// **************************************************************
int	find_heredoc_delim(char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (!within_quote(ptr, i) && !ft_strncmp(ptr + i, "<<", 2))
		{
			i += 2;
			while (ptr[i] && ((ptr[i] >= 9 && ptr[i] <= 13) || (ptr[i] == 32)))
				i++;
			if (!forbidden_word(ptr, i) && ptr[i])
				return (i);
		}
		i++;
	}
	return (0);
}

// **********************************
// Simply expands the $ variables	*
// stored in line using the already	*
// existing dollar_processor plugin	*
// that takes shell struct as arg	*
// **********************************
void	expand_env(t_mini *shell, char *line)
{
	char	*tmp;

	tmp = (char *) malloc(MAX_LINE_LEN * sizeof(char));
	ft_strlcpy(tmp, shell->cmd[0], ft_strlen(shell->cmd[0]) + 1);
	ft_strlcpy(shell->cmd[0], line, ft_strlen(line) + 1);
	dollar_processor(shell);
	ft_strlcpy(line, shell->cmd[0], ft_strlen(shell->cmd[0]) + 1);
	ft_strlcpy(shell->cmd[0], tmp, ft_strlen(tmp) + 1);
	free(tmp);
}

// ******************************************************
// Just a function for locating input file name read access permission	*
// ******************************************************
int	find_file_delim(char *ptr)
{
	char	*name;
	int		i;

	name = (char *) malloc(MAX_LINE_LEN * sizeof(char));
	i = 0;
	while (ptr[i])
	{
		if (!within_quote(ptr, i) && !ft_strncmp(ptr + i, "<", 1))
		{
			i += 1;
			while (ptr[i] && ((ptr[i] >= 9 && ptr[i] <= 13) || (ptr[i] == 32)))
				i++;
			copy_one_word(name, ptr + i);
			if (!access(name, R_OK) && (free(name), 1))
				return (i);
		}
		i++;
	}
	return (0);
}
