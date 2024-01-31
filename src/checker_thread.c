/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:44:37 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 16:12:50 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_philos_dead(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->shared->nof_philos)
	{
		pthread_mutex_lock(&dinner->philos_arr[i].eating_start_time_mutex);
		if (get_actual_time() - dinner->philos_arr[i].eating_start_time > dinner->shared->init_time_to_die)
		{
			pthread_mutex_lock(&dinner->shared->printf_mutex);
			printf("%-10ld%-6dis dead\n", get_dinner_time(dinner->shared->dinner_start_time), dinner->philos_arr[i].id);
			dinner->shared->dinner_over = 1;
			pthread_mutex_unlock(&dinner->shared->printf_mutex);
			pthread_mutex_unlock(&dinner->philos_arr[i].eating_start_time_mutex);
			return (1);
		}
		pthread_mutex_unlock(&dinner->philos_arr[i].eating_start_time_mutex);
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
		pthread_mutex_lock(&dinner->philos_arr[i].nof_meals_mutex);
		if (dinner->philos_arr[i].nof_meals < dinner->max_eat_rounds)
		{
			pthread_mutex_unlock(&dinner->philos_arr[i].nof_meals_mutex);
			return (0);
		}
		pthread_mutex_unlock(&dinner->philos_arr[i].nof_meals_mutex);
		i++;
	}
	pthread_mutex_lock(&dinner->shared->printf_mutex);
	printf("%-10ldall   philos have eaten at least %d time\n", get_dinner_time(dinner->shared->dinner_start_time), dinner->max_eat_rounds);
	dinner->shared->dinner_over = 1;
	pthread_mutex_unlock(&dinner->shared->printf_mutex);
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
