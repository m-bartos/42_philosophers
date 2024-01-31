/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping_thinking.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:19:56 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 17:01:32 by mbartos          ###   ########.fr       */
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
		printf("%-10ld%-6dis sleeping\n", dinner_time, philo->id);
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
		printf("%-10ld%-6dis thinking\n", dinner_time, philo->id);
		pthread_mutex_unlock(&philo->shared->printf_mtx);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->shared->printf_mtx);
		return (0);
	}
}
