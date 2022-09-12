/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: euyi <euyi@student.42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:41:23 by euyi              #+#    #+#             */
/*   Updated: 2022/09/11 16:41:28 by euyi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../assets/minishell.h"

/*****************************************************************/
/* This function processes ^C (SIGINT) and ^\ (SIGQUIT). SIGINT	 */
/* writes a new line and redisplays the content of readline 	 */
/* buffer while SIGQUIT also redisplays the content of readline	 */
/* buffer and deletes its entire line content.					 */
/*****************************************************************/
void	sig_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		g_exit_status = 131;
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("\033[0K", 1);
		return ;
	}
}

/*****************************************************************/
/* init_signal() function declares the sigaction variable signale*/
/* Signale member variables sa_flags is set to 0 and unused and	 */
/* sa_sigaction is set to sig_handler which calls the			 */
/* sig_handler() function.										 */
/*****************************************************************/
void	init_signal(t_mini *shell)
{
	struct sigaction	signale;

	(void)shell;
	signale.sa_flags = 0;
	signale.sa_sigaction = sig_handler;
	if (sigaction(SIGINT, &signale, NULL))
		printf("Sigaction init error!\n");
	if (sigaction(SIGQUIT, &signale, NULL))
		printf("Sigaction init error!\n");
}
