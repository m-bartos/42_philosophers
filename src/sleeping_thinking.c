/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping_thinking.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:19:56 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 16:20:17 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->printf_mutex);
	if (philo->shared->dinner_over == 0)
	{
		printf("%-10ld%-6dis sleeping\n", get_dinner_time(philo->shared->dinner_start_time), philo->id);
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		sleep_ms(philo->shared->init_time_to_sleep);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		return (0);
	}
}

int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->printf_mutex);
	if (philo->shared->dinner_over == 0)
	{
		printf("%-10ld%-6dis thinking\n", get_dinner_time(philo->shared->dinner_start_time), philo->id);
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		return (0);
	}
}
