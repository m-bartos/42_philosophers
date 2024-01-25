/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:21:12 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/25 16:17:36 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	args_error(void)
{
	ft_putstr_fd("Error: Issue with arguments. Input must be an integer, non-negative, and have the correct number of parameters.", 2);
	exit(5);
}

void	zero_philo_error(void)
{
	ft_putstr_fd("Error: At least one philosopher needed.", 2);
	exit(5);
}

void	check_args(int argc, char **argv)
{
	if (argc < 5)
		args_error();
	if (ft_int_atoi(argv[1]) < 0)
		args_error();
	if (ft_int_atoi(argv[1]) == 0)
		zero_philo_error();
	if (ft_int_atoi(argv[2]) < 0)
		args_error();
	if (ft_int_atoi(argv[3]) < 0)
		args_error();
	if (ft_int_atoi(argv[4]) < 0)
		args_error();
	if (argc == 6)
	{
		if (ft_int_atoi(argv[5]) < 0)
			args_error();
	}
	if (argc > 6)
		args_error();
}