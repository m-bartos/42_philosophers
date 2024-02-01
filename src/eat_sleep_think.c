/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:19:56 by mbartos           #+#    #+#             */
/*   Updated: 2024/02/01 12:30:08 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *philo)
{
	long	dinner_time;

	pthread_mutex_lock(&philo->shared->printf_mtx);
	if (philo->shared->dinner_over == 0)
	{
		dinner_time = get_dinner_time(philo->shared->dinner_start_time);
		printf("%-10ld%-6dis sleeping\n", dinner_time, philo->id + 1);
		pthread_mutex_unlock(&philo->shared->printf_mtx);
		sleep_ms(philo->shared->time_sleep);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->shared->printf_mtx);
		return (0);
	}
}

int	thinking(t_philo *philo)
{
	long	dinner_time;

	pthread_mutex_lock(&philo->shared->printf_mtx);
	if (philo->shared->dinner_over == 0)
	{
		dinner_time = get_dinner_time(philo->shared->dinner_start_time);
		printf("%-10ld%-6dis thinking\n", dinner_time, philo->id + 1);
		pthread_mutex_unlock(&philo->shared->printf_mtx);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->shared->printf_mtx);
		return (0);
	}
}

int	eating(t_philo *philo)
{
	long	dinner_time;

	if (philo->hold_right_fork == 1 && philo->hold_left_fork == 1)
	{
		pthread_mutex_lock(&philo->shared->printf_mtx);
		if (philo->shared->dinner_over == 1)
		{
			pthread_mutex_unlock(&philo->shared->printf_mtx);
			return (0);
		}
		dinner_time = get_dinner_time(philo->shared->dinner_start_time);
		printf("%-10ld%-6dis eating\n", dinner_time, philo->id + 1);
		pthread_mutex_unlock(&philo->shared->printf_mtx);
		pthread_mutex_lock(&philo->eating_start_time_mtx);
		philo->eat_start_time = get_time();
		pthread_mutex_unlock(&philo->eating_start_time_mtx);
		sleep_ms(philo->shared->time_eat);
		pthread_mutex_lock(&philo->nof_meals_mtx);
		philo->nof_meals++;
		pthread_mutex_unlock(&philo->nof_meals_mtx);
		return (1);
	}
	return (0);
}
