/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_env_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:11:29 by euyi              #+#    #+#             */
/*   Updated: 2022/09/11 16:44:53 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

// **************************************************
// this function first copies src1 to dest, then	*
// it appends src2 at the end of dest.				*
// then if flag is true, it appends "\0DF\0" 		*
// at the end of dest								*
// return value is always true						*
// **************************************************
int	copy_var_to_env(char *dest, const char *src2, char *src1, int flag)
{
	int	i;
	int	flag2;

	flag2 = 0;
	i = ft_strlcpy(dest, src1, ft_strlen(src1) + 1);
	src2 += len_b4_eq_sign(src2) + 1;
	copy_one_word(dest + i, src2);
	if (*src2 == '\'' && find_closing_quote(src2 + 1, '\'') && ++src2)
		flag2 = 39;
	else if (*src2 == '"' && find_closing_quote(src2 + 1, '"') && ++src2)
		flag2 = 34;
	while (*src2 && flag2 && *src2 != flag2)
		src2++;
	if ((*src2 == '\'' || *src2 == '"') && ++src2
		&& (*src2 < 9 || (*src2 > 13 && *src2 != 32)))
		copy_one_word(dest + ft_strlen(dest), src2);
	if (flag == 1)
		ft_memcpy(dest + ft_strlen(dest), "\0DF\0", 4);
	return (1);
}

// **************************************************
// This function is used by scalar_var_assignor to	*
// copy the envp name characters from src to dest	*
// **************************************************
void	copy_envp_name(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (*src && ((*src >= 9 && *src <= 13) || (*src == 32)))
		src++;
	while (src[i] && src[i] != '=')
	{
		dest[i] = src[i];
		i++;
		if (i == 99)
			break ;
	}
	dest[i] = '=';
	dest[i + 1] = 0;
}

// just an extension of run_export() below
static void	run_export_2(t_mini *shell, char *src, int flag, char *name)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (!ft_memcmp(shell->envp[i], " \0", 2) && flag
			&& copy_var_to_env(shell->envp[i], src, name, 1))
			return ;
		i++;
	}
	shell->envp[i] = (char *) malloc(MAX_LINE_LEN * sizeof(char));
	shell->envp[i + 1] = NULL;
	copy_var_to_env(shell->envp[i], src, name, 1);
}

// ******************************************
// This function runs the export builtin.	*
// src is a pointer to the beginning of the	*
// export argument. If flag is false, it	*
// means that we're only supposed to export	*
// the name of an existing scalar variable.	*
// If flag is true, it means that we're 	*
// supposed to create a new scalar variable	*
// and then export it.						*
// accordingly using the right flag			*
// ******************************************
void	run_export(t_mini *shell, char *src, int flag)
{
	int		i;
	char	name[100];

	i = 0;
	copy_envp_name(name, src);
	while (shell->envp[i])
	{
		if (flag && !ft_strncmp(shell->envp[i], name, ft_strlen(name))
			&& copy_var_to_env(shell->envp[i], src, name, 1))
			return ;
		else if (!flag && !ft_strncmp(shell->envp[i], name, ft_strlen(name))
			&& (ft_memcpy(shell->envp[i] + ft_strlen(shell->envp[i]),
					"\0DF\0", 4), 1))
			return ;
		i++;
	}
	if (!flag)
		return ;
	run_export_2(shell, src, flag, name);
}
