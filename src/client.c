/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 00:02:31 by arpenel           #+#    #+#             */
/*   Updated: 2025/05/07 00:02:32 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	g_ack_received;

/**
 * Set up signal action and check for errors
 */
void	setup_signal_action(struct sigaction *sa, int signum)
{
	int	result;

	result = sigaction(signum, sa, NULL);
	if (result == -1)
	{
		ft_printf("\033[1;31mError setting up signal handlers\033[0m\n");
		exit(1);
	}
}

/**
 * Handler for acknowledgment signals from server
 */
void	ack_handler(int signum, siginfo_t *siginfo, void *context)
{
	(void)signum;
	(void)context;
	(void)siginfo;
	g_ack_received = 1;
}

/**
 * Send a character bit by bit to the server
 */
void	send_char(int pid, unsigned char character)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((character & (1 << (i))) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		while (!g_ack_received)
			;
		g_ack_received = 0;
	}
}

/**
 * Send the complete message to the server
 */
void	send_message(pid_t server_pid, char *message)
{
	int	i;

	i = 0;
	ft_printf("\033[1;36mSending message to server...\033[0m\n");
	while (message[i])
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_char(server_pid, '\0');
	ft_printf("\033[1;32mMessage sent successfully!\033[0m\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t				server_pid;
	char				*message;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &ack_handler;
	setup_signal_action(&sa, SIGUSR1);
	if (argc != 3)
	{
		ft_printf("\033[1;31mError: Invalid format\033[0m\n");
		ft_printf("\033[1;33mUsage: ./client [SERVER_PID] [MESSAGE]\033[0m\n");
		exit(1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_printf("\033[1;31mError: Invalid server PID\033[0m\n");
		exit(1);
	}
	message = argv[2];
	send_message(server_pid, message);
	return (0);
}