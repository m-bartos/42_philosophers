/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:06:28 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 16:57:49 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_ms(long period)
{
	long	init_time;

	init_time = get_time();
	while ((get_time() - init_time) < period)
		usleep(10);
}

long int	get_time(void)
{
	struct timeval	time;
	long			time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = (long)(time.tv_sec * 1000 + time.tv_usec / 1000);
	return (time_in_ms);
}

long int	get_dinner_time(long time)
{
	long	party_time;

	party_time = (get_time() - time);
	return (party_time);
}
