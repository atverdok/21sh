/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 04:20:41 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 04:20:46 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int	ft_exit(char **args)
{
	if (len_arr_str(args) > 2)
	{
		ft_print_error("ft_exit: ", "", ERR_TMA);
		return (1);
	}
	if (len_arr_str(args) == 2 && ft_atoi(args[1]))
	{
		reset_input_mode();
		ft_putendl("exit");
		exit(ft_atoi(args[1]));
	}
	else if (len_arr_str(args) == 1)
	{
		reset_input_mode();
		ft_putendl("exit");
		exit(0);
	}
	return (1);
}
