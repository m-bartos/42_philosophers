/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:22:14 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 16:57:16 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mallocs_in_philos_arr(t_dinner *program)
{
	int	i;
	int	nof_philos;

	nof_philos = program->shared->nof_philos;
	program->philos = (t_philo *) malloc(sizeof(t_philo) * nof_philos);
	if (program->philos == NULL)
		return (0);
	i = 0;
	while (i < nof_philos)
	{
		init_one_philo(&program->philos[i], program->shared, i);
		i++;
	}
	return (1);
}

void	init_fill_t_program(char **argv, t_dinner *dinner, t_shared *shared)
{
	dinner->shared = shared;
	dinner->shared->table_forks = NULL;
	dinner->shared->forks_mtxs = NULL;
	shared->dinner_start_time = 0;
	dinner->shared->nof_philos = ft_int_atoi(argv[1]);
	shared->time_die = ft_int_atoi(argv[2]);
	shared->time_eat = ft_int_atoi(argv[3]);
	shared->time_sleep = ft_int_atoi(argv[4]);
	shared->dinner_over = 0;
	dinner->philos = NULL;
	dinner->max_eat_rounds = -1;
}

int	init_mallocs_in_t_shared(t_shared *shared)
{
	int				i;
	int				num_philos;
	unsigned long	size;

	num_philos = shared->nof_philos;
	size = sizeof(pthread_mutex_t);
	shared->forks_mtxs = (pthread_mutex_t *) malloc(size * num_philos);
	if (shared->forks_mtxs == NULL)
		return (0);
	shared->table_forks = (int *) malloc(sizeof(int) * num_philos);
	if (shared->table_forks == NULL)
		return (0);
	i = 0;
	while (i < num_philos)
		shared->table_forks[i++] = 1;
	return (1);
}

void	init(int argc, char **argv, t_dinner *program, t_shared *shared)
{
	init_fill_t_program(argv, program, shared);
	if (!init_mallocs_in_t_shared(shared))
	{
		free_t_program(program);
		exit (21);
	}
	if (!init_mallocs_in_philos_arr(program))
	{
		free_t_program(program);
		exit (22);
	}
	if (argc == 6)
		add_max_eat_rounds(argv[5], program);
}
