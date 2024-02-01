/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:44:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/02/01 12:45:42 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_philos_dead(t_dinner *dinner)
{
	int		i;
	long	time;
	t_philo	*philo;

	i = 0;
	while (i < dinner->shared->nof_philos)
	{
		philo = &dinner->philos[i];
		pthread_mutex_lock(&philo->eating_start_time_mtx);
		if (get_time() - philo->eat_start_time > dinner->shared->time_die)
		{
			pthread_mutex_lock(&dinner->shared->printf_mtx);
			time = get_dinner_time(dinner->shared->dinner_start_time);
			printf("%-10ld%-6dis dead\n", time, dinner->philos[i].id + 1);
			dinner->shared->dinner_over = 1;
			pthread_mutex_unlock(&dinner->shared->printf_mtx);
			pthread_mutex_unlock(&philo->eating_start_time_mtx);
			return (1);
		}
		pthread_mutex_unlock(&philo->eating_start_time_mtx);
		i++;
	}
	return (0);
}

int	have_all_eaten(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->shared->nof_philos)
	{
		pthread_mutex_lock(&dinner->philos[i].nof_meals_mtx);
		if (dinner->philos[i].nof_meals < dinner->max_eat_rounds)
		{
			pthread_mutex_unlock(&dinner->philos[i].nof_meals_mtx);
			return (0);
		}
		pthread_mutex_unlock(&dinner->philos[i].nof_meals_mtx);
		i++;
	}
	pthread_mutex_lock(&dinner->shared->printf_mtx);
	dinner->shared->dinner_over = 1;
	pthread_mutex_unlock(&dinner->shared->printf_mtx);
	return (1);
}

void	*checking_philos(void *dinner_void)
{
	t_dinner	*dinner;

	dinner = (t_dinner *) dinner_void;
	while (1)
	{
		if (are_philos_dead(dinner) == 1)
			return (NULL);
		if (dinner->max_eat_rounds != -1)
		{
			if (have_all_eaten(dinner) == 1)
				return (NULL);
		}
	}
}
