/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:46:51 by mbartos           #+#    #+#             */
/*   Updated: 2024/02/01 12:34:20 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	try_right_fork(t_philo *philo, int id)
{
	long	dinner_time;
	int		philo_id;

	pthread_mutex_lock(&philo->shared->forks_mtxs[id]);
	if (philo->shared->table_forks[id] == 1)
	{
		philo->shared->table_forks[id] = 0;
		philo->hold_right_fork = 1;
		pthread_mutex_lock(&philo->shared->printf_mtx);
		if (philo->shared->dinner_over == 0)
		{
			philo_id = id + 1;
			dinner_time = get_dinner_time(philo->shared->dinner_start_time);
			printf("%-10ld%-6dhas taken a right fork\n", dinner_time, philo_id);
		}
		pthread_mutex_unlock(&philo->shared->printf_mtx);
		pthread_mutex_unlock(&philo->shared->forks_mtxs[id]);
		return (0);
	}
	pthread_mutex_unlock(&philo->shared->forks_mtxs[id]);
	return (1);
}

int	try_left_fork(t_philo *philo, int fork_index)
{
	long	dinner_time;
	int		philo_id;

	pthread_mutex_lock(&philo->shared->forks_mtxs[fork_index]);
	if (philo->shared->table_forks[fork_index] == 1)
	{
		philo->shared->table_forks[fork_index] = 0;
		philo->hold_left_fork = 1;
		pthread_mutex_lock(&philo->shared->printf_mtx);
		if (philo->shared->dinner_over == 0)
		{
			philo_id = philo->id + 1;
			dinner_time = get_dinner_time(philo->shared->dinner_start_time);
			printf("%-10ld%-6dhas taken a left fork\n", dinner_time, philo_id);
		}
		pthread_mutex_unlock(&philo->shared->printf_mtx);
		pthread_mutex_unlock(&philo->shared->forks_mtxs[fork_index]);
		return (0);
	}
	pthread_mutex_unlock(&philo->shared->forks_mtxs[fork_index]);
	return (1);
}

void	take_right_fork(t_philo *philo)
{
	int		in_loop;

	in_loop = 1;
	pthread_mutex_lock(&philo->shared->printf_mtx);
	while (in_loop == 1 && philo->shared->dinner_over == 0)
	{
		pthread_mutex_unlock(&philo->shared->printf_mtx);
		in_loop = try_right_fork(philo, philo->id);
		pthread_mutex_lock(&philo->shared->printf_mtx);
	}
	pthread_mutex_unlock(&philo->shared->printf_mtx);
}

void	take_left_fork(t_philo *philo)
{
	int	fork_index;
	int	in_loop;

	if (philo->id == (philo->shared->nof_philos - 1))
		fork_index = 0;
	else
		fork_index = philo->id + 1;
	in_loop = 1;
	pthread_mutex_lock(&philo->shared->printf_mtx);
	while (in_loop == 1 && philo->shared->dinner_over == 0)
	{
		pthread_mutex_unlock(&philo->shared->printf_mtx);
		in_loop = try_left_fork(philo, fork_index);
		pthread_mutex_lock(&philo->shared->printf_mtx);
	}
	pthread_mutex_unlock(&philo->shared->printf_mtx);
}

void	put_both_forks_on_table(t_philo *philo)
{
	int	fork_index;

	pthread_mutex_lock(&philo->shared->forks_mtxs[philo->id]);
	philo->hold_right_fork = 0;
	philo->shared->table_forks[philo->id] = 1;
	pthread_mutex_unlock(&philo->shared->forks_mtxs[philo->id]);
	if (philo->id == (philo->shared->nof_philos - 1))
		fork_index = 0;
	else
		fork_index = philo->id + 1;
	pthread_mutex_lock(&philo->shared->forks_mtxs[fork_index]);
	philo->hold_left_fork = 0;
	philo->shared->table_forks[fork_index] = 1;
	pthread_mutex_unlock(&philo->shared->forks_mtxs[fork_index]);
}
