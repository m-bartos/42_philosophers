/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:46:51 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 14:56:40 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_right_fork(t_philo *philo)
{
	int		in_loop;
	long	dinner_time;

	in_loop = 1;
	pthread_mutex_lock(&philo->shared->printf_mutex);
	while (in_loop == 1 && philo->shared->dinner_over == 0)
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		pthread_mutex_lock(&philo->shared->forks_mutexes[philo->id]);
		if (philo->shared->table_forks[philo->id] == 1)
		{
			philo->shared->table_forks[philo->id] = 0;
			philo->hold_right_fork = 1;
			pthread_mutex_lock(&philo->shared->printf_mutex);
			if (philo->shared->dinner_over == 0)
			{
				dinner_time = get_dinner_time(philo->shared->dinner_start_time);
				printf("%-10ld%-6dhas taken a right fork\n", dinner_time, philo->id);
			}
			pthread_mutex_unlock(&philo->shared->printf_mutex);
			in_loop = 0;
		}
		pthread_mutex_unlock(&philo->shared->forks_mutexes[philo->id]);
		pthread_mutex_lock(&philo->shared->printf_mutex);
	}
	pthread_mutex_unlock(&philo->shared->printf_mutex);
}

void	grab_left_fork(t_philo *philo)
{
	int	fork_index;
	int	in_loop;

	if (philo->id == (philo->shared->nof_philos - 1))
		fork_index = 0;
	else
		fork_index = philo->id + 1;
	in_loop = 1;
	pthread_mutex_lock(&philo->shared->printf_mutex);
	while (in_loop == 1 && philo->shared->dinner_over == 0)
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		pthread_mutex_lock(&philo->shared->forks_mutexes[fork_index]);
		if (philo->shared->table_forks[fork_index] == 1)
		{
			philo->shared->table_forks[fork_index] = 0;
			philo->hold_left_fork = 1;
			pthread_mutex_lock(&philo->shared->printf_mutex);
			if (philo->shared->dinner_over == 0)
				printf("%-10ld%-6dhas taken a left fork\n", get_dinner_time(philo->shared->dinner_start_time), philo->id);
			pthread_mutex_unlock(&philo->shared->printf_mutex);
			in_loop = 0;
		}
		pthread_mutex_unlock(&philo->shared->forks_mutexes[fork_index]);
		pthread_mutex_lock(&philo->shared->printf_mutex);
	}
	pthread_mutex_unlock(&philo->shared->printf_mutex);
}

void	put_both_forks_on_table(t_philo *philo)
{
	int	fork_index;

	pthread_mutex_lock(&philo->shared->forks_mutexes[philo->id]);
	philo->hold_right_fork = 0;
	philo->shared->table_forks[philo->id] = 1;
	pthread_mutex_unlock(&philo->shared->forks_mutexes[philo->id]);
	if (philo->id == (philo->shared->nof_philos - 1))
		fork_index = 0;
	else
		fork_index = philo->id + 1;
	pthread_mutex_lock(&philo->shared->forks_mutexes[fork_index]);
	philo->hold_left_fork = 0;
	philo->shared->table_forks[fork_index] = 1;
	pthread_mutex_unlock(&philo->shared->forks_mutexes[fork_index]);
}

int	eating(t_philo *philo)
{
	long	dinner_time;

	pthread_mutex_lock(&philo->shared->printf_mutex);
	if (philo->shared->dinner_over == 1)
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		return (0);
	}
	dinner_time = get_dinner_time(philo->shared->dinner_start_time);
	printf("%-10ld%-6dis eating\n", dinner_time, philo->id);
	pthread_mutex_unlock(&philo->shared->printf_mutex);
	pthread_mutex_lock(&philo->eating_start_time_mutex);
	philo->eating_start_time = get_actual_time();
	pthread_mutex_unlock(&philo->eating_start_time_mutex);
	sleep_ms(philo->shared->init_time_to_eat);
	pthread_mutex_lock(&philo->nof_meals_mutex);
	philo->nof_meals++;
	pthread_mutex_unlock(&philo->nof_meals_mutex);
	return (1);
}
