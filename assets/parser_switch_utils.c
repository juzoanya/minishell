/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_switch_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:45:47 by euyi              #+#    #+#             */
/*   Updated: 2022/09/09 20:50:47 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// *********************************************************
// segment_cmd() simply segments the commands stored as		*
// a single string in tmp to shorter command sentences		*
// divided according to the number of pipe instructions.	*
// After execution, we will end up having the first cmd		*
// sentence stored in cmd[0], the second stored in			*
// cmd[1], etc. In the end, the cmd[last_array]				*
// is set to NULL											*
// **********************************************************
void	segment_cmd(char **cmd, char *tmp, int i)
{
	int	j;
	int	n;

	n = 0;
	while (tmp[n])
	{
		cmd[i] = (char *) malloc(MAX_LINE_LEN * sizeof(char));
		j = 0;
		while (tmp[n])
		{
			cmd[i][j] = tmp[n];
			j++;
			n++;
			if (!tmp[n] || (tmp[n] == '|' && !within_quote(tmp, n)))
			{
				if (tmp[n])
					n++;
				cmd[i][j] = 0;
				break ;
			}
		}
		i++;
	}
	cmd[i] = NULL;
}

// ******************************************************************
// count_seg() counts the number of times the pipe (|) symbol		*
// stored in char c (param 3)										*
// appeared in the src string. It only counts those occurences of	*
// the pipe (|) symbol that were not enclosed within either			*
// a single or double quotes.										*
// Then it stores the pipe count to shell->pipe_count.				*
// The return value is the pipe (|) symbol count total + 2.			*
// Because if we have X number of pipe, that means we will			*
// need X + 2 arrays to store the separate CMD sentences (including	*
// the NULL pointer in the end)										*
// ******************************************************************
int	count_seg(t_mini *shell, char *src, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (src[i])
	{
		i++;
		if (src[i] == c && !within_quote(src, i))
			count++;
	}
	shell->pipe_count = count;
	return (count + 2);
}

// ******************************************************************
// within_quote() checks if the array element in ptr[arr_point]		*
// is enclosed within either a single or double quote in			*
// the ptr string. If the array element in ptr[arr_point] is		*
// within a single quote, it returns 1, else if it is within		*
// a double quote, it returns 2, else it returns 0 meaning the		*
// array element in ptr[arr_point] is not enclosed within a quote	*
// ******************************************************************
int	within_quote(const char *ptr, int arr_point)
{
	int	i;
	int	one_quot;
	int	two_quot;
	int	flag;

	i = 0;
	one_quot = 0;
	two_quot = 0;
	flag = 0;
	if (!arr_point)
		return (0);
	while (i < arr_point)
	{
		if (ptr[i] == '\'' && two_quot == 0)
			flag = 1;
		else if (ptr[i] == '"' && one_quot == 0)
			flag = 2;
		if (ptr[i] == '\'')
			one_quot++;
		if (ptr[i] == '"')
			two_quot++;
		i++;
	}
	return (within_quote_2(ptr + (i + 1), one_quot, two_quot, flag));
}

// **********************************************************************
// This is the bottom half of within_quote() splitted out to			*
// save line count.														*
// This part checks if a single or double quote is currently open		*
// using the received values stored in one_quot and two_quot.			*
// If yes, it searches for the closing quote from ptr[arr_point + 1]	*
// until the last array element of ptr. If it finds the closing quote	*
// for single quote, it returns 1, if it finds the closing quote for	*
// double quotes, it returns 2, else it returns 0						*
// **********************************************************************
int	within_quote_2(const char *ptr, int one_q, int two_q, int fl)
{
	int	i;

	i = 0;
	if (!(one_q % 2) && !(two_q % 2))
		return (0);
	if (fl == 1 && one_q == 1 && check_closing_quote(ptr, '\''))
		return (1);
	else if (fl == 2 && two_q == 1 && check_closing_quote(ptr, '"'))
		return (2);
	while (ptr[i])
	{
		if (ptr[i] == '\'' && one_q % 2)
			return (1);
		else if (ptr[i] == '"' && two_q % 2)
			return (2);
		i++;
	}
	return (0);
}

// *************************************************
// Just a helper function used by within_quote()	*
// to better manage nested quotes					*
// *************************************************
int	check_closing_quote(const char *ptr, char c)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == c)
			return (1);
		i++;
	}
	return (0);
}
