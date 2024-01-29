/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:22:14 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/29 14:42:57 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_actual_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000);
}

long int	get_party_time(long int time)
{
	return (get_actual_time_ms() - time);
}

void	free_t_program(t_program *program)
{
	free(program->philos_arr);
	free(program->shared->forks_mutex);
	free(program->shared->table_forks);
}

void	init_one_philo(t_onephilo *philo, t_shared_info *shared, int id)
{
	philo->id = id;
	philo->time_to_die = shared->init_time_to_die;
	philo->time_to_eat = shared->init_time_to_eat;
	philo->time_to_sleep = shared->init_time_to_sleep;
	philo->hold_left_fork = 0;
	philo->hold_right_fork = 0;
	philo->shared = shared;
}

int	init_mallocs_in_philos_arr(t_program *program, t_shared_info *shared)
{
	int	i;

	program->philos_arr = (t_onephilo *) malloc (sizeof(t_onephilo) * shared->nof_philos);
	if (program->philos_arr == NULL)
		return (0);
	i = 0;
	while (i < shared->nof_philos)
	{
		init_one_philo(&(program->philos_arr[i]), shared, i);
		i++;
	}
	return (1);
}

void	init_fill_t_program(char **argv, t_program *program, t_shared_info *shared)
{
	program->shared = shared;
	program->shared->table_forks = NULL;
	program->shared->forks_mutex = NULL;
	shared->time = get_actual_time_ms();
	program->shared->nof_philos = ft_int_atoi(argv[1]);
	shared->init_time_to_die = ft_int_atoi(argv[2]);
	shared->init_time_to_eat = ft_int_atoi(argv[3]);
	shared->init_time_to_sleep = ft_int_atoi(argv[4]);
	program->philos_arr = NULL;
	program->max_eat_rounds = -1;

}

void	add_max_eat_rounds(char	*str_max_eat_rounds, t_program *program)
{
	program->max_eat_rounds = ft_int_atoi(str_max_eat_rounds);
}

int	init_mallocs_in_t_shared(t_shared_info *shared)
{
	int i;

	shared->forks_mutex = (pthread_mutex_t *) malloc (sizeof(pthread_mutex_t) * shared->nof_philos);
	if (shared->forks_mutex == NULL)
		return (0);
	shared->table_forks= (int *) malloc (sizeof(int) * shared->nof_philos);
	if (shared->table_forks == NULL)
		return (0);
	i = 0;
	while (i < shared->nof_philos)
	{
		shared->table_forks[i] = 1;
		i++;
	}
	return (1);
}

int	init_t_program(int argc, char **argv, t_program *program, t_shared_info *shared)
{

	init_fill_t_program(argv, program, shared);
	if (!init_mallocs_in_t_shared(shared))
		return (0);
	if (!init_mallocs_in_philos_arr(program, shared))
		return (0);
	if (argc == 6)
		add_max_eat_rounds(argv[5], program);
	return (1);
}

void	init(int argc, char **argv, t_program *program, t_shared_info *shared)
{
	//init t_program struct with argvs
	if (init_t_program(argc, argv, program, shared) == 0)
	{
		free_t_program(program);
		exit(22);
	}
}
