/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:34:59 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 17:24:58 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_philo *philo)
{
	if (philo->id % 2)
		take_right_fork(philo);
	else
		take_left_fork(philo);
	if (philo->hold_left_fork == 1)
		take_right_fork(philo);
	else if (philo->hold_right_fork == 1)
		take_left_fork(philo);
}

void	*routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *) philo_void;
	pthread_mutex_lock(&philo->shared->printf_mtx);
	while (philo->shared->dinner_over == 0)
	{
		pthread_mutex_unlock(&philo->shared->printf_mtx);
		grab_forks(philo);
		if (eating(philo) == 0)
			return (NULL);
		put_both_forks_on_table(philo);
		if (sleeping(philo) == 0)
			return (NULL);
		if (thinking(philo) == 0)
			return (NULL);
		pthread_mutex_lock(&philo->shared->printf_mtx);
	}
	pthread_mutex_unlock(&philo->shared->printf_mtx);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;
	t_shared	shared;
	t_philo		*philo;
	int			i;

	check_args(argc, argv);
	init(argc, argv, &dinner, &shared);
	init_mutexes(&dinner);
	shared.dinner_start_time = get_time();
	i = 0;
	while (i < dinner.shared->nof_philos)
	{
		philo = &dinner.philos[i];
		pthread_create(&philo->thread, NULL, &routine, philo);
		i++;
	}
	pthread_create(&dinner.checker_thread, NULL, &checking_philos, &dinner);
	i = 0;
	while (i < dinner.shared->nof_philos)
		pthread_join(dinner.philos[i++].thread, NULL);
	pthread_join(dinner.checker_thread, NULL);
	destroy_mutexes(&dinner);
	free_t_program(&dinner);
	return (0);
}
