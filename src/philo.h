/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:44:43 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/26 11:55:20 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../lib/libft/libft.h"
# include <pthread.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct onephilo
{
	pthread_t	thread;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			left_fork;
	int			right_fork;
}		t_onephilo;

typedef struct program
{
	t_onephilo		*philos_arr;
	int				init_time_to_die;
	int				init_time_to_eat;
	int				init_time_to_sleep;
	pthread_mutex_t	mutex;
	int				nof_forks;
	int				*forks;
	int				time;
	int				max_eat_rounds;
}		t_program;

// check_args.c
void	check_args(int argc, char **argv);

// init.c
void	free_t_program(t_program *program);
void	init(int argc, char **argv, t_program *program);

#endif
