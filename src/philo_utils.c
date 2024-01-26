/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:59:27 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/26 15:26:42 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_program_struct(t_program *program)
{
	int i;

	printf("========= PROGRAM STRUCT =========\n");
	printf("Init time to die: %d\n", program->init_time_to_die);
	printf("Init time to eat: %d\n", program->init_time_to_eat);
	printf("Init time to sleep: %d\n", program->init_time_to_sleep);
	printf("Total num of forks(and philosophers): %d\n", program->nof_philos);
	printf("Actual time: %d\n", program->time);
	printf("MAX EAT ROUNDS: %d\n", program->max_eat_rounds);
	printf("\n");
	i = 0;
	while (i < program->nof_philos)
	{
		printf("========= Philosopher %d =========\n", i);
		printf("Fork %d on table: %d\n", i, program->philos_arr->fork_on_table);
		printf("Philo %d - time to die: %d\n", i, program->philos_arr[i].time_to_die);
		printf("Philo %d - time to eat: %d\n", i, program->philos_arr[i].time_to_eat);
		printf("Philo %d - time to sleep: %d\n", i, program->philos_arr[i].time_to_sleep);
		printf("Philo %d - left fork in hand: %d\n", i, program->philos_arr[i].hold_left_fork);
		printf("Philo %d - right fork in hand: %d\n", i, program->philos_arr[i].hold_right_fork);
		printf("\n");
		i++;
	}
}