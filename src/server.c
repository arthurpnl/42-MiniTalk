/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:02:34 by arpenel           #+#    #+#             */
/*   Updated: 2025/05/07 00:02:37 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/**
 * Display a single character to standard output
 */
void	print_char(char c)
{
	write(1, &c, 1);
}

/**
 * Display server banner with PID information
 */
void	display_banner(int pid)
{
	ft_printf("\n\e[1;35m");
	ft_printf("╔══════════════════════════════════════════════╗\n");
	ft_printf("║              MINITALK SERVER                ║\n");
	ft_printf("╚══════════════════════════════════════════════╝\n");
	ft_printf("\e[1;36mPID: \e[0;91m%d\033[0m\n", pid);
	ft_printf("\e[1;33mWaiting for messages...\e[0m\n\n>>");
}

/**
 * Signal handler function
 * Reconstructs characters bit by bit from received signals
 */
void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int	current_char;
	static int	bit_index;

	(void)context;
	if (!info->si_pid)
		exit(0);
	if (signal == SIGUSR1)
		current_char |= (1 << bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == '\0')
		{
			ft_printf("\n");
			kill(info->si_pid, SIGUSR1);
		}
		else
			print_char(current_char);
		bit_index = 0;
		current_char = 0;
	}
	kill(info->si_pid, SIGUSR1);
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