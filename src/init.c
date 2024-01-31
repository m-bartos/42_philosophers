/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:22:14 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 10:42:52 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_actual_time_ms(void)
{
	struct timeval	time;
	long			time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = (long)(time.tv_sec * 1000 + time.tv_usec / 1000);
	return (time_in_ms);
}

long int	get_dinner_time(long time)
{
	long	party_time;

	party_time = (get_actual_time_ms() - time);
	return (party_time);
}

void	free_t_program(t_dinner *program)
{
	free(program->philos_arr);
	free(program->shared->forks_mutexes);
	free(program->shared->table_forks);
}

void	init_one_philo(t_philo *philo, t_shared *shared, int id)
{
	philo->id = id;
	philo->eating_start_time = get_actual_time_ms();
	philo->hold_left_fork = 0;
	philo->hold_right_fork = 0;
	philo->shared = shared;
}

int	init_mallocs_in_philos_arr(t_dinner *program)
{
	int	i;
	int	nof_philos;

	nof_philos = program->shared->nof_philos;
	program->philos_arr = (t_philo *) malloc(sizeof(t_philo) * nof_philos);
	if (program->philos_arr == NULL)
		return (0);
	i = 0;
	while (i < nof_philos)
	{
		init_one_philo(&program->philos_arr[i], program->shared, i);
		i++;
	}
	return (1);
}

void	init_fill_t_program(char **argv, t_dinner *dinner, t_shared *shared)
{
	dinner->shared = shared;
	dinner->shared->table_forks = NULL;
	dinner->shared->forks_mutexes = NULL;
	shared->dinner_start_time = get_actual_time_ms();
	dinner->shared->nof_philos = ft_int_atoi(argv[1]);
	shared->init_time_to_die = ft_int_atoi(argv[2]);
	shared->init_time_to_eat = ft_int_atoi(argv[3]);
	shared->init_time_to_sleep = ft_int_atoi(argv[4]);
	shared->dinner_over = 0;
	dinner->philos_arr = NULL;
	dinner->max_eat_rounds = -1;
}

void	add_max_eat_rounds(char	*str_max_eat_rounds, t_dinner *program)
{
	program->max_eat_rounds = ft_int_atoi(str_max_eat_rounds);
}

int	init_mallocs_in_t_shared(t_shared *shared)
{
	int	i;

	shared->forks_mutexes = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * shared->nof_philos);
	if (shared->forks_mutexes == NULL)
		return (0);
	shared->table_forks = (int *) malloc(sizeof(int) * shared->nof_philos);
	if (shared->table_forks == NULL)
		return (0);
	i = 0;
	while (i < shared->nof_philos)
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
