/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:05:24 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 16:57:49 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_t_program(t_dinner *program)
{
	free(program->philos);
	free(program->shared->forks_mtxs);
	free(program->shared->table_forks);
}

void	init_one_philo(t_philo *philo, t_shared *shared, int id)
{
	philo->id = id;
	philo->eat_start_time = get_time();
	philo->hold_left_fork = 0;
	philo->hold_right_fork = 0;
	philo->nof_meals = 0;
	philo->shared = shared;
}

void	add_max_eat_rounds(char	*str_max_eat_rounds, t_dinner *program)
{
	program->max_eat_rounds = ft_int_atoi(str_max_eat_rounds);
}
