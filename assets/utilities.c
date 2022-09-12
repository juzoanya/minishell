/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juzoanya <juzoanya@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 11:46:31 by juzoanya          #+#    #+#             */
/*   Updated: 2022/09/12 12:42:11 by juzoanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_exit_status(int code)
{
	int	fd;

	fd = open("exit_status", O_RDWR | O_APPEND | O_CREAT | O_TRUNC, 0644);
	ft_putnbr_fd(code, fd);
	if (close(fd) == -1)
		printf("File close error\n");
}

void	read_parse_exit(t_mini *shell)
{
	int		fd;
	char	*buf;

	(void)shell;
	if (!access("exit_status", F_OK))
	{
		fd = open("exit_status", O_RDONLY);
		buf = (char *)malloc(sizeof(char) * 10);
		if (read(fd, buf, 10) == -1)
			printf("File read error\n");
		if (close(fd) == -1)
			printf("File close error\n");
		unlink("exit_status");
	}
	g_exit_status = ft_atoi(buf);
	free(buf);
}
