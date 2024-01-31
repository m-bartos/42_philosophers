/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:34:59 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 14:35:07 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_right_fork(t_philo *philo)
{
	int	in_loop;

	in_loop = 1;
	pthread_mutex_lock(&philo->shared->printf_mutex);
	while (in_loop == 1 && philo->shared->dinner_over == 0)
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		pthread_mutex_lock(&philo->shared->forks_mutexes[philo->id]);
		if (philo->shared->table_forks[philo->id] == 1)
		{
			philo->shared->table_forks[philo->id] = 0;
			philo->hold_right_fork = 1;
			pthread_mutex_lock(&philo->shared->printf_mutex);
			if (philo->shared->dinner_over == 0)
				printf("%-10ld%-6dhas taken a right fork\n", get_dinner_time(philo->shared->dinner_start_time), philo->id);
			pthread_mutex_unlock(&philo->shared->printf_mutex);
			in_loop = 0;
		}
		pthread_mutex_unlock(&philo->shared->forks_mutexes[philo->id]);
		pthread_mutex_lock(&philo->shared->printf_mutex);
	}
	pthread_mutex_unlock(&philo->shared->printf_mutex);
}

void	grab_left_fork(t_philo *philo)
{
	int	fork_index;
	int	in_loop;

	if (philo->id == (philo->shared->nof_philos - 1))
		fork_index = 0;
	else
		fork_index = philo->id + 1;
	in_loop = 1;
	pthread_mutex_lock(&philo->shared->printf_mutex);
	while (in_loop == 1 && philo->shared->dinner_over == 0)
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		pthread_mutex_lock(&philo->shared->forks_mutexes[fork_index]);
		if (philo->shared->table_forks[fork_index] == 1)
		{
			philo->shared->table_forks[fork_index] = 0;
			philo->hold_left_fork = 1;
			pthread_mutex_lock(&philo->shared->printf_mutex);
			if (philo->shared->dinner_over == 0)
				printf("%-10ld%-6dhas taken a left fork\n", get_dinner_time(philo->shared->dinner_start_time), philo->id);
			pthread_mutex_unlock(&philo->shared->printf_mutex);
			in_loop = 0;
		}
		pthread_mutex_unlock(&philo->shared->forks_mutexes[fork_index]);
		pthread_mutex_lock(&philo->shared->printf_mutex);
	}
	pthread_mutex_unlock(&philo->shared->printf_mutex);
}

void	sleep_ms(long period)
{
	long	init_time;

	init_time = get_actual_time_ms();
	while ((get_actual_time_ms() - init_time) < period)
		usleep(10);
}

void	put_both_forks_on_table(t_philo *philo)
{
	int	fork_index;

	pthread_mutex_lock(&philo->shared->forks_mutexes[philo->id]);
	philo->hold_right_fork = 0;
	philo->shared->table_forks[philo->id] = 1;
	pthread_mutex_unlock(&philo->shared->forks_mutexes[philo->id]);
	if (philo->id == (philo->shared->nof_philos - 1))
		fork_index = 0;
	else
		fork_index = philo->id + 1;
	pthread_mutex_lock(&philo->shared->forks_mutexes[fork_index]);
	philo->hold_left_fork = 0;
	philo->shared->table_forks[fork_index] = 1;
	pthread_mutex_unlock(&philo->shared->forks_mutexes[fork_index]);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->printf_mutex);
	if (philo->shared->dinner_over == 1)
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		return (0);
	}
	printf("%-10ld%-6dis eating\n", get_dinner_time(philo->shared->dinner_start_time), philo->id);
	pthread_mutex_unlock(&philo->shared->printf_mutex);
	pthread_mutex_lock(&philo->eating_start_time_mutex);
	philo->eating_start_time = get_actual_time_ms();
	pthread_mutex_unlock(&philo->eating_start_time_mutex);
	sleep_ms(philo->shared->init_time_to_eat);
	pthread_mutex_lock(&philo->nof_meals_mutex);
	philo->nof_meals++;
	pthread_mutex_unlock(&philo->nof_meals_mutex);
	return (1);
}

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

int	are_philos_dead(t_dinner *dinner)
{
	int	i;

	i = 0;
	while (i < dinner->shared->nof_philos)
	{
		pthread_mutex_lock(&dinner->philos_arr[i].eating_start_time_mutex);
		if (get_actual_time_ms() - dinner->philos_arr[i].eating_start_time > dinner->shared->init_time_to_die)
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

int	all_have_eaten(t_dinner *dinner)
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
			if (all_have_eaten(dinner) == 1)
				return (NULL);
		}
	}
}

//check for how many times each philo ate (add nof_eats to t_onephilo)

int	main(int argc, char **argv)
{
	t_dinner	dinner;
	t_shared	shared;
	int			i;


	check_args(argc, argv);
	init(argc, argv, &dinner, &shared);

	//printing struct for check
	ft_print_program_struct(&dinner);

	// playing with threads
	i = 0;
	while (i < dinner.shared->nof_philos)
	{
		pthread_mutex_init(&dinner.shared->forks_mutexes[i], NULL);
		pthread_mutex_init(&dinner.philos_arr[i].eating_start_time_mutex, NULL);
		pthread_mutex_init(&dinner.philos_arr[i].nof_meals_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&dinner.shared->printf_mutex, NULL);
	//time init
	//shared.dinner_start_time = get_actual_time_ms(); // no need
	i = 0;
	while (i < dinner.shared->nof_philos)
	{
		pthread_create(&dinner.philos_arr[i].thread, NULL, &routine, &dinner.philos_arr[i]);
		i++;
	}
	pthread_create(&dinner.watch_thread, NULL, &checking_philos, &dinner);
	i = 0;
	while (i < dinner.shared->nof_philos)
	{
		pthread_join(dinner.philos_arr[i].thread, NULL);
		i++;
	}
	pthread_join(dinner.watch_thread, NULL);
	i = 0;
	while (i < dinner.shared->nof_philos)
	{
		pthread_mutex_destroy(&shared.forks_mutexes[i]);
		pthread_mutex_destroy(&dinner.philos_arr[i].eating_start_time_mutex);
		pthread_mutex_destroy(&dinner.philos_arr[i].nof_meals_mutex);
		i++;
	}
	pthread_mutex_destroy(&dinner.shared->printf_mutex);
	free_t_program(&dinner);
	return (0);
}
