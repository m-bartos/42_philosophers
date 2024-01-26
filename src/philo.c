/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:34:59 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/26 14:56:51 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_right_fork(t_program *program, int philo_index)
{
	if (program->forks[philo_index] == 1)
	{
		program->forks[philo_index] = 0;
		program->philos_arr[philo_index].right_fork = 1;
		printf("%d     %d has taken a right fork", program->time, philo_index);
	}
}

void	grab_left_fork(t_program *program, int philo_index)
{
	if (philo_index == program->nof_forks - 1)
	{
		if (program->forks[0] == 1)
		{
			program->forks[0] = 0;
			program->philos_arr[philo_index].left_fork = 1;
			printf("%d     %d has taken a left fork", program->time, philo_index);
		}
	}
	else
	{
		if (program->forks[philo_index + 1] == 1)
		{
			program->forks[philo_index + 1] = 0;
			program->philos_arr[philo_index].left_fork = 1;
			printf("%d     %d has taken a left fork", program->time, philo_index);
		}
	}
}

void *routine(void *program)
{
	t_program *program2;

	program2 = (t_program *) program;
	pthread_mutex_lock(&program2->mutex);
	printf("Test from thread!\n");
	pthread_mutex_unlock(&program2->mutex);
	return (NULL);
}

void	ft_print_program_struct(t_program *program)
{
	int i;

	printf("========= PROGRAM STRUCT =========\n");
	printf("Init time to die: %d\n", program->init_time_to_die);
	printf("Init time to eat: %d\n", program->init_time_to_eat);
	printf("Init time to sleep: %d\n", program->init_time_to_sleep);
	printf("Total num of forks(and philosophers): %d\n", program->nof_forks);
	printf("Actual time: %d\n", program->time);
	printf("MAX EAT ROUNDS: %d\n", program->max_eat_rounds);
	printf("\n");
	i = 0;
	while (i < program->nof_forks)
	{
		printf("========= Philosopher %d =========\n", i);
		printf("Fork %d on table: %d\n", i, program->forks[i]);
		printf("Philo %d - time to die: %d\n", i, program->philos_arr[i].time_to_die);
		printf("Philo %d - time to eat: %d\n", i, program->philos_arr[i].time_to_eat);
		printf("Philo %d - time to sleep: %d\n", i, program->philos_arr[i].time_to_sleep);
		printf("Philo %d - left fork in hand: %d\n", i, program->philos_arr[i].left_fork);
		printf("Philo %d - right fork in hand: %d\n", i, program->philos_arr[i].right_fork);
		printf("\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_onephilo	one_philo[5];
	t_program	program;
	int			i;

	check_args(argc, argv);
	init(argc, argv, &program);
	//printing struct for check
	ft_print_program_struct(&program);

	// playing with threads
	pthread_mutex_init(&program.mutex, NULL);
	i = 0;
	while (i < program.nof_forks)
	{
		pthread_create(&one_philo[i].thread, NULL, &routine, &program);
		i++;
	}
	i = 0;
	while (i < program.nof_forks)
	{
		pthread_join(one_philo[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&program.mutex);
	free_t_program(&program);
	return (0);
}
