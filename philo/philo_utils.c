/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:59:27 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 16:57:16 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_program_struct(t_dinner *program)
{
	int	i;

	printf("========= PROGRAM STRUCT =========\n");
	printf("Init time to die: %ld\n", program->shared->time_die);
	printf("Init time to eat: %ld\n", program->shared->time_eat);
	printf("Init time to sleep: %ld\n", program->shared->time_sleep);
	printf("Total num of forks(and philosophers): %d\n", program->shared->nof_philos);
	printf("Start time: %ld\n", program->shared->dinner_start_time);
	printf("MAX EAT ROUNDS: %d\n", program->max_eat_rounds);
	printf("\n");
	i = 0;
	while (i < program->shared->nof_philos)
	{
		printf("========= Philosopher %d =========\n", i);
		printf("Fork %d on table: %d\n", i, program->shared->table_forks[i]);
		printf("Philo %d - left fork in hand: %d\n", i, program->philos[i].hold_left_fork);
		printf("Philo %d - right fork in hand: %d\n", i, program->philos[i].hold_right_fork);
		printf("\n");
		i++;
	}
}
