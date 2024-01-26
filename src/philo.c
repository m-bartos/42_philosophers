/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:34:59 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/26 15:47:36 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_right_fork(t_program *program, int philo_index)
{
	pthread_mutex_lock(&program->philos_arr[philo_index].fork_mutex);
	if (program->philos_arr[philo_index].fork_on_table == 1)
	{
		program->philos_arr[philo_index].fork_on_table = 0;
		program->philos_arr[philo_index].hold_right_fork = 1;
		pthread_mutex_lock(&program->printf_mutex);
		printf("%d     %d has taken a right fork\n", program->time, philo_index);
		pthread_mutex_unlock(&program->printf_mutex);
	}
	pthread_mutex_unlock(&program->philos_arr[philo_index].fork_mutex);
}

void	grab_left_fork(t_program *program, int philo_index)
{
	int	fork_index;

	if (philo_index == (program->nof_philos - 1))
		fork_index = 0;
	else
		fork_index = philo_index + 1;
	pthread_mutex_lock(&program->philos_arr[fork_index].fork_mutex);
	if (program->philos_arr[fork_index].fork_on_table == 1)
	{
		program->philos_arr[fork_index].fork_on_table = 0;
		program->philos_arr[philo_index].hold_left_fork = 1;
		pthread_mutex_lock(&program->printf_mutex);
		printf("%d     %d has taken a left fork\n", program->time, philo_index);
		pthread_mutex_unlock(&program->printf_mutex);
	}
	pthread_mutex_unlock(&program->philos_arr[fork_index].fork_mutex);
}

void	*routine(void *program)
{
	t_program *program2;

	program2 = (t_program *) program;
	pthread_mutex_lock(&program2->printf_mutex);
	printf("Test from thread!\n");
	pthread_mutex_unlock(&program2->printf_mutex);
	grab_left_fork(program2, 1);
	grab_right_fork(program2, 1);
	grab_left_fork(program2, 0);
	grab_right_fork(program2, 0);
	return (NULL);
}

//check for how many times each philo ate (add nof_eats to t_onephilo)

int	main(int argc, char **argv)
{
	t_program	program;
	int			i;

	check_args(argc, argv);
	init(argc, argv, &program);
	//printing struct for check
	ft_print_program_struct(&program);

	// playing with threads
	pthread_mutex_init(&program.printf_mutex, NULL);
	i = 0;
	while (i < program.nof_philos)
	{
		pthread_create(&program.philos_arr[i].thread, NULL, &routine, &program);
		i++;
	}
	i = 0;
	while (i < program.nof_philos)
	{
		pthread_join(program.philos_arr[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&program.printf_mutex);
	free_t_program(&program);
	return (0);
}
