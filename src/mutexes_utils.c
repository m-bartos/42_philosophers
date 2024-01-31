/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:50:20 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 16:57:16 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->shared->nof_philos)
	{
		pthread_mutex_init(&dinner->shared->forks_mtxs[i], NULL);
		pthread_mutex_init(&dinner->philos[i].eating_start_time_mtx, NULL);
		pthread_mutex_init(&dinner->philos[i].nof_meals_mtx, NULL);
		i++;
	}
	pthread_mutex_init(&dinner->shared->printf_mtx, NULL);
}

void	destroy_mutexes(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->shared->nof_philos)
	{
		pthread_mutex_destroy(&dinner->shared->forks_mtxs[i]);
		pthread_mutex_destroy(&dinner->philos[i].eating_start_time_mtx);
		pthread_mutex_destroy(&dinner->philos[i].nof_meals_mtx);
		i++;
	}
	pthread_mutex_destroy(&dinner->shared->printf_mtx);
}
