/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:44:33 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/24 16:04:56 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *mutex)
{
	pthread_mutex_lock(mutex);
	ft_printf("Test from thread!\n");
	pthread_mutex_unlock(mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t		t1[50];
	int				i;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 50)
	{
		pthread_create(&t1[i], NULL, &routine, &mutex);
		i++;
	}
	i = 0;
	while (i < 50)
	{
		pthread_join(t1[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
