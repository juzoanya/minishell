/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_processor_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:58:03 by euyi              #+#    #+#             */
/*   Updated: 2022/09/11 16:23:54 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

// **********************************************************
// simply counts and returns the strlen of an envp array	*
// before the occurence of '=' sign							*
// **********************************************************
int	len_b4_eq_sign(const char *ptr)
{
	int	i;

	i = 0;
	while (ptr[i] && ptr[i] != '=')
		i++;
	return (i);
}

// ******************************************************
// cpy_envp_val() copies all data from envp to dest,	*
// and then append the data in src to dest				*
// It returns the strlen of only the chars copied 		*
// from envp to dest									*
// ******************************************************
int	cpy_envp_val(char *dest, char *envp, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		dest[i] = envp[i];
		i++;
	}
	if (src)
	{
		while (src[j])
		{
			dest[i] = src[j];
			i++;
			j++;
		}
	}
	dest[i] = 0;
	return (i - j);
}

// ******************************************************
// overwrite_dest_to_src() copies all elements from		*
// dest into src, overwriting all previous data stored	*
// in src												*
// ******************************************************
void	overwrite_dest_to_src(char *src, char *dest)
{
	int	i;

	i = 0;
	while (dest[i])
	{
		src[i] = dest[i];
		i++;
	}
	src[i] = 0;
}

// ******************************************************
// shifts back all element in an array by one 			*
// array point. EG arr[0] gets overwritten by arr[1],	*
// array[1] gets overwritten by arr[2], ...				*
// ******************************************************
void	shift_back_element(char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		src[i] = src[i + 1];
		i++;
	}
}

// **************************************************************
// last port of call that only activates in case the $attr is	*
// neither found in envp and is also not $?						*
// **************************************************************
void	remove_dollar_attr(char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != ' ')
	{
		i++;
		if (i == 1 && src[i] == '$')
		{
			i = 2;
			break ;
		}
	}
	while (i > 0)
	{
		shift_back_element(src);
		i--;
	}
}
