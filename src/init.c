/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:22:14 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/26 15:26:02 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_t_program(t_program *program)
{
	free(program->philos_arr);
}

void	init_one_philo(t_program *program, t_onephilo *philo)
{
	philo->time_to_die = program->init_time_to_die;
	philo->time_to_eat = program->init_time_to_eat;
	philo->time_to_sleep = program->init_time_to_sleep;
	philo->hold_left_fork = 0;
	philo->hold_right_fork = 0;
	philo->fork_on_table = 1;
}

int	init_philos_arr(t_program *program)
{
	int	i;

	program->philos_arr = (t_onephilo *) malloc (sizeof(t_onephilo ) * program->nof_philos);
	if (program->philos_arr == NULL)
		return (0);
	i = 0;
	while (i < program->nof_philos)
	{
		init_one_philo(program, &(program->philos_arr[i]));
		i++;
	}
	return (1);
}

void	init_fill_t_program(char **argv, t_program *program)
{
	program->nof_philos = ft_int_atoi(argv[1]);
	program->philos_arr = NULL;
	program->init_time_to_die = ft_int_atoi(argv[2]);
	program->init_time_to_eat = ft_int_atoi(argv[3]);
	program->init_time_to_sleep = ft_int_atoi(argv[4]);
	program->time = 0;
	program->max_eat_rounds = -1;
}

void	add_max_eat_rounds(char	*str_max_eat_rounds, t_program *program)
{
	program->max_eat_rounds = ft_int_atoi(str_max_eat_rounds);
}

int	init_t_program(int argc, char **argv, t_program *program)
{
	init_fill_t_program(argv, program);
	if (!init_philos_arr(program))
		return (0);
	if (argc == 6)
		add_max_eat_rounds(argv[5], program);
	return (1);
}

void	init(int argc, char **argv, t_program *program)
{
	//init t_program struct with argvs
	if (init_t_program(argc, argv, program) == 0)
	{
		free_t_program(program);
		exit(22);
	}
}
