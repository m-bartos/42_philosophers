/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:22:14 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/25 16:10:12 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_one_philo(t_program *program, t_onephilo *onephilo_to_fill)
{
	onephilo_to_fill->time_to_die = program->init_time_to_die;
	onephilo_to_fill->time_to_eat = program->init_time_to_eat;
	onephilo_to_fill->time_to_sleep = program->init_time_to_sleep;
	onephilo_to_fill->left_fork = 0;
	onephilo_to_fill->right_fork = 0;
}

int	init_philos_arr(t_program *program)
{
	int	i;

	program->philos_arr = (t_onephilo **) malloc (sizeof(t_onephilo *));
	if (program->philos_arr == NULL)
		return (0);
	i = 0;
	while (i < program->nof_forks)
	{
		program->philos_arr[i] = (t_onephilo *) malloc(sizeof(t_onephilo) * 1);
		if (program->philos_arr[i] == NULL)
			return (0);
		init_one_philo(program, program->philos_arr[i]);
		i++;
	}
	return (1);
}

void	init_times(char **argv, t_program *program)
{
	program->init_time_to_die = ft_int_atoi(argv[2]);
	program->init_time_to_eat = ft_int_atoi(argv[3]);
	program->init_time_to_sleep = ft_int_atoi(argv[4]);
	program->time = 0;
	program->max_eat_rounds = -1;
}

int	init_forks(char *str_forks, t_program *program)
{
	int	i;

	program->nof_forks = ft_int_atoi(str_forks);
	program->forks = (int *) malloc(sizeof(int) * (program->nof_forks));
	if (program->forks == NULL)
		return (0);
	i = 0;
	while (i < program->nof_forks)
		program->forks[i++] = 1;
	return (1);
}

int	init_struct_program(char **argv, t_program *program)
{
	if (!init_forks(argv[1], program))
		return (0);
		//free struct
	init_times(argv, program);
	if (!init_philos_arr(program))
		return (0);
		//free struct
	return (1);
}

void	add_max_eat_rounds(char	*str_max_eat_rounds, t_program *program)
{
	program->max_eat_rounds = ft_int_atoi(str_max_eat_rounds);
}

void	init(int argc, char **argv, t_program *program)
{
	//init program
	if (init_struct_program(argv, program) == 0)
		exit(22); // could be inside init_struct
	if (argc == 6)
		add_max_eat_rounds(argv[5], program);
}
