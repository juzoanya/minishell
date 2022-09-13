/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-dollar_processor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:07:37 by euyi              #+#    #+#             */
/*   Updated: 2022/09/13 12:48:36 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

static int	parse_dollar_sign(char *dest, char *src,
				char **envp, t_mini *shell);
static int	expand_dollar_question(char *dest, char *src, t_mini *shell);

void	dollar_processor(t_mini *shell)
{
	int		i;
	char	*tmp;
	char	**cmd;
	int		cycle;

	i = 0;
	tmp = (char *) malloc(MAX_LINE_LEN * sizeof(char));
	cmd = shell->cmd;
	cycle = shell->cycle;
	while (cmd && cmd[cycle][i])
	{
		if (cmd[cycle][i] == '$' && (within_quote(cmd[cycle], i) != 1)
			&& ft_strncmp(cmd[cycle] + i, "$ ", 2)
			&& ft_strncmp(cmd[cycle] + i, "$\0", 2))
			i += parse_dollar_sign(tmp, cmd[cycle] + i, shell->envp, shell) - 1;
		i += 1;
	}
	free (tmp);
}

// **************************************************************
// This function overwrites the $attribute 						*
// from the beginning of src, using dest as a tmp				*
// memory location for copying the remainder of SRC				*
// along with the envp value (if exists for the $attribute)		*
// the return value is the strlen of the arrays that was		*
// overwritten in src											*
// **************************************************************
static int	parse_dollar_sign(char *dest, char *src, char **envp, t_mini *shell)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], src + 1, len_b4_eq_sign(envp[i]))
			&& (*(src + (len_b4_eq_sign(envp[i]) + 1)) == ' '
				|| *(src + (len_b4_eq_sign(envp[i]) + 1)) == 0
				|| *(src + (len_b4_eq_sign(envp[i]) + 1)) == '\''
				|| *(src + (len_b4_eq_sign(envp[i]) + 1)) == '"'))
		{
			j = cpy_envp_val(dest, envp[i] + (len_b4_eq_sign(envp[i]) + 1),
					src + (len_b4_eq_sign(envp[i]) + 1));
			overwrite_dest_to_src(src, dest);
			return (j);
		}
		i++;
	}
	j = expand_dollar_question(dest, src, shell);
	if (j)
		return (j);
	remove_dollar_attr(src);
	return (0);
}

// ******************************************************************
// This function expands the $? when it is found within the			*
// current cmd[cycle] array.										*
// Since it is only called from within the parse_dollar_sign()		*
// it will return the strlen of ft_itoa(shell->last_exit_status)	*
// ******************************************************************
static int	expand_dollar_question(char *dest, char *src, t_mini *shell)
{
	int	j;

	j = 0;
	(void)shell;
	if (!ft_strncmp(src, "$?", 2))
	{
		dest = ft_itoa(g_exit_status);
		j = ft_strlen(dest);
		cpy_envp_val(dest + j, src + 2, NULL);
		overwrite_dest_to_src(src, dest);
		free(dest);
	}
	return (j);
}
