/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:02:34 by arpenel           #+#    #+#             */
/*   Updated: 2025/05/07 11:35:29 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	display_banner(int pid)
{
	ft_printf("\n\e[1;35m");
	ft_printf("╔══════════════════════════════════════════════╗\n");
	ft_printf("║              MINITALK SERVER                 ║\n");
	ft_printf("╚══════════════════════════════════════════════╝\n");
	ft_printf("\e[1;36mPID: \e[0;91m%d\033[0m\n", pid);
	ft_printf("\e[1;33mWaiting for messages...\e[0m\n\n>>");
}

void	print_char(char c)
{
	if (c >= 32 && c <= 126)
		write(1, &c, 1);
	else if (c == '\n')
		write(1, &c, 1);
}

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int	current_char = 0;
	static int	bit_index = 0;

	(void)context;
	(void)info;
	if (signal == SIGUSR1)
		current_char |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == '\0')
			ft_printf("\n");
		else
			print_char(current_char);
		current_char = 0;
		bit_index = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	display_banner(getpid());
	sa.sa_sigaction = &signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
