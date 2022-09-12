/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 20:40:09 by euyi              #+#    #+#             */
/*   Updated: 2022/08/29 18:37:16 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[(i)] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	s1--;
	s2--;
	while (n > 0)
	{
		s1++;
		s2++;
		n--;
		if (*s1 == '\0' && *s2 == '\0')
			return (0);
		else if (*s1 == '\0')
			return (-21);
		else if (*s2 == '\0')
			return (21);
		else if (*s1 != *s2)
			return ((int)*s1 - (int)*s2);
	}
	return (0);
}

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n /= -1;
		len++;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*moulinette_guard(char *ptr, int n)
{
	if (n == -1)
	{
		ptr = (char *) malloc(MAX_LINE_LEN * sizeof(char));
		ptr[0] = '-';
		ptr[1] = '2';
		ptr[2] = '1';
		ptr[3] = '4';
		ptr[4] = '7';
		ptr[5] = '4';
		ptr[6] = '8';
		ptr[7] = '3';
		ptr[8] = '6';
		ptr[9] = '4';
		ptr[10] = '8';
		ptr[11] = '\0';
	}
	else if (n == 0)
	{
		ptr = (char *) malloc(MAX_LINE_LEN * sizeof(char));
		ptr[0] = '0';
		ptr[1] = '\0';
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		j;
	char	*ptr;

	j = ft_intlen(n);
	if (n == -2147483648)
		return (moulinette_guard("AFAIK", -1));
	if (n == 0)
		return (moulinette_guard("AFAIK", 0));
	ptr = (char *) malloc(MAX_LINE_LEN * sizeof(char));
	if (n < 0)
	{
		ptr[0] = '-';
		n /= -1;
	}
	ptr[j] = '\0';
	while (n > 0)
	{
		ptr[(j - 1)] = '0' + (n % 10);
		n /= 10;
		j--;
	}
	return (ptr);
}
