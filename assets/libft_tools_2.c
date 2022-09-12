/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:37:20 by euyi              #+#    #+#             */
/*   Updated: 2022/09/07 21:52:32 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	hold;
	size_t	i;

	hold = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while ((i < size - 1) && (i != hold))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	return (hold);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
		i--;
	}	
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*mem;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	mem = (char *)malloc(sizeof(*mem) * (len + 1));
	if ((s1 == NULL || s2 == NULL) || mem == NULL)
		return (NULL);
	while (*s1 != '\0')
	{
		mem[i] = *s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		mem[i] = *s2++;
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*ptr;

	ptr = dest;
	while (n > 0)
	{
		*(char *)dest = *(char *)src;
		dest++;
		src++;
		n--;
	}
	return (ptr);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		if (((unsigned char *)s1)[(i)] != ((unsigned char *)s2)[(i)])
			return (((unsigned char *)s1)[(i)] - ((unsigned char *)s2)[(i)]);
		i++;
		n--;
	}
	return (0);
}
