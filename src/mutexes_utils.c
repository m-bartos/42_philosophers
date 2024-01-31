/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:50:20 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 14:51:02 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->shared->nof_philos)
	{
		pthread_mutex_init(&dinner->shared->forks_mutexes[i], NULL);
		pthread_mutex_init(&dinner->philos_arr[i].eating_start_time_mutex, NULL);
		pthread_mutex_init(&dinner->philos_arr[i].nof_meals_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&dinner->shared->printf_mutex, NULL);
}

void	destroy_mutexes(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->shared->nof_philos)
	{
		pthread_mutex_destroy(&dinner->shared->forks_mutexes[i]);
		pthread_mutex_destroy(&dinner->philos_arr[i].eating_start_time_mutex);
		pthread_mutex_destroy(&dinner->philos_arr[i].nof_meals_mutex);
		i++;
	}
	pthread_mutex_destroy(&dinner->shared->printf_mutex);
}
