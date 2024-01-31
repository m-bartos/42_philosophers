/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:34:59 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 10:20:52 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_right_fork(t_onephilo *philo)
{
	int	in_loop;

	in_loop = 1;
	pthread_mutex_lock(&philo->shared->printf_mutex);
	while(in_loop == 1 && philo->shared->dinner_over == 0)
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		pthread_mutex_lock(&philo->shared->forks_mutexes[philo->id]);
		if (philo->shared->table_forks[philo->id] == 1)
		{
			philo->shared->table_forks[philo->id] = 0;
			philo->hold_right_fork = 1;
			pthread_mutex_lock(&philo->shared->printf_mutex);
			printf("%ld     %d   has taken a right fork\n", get_party_time(philo->shared->dinner_start_time), philo->id);
			pthread_mutex_unlock(&philo->shared->printf_mutex);
			in_loop = 0;
		}
		pthread_mutex_unlock(&philo->shared->forks_mutexes[philo->id]);
		pthread_mutex_lock(&philo->shared->printf_mutex);
	}
	pthread_mutex_unlock(&philo->shared->printf_mutex);
}

void	grab_left_fork(t_onephilo *philo)
{
	int	fork_index;
	int	in_loop;

	if (philo->id == (philo->shared->nof_philos - 1))
		fork_index = 0;
	else
		fork_index = philo->id + 1;
	in_loop = 1;
	pthread_mutex_lock(&philo->shared->printf_mutex);
	while(in_loop == 1 && philo->shared->dinner_over == 0)
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		pthread_mutex_lock(&philo->shared->forks_mutexes[fork_index]);
		if (philo->shared->table_forks[fork_index] == 1)
		{
			philo->shared->table_forks[fork_index] = 0;
			philo->hold_left_fork = 1;
			pthread_mutex_lock(&philo->shared->printf_mutex);
			printf("%ld     %d   has taken a left fork\n", get_party_time(philo->shared->dinner_start_time), philo->id);
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

void	put_both_forks_on_table(t_onephilo *philo)
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

int	eating(t_onephilo *philo)
{
	pthread_mutex_lock(&philo->shared->printf_mutex);
	if (philo->shared->dinner_over == 1)
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->shared->printf_mutex);
	pthread_mutex_lock(&philo->shared->printf_mutex);
	printf("%ld     %d   is eating\n", get_party_time(philo->shared->dinner_start_time), philo->id);
	pthread_mutex_unlock(&philo->shared->printf_mutex);
	pthread_mutex_lock(&philo->eating_start_time_mutex);
	philo->eating_start_time = get_actual_time_ms();
	pthread_mutex_unlock(&philo->eating_start_time_mutex);
	sleep_ms(philo->shared->init_time_to_eat);
	return (1);
}

int	sleeping(t_onephilo *philo)
{
	pthread_mutex_lock(&philo->shared->printf_mutex);
	if (philo->shared->dinner_over == 1)
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->shared->printf_mutex);
	pthread_mutex_lock(&philo->shared->printf_mutex);
	printf("%ld     %d   is sleeping\n", get_party_time(philo->shared->dinner_start_time), philo->id);
	pthread_mutex_unlock(&philo->shared->printf_mutex);
	sleep_ms(philo->shared->init_time_to_sleep);
	return (1);
}

int	thinking(t_onephilo *philo)
{
	pthread_mutex_lock(&philo->shared->printf_mutex);
	if (philo->shared->dinner_over == 1)
	{
		pthread_mutex_unlock(&philo->shared->printf_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->shared->printf_mutex);
	pthread_mutex_lock(&philo->shared->printf_mutex);
	printf("%ld     %d   is thinking\n", get_party_time(philo->shared->dinner_start_time), philo->id);
	pthread_mutex_unlock(&philo->shared->printf_mutex);
	return (1);
}

void	*routine(void *philo_void)
{
	t_onephilo *philo;

	philo = (t_onephilo *) philo_void;

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

void	*checking_philos(void *program_void)
{
	t_program	*program;
	int			i;

	program = (t_program *) program_void;

	i = 0;
	while (1)
	{
		while (i < program->shared->nof_philos)
		{
			pthread_mutex_lock(&program->philos_arr[i].eating_start_time_mutex);
			if (get_actual_time_ms() - program->philos_arr[i].eating_start_time > program->shared->init_time_to_die)
			{
					pthread_mutex_lock(&program->shared->printf_mutex);
					printf("%ld     %d    is dead\n", get_party_time(program->shared->dinner_start_time), program->philos_arr[i].id);
					program->shared->dinner_over = 1;
					pthread_mutex_unlock(&program->shared->printf_mutex);
					pthread_mutex_unlock(&program->philos_arr[i].eating_start_time_mutex);
					return (NULL);
			}
			pthread_mutex_unlock(&program->philos_arr[i].eating_start_time_mutex);
			i++;
		}
		i = 0;
	}
	return (NULL);
}

//check for how many times each philo ate (add nof_eats to t_onephilo)

int	main(int argc, char **argv)
{
	t_program		program;
	t_shared_info	shared;
	int				i;


	check_args(argc, argv);
	init(argc, argv, &program, &shared);

	//printing struct for check
	ft_print_program_struct(&program);

	// playing with threads
	i = 0;
	while (i < shared.nof_philos)
	{
		pthread_mutex_init(&shared.forks_mutexes[i], NULL);
		pthread_mutex_init(&program.philos_arr[i].eating_start_time_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&program.shared->printf_mutex, NULL);
	//time init
	shared.dinner_start_time = get_actual_time_ms(); // no need
	i = 0;
	while (i < shared.nof_philos)
	{
		pthread_create(&program.philos_arr[i].thread, NULL, &routine, &program.philos_arr[i]);
		i++;
	}
	pthread_create(&program.watch_thread, NULL, &checking_philos, &program);
	i = 0;
	while (i < shared.nof_philos)
	{
		pthread_join(program.philos_arr[i].thread, NULL);
		i++;
	}
	pthread_join(program.watch_thread, NULL);
	i = 0;
	while (i < shared.nof_philos)
	{
		pthread_mutex_destroy(&shared.forks_mutexes[i]);
		pthread_mutex_destroy(&program.philos_arr[i].eating_start_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&program.shared->printf_mutex);
	free_t_program(&program);
	return (0);
}
