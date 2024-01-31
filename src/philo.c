/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:34:59 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 16:07:10 by mbartos          ###   ########.fr       */
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

void	*routine(void *philo_void)
{
	t_philo	*philo;

	philo = (t_philo *) philo_void;
	pthread_mutex_lock(&philo->shared->printf_mutex);
	while (philo->shared->dinner_over == 0)
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		if (philo->id % 2)
			grab_right_fork(philo);
		else
			grab_left_fork(philo);
		if (philo->hold_left_fork == 1)
			grab_right_fork(philo);
		else if (philo->hold_right_fork == 1)
			grab_left_fork(philo);
		if (philo->hold_right_fork == 1 && philo->hold_left_fork == 1)
		{
			if (eating(philo) == 0)
				return (NULL);
			put_both_forks_on_table(philo);
		}
		if (sleeping(philo) == 0)
			return (NULL);
		if (thinking(philo) == 0)
			return (NULL);
		pthread_mutex_lock(&philo->shared->printf_mutex);
	}
	pthread_mutex_unlock(&philo->shared->printf_mutex);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_dinner	dinner;
	t_shared	shared;
	int			i;

	check_args(argc, argv);
	init(argc, argv, &dinner, &shared);
	// ft_print_program_struct(&dinner);
	init_mutexes(&dinner);
	i = 0;
	while (i < dinner.shared->nof_philos)
	{
		pthread_create(&dinner.philos_arr[i].thread, NULL, &routine, &dinner.philos_arr[i]);
		i++;
	}
	pthread_create(&dinner.checker_thread, NULL, &checking_philos, &dinner);
	i = 0;
	while (i < dinner.shared->nof_philos)
		pthread_join(dinner.philos_arr[i++].thread, NULL);
	pthread_join(dinner.checker_thread, NULL);
	destroy_mutexes(&dinner);
	free_t_program(&dinner);
	return (0);
}
