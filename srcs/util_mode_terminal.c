/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_mode_terminal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 15:02:09 by atverdok          #+#    #+#             */
/*   Updated: 2017/06/21 15:02:12 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void	reset_input_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_saved_attributes);
}

void	save_attributes(void)
{
	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("Not a terminal.\n", 2);
		exit(EXIT_FAILURE);
	}
	tcgetattr(STDIN_FILENO, &g_saved_attributes);
}

void	set_input_mode(void)
{
	struct termios tattr;

	if (!isatty(STDIN_FILENO))
	{
		ft_putstr_fd("Not a terminal.\n", 2);
		exit(EXIT_FAILURE);
	}
	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ICANON | ECHO | ISIG);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &tattr);
}
