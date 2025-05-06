/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arpenel <arpenel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:38:07 by arpenel           #+#    #+#             */
/*   Updated: 2025/05/04 18:38:13 by arpenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../Libft/includes/libft.h"
# include "../Libft/includes/ft_printf.h"
# include <signal.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

void	ft_handler(int signal, siginfo_t *info, void *context);
void	ft_signal(int pid, unsigned char character);
void	signal_handler(int signum, siginfo_t *siginfo, void *context);
void	error_sigaction(struct sigaction *sa, int signum);

#endif