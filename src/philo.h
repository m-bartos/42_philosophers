/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:44:43 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/26 15:30:28 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct onephilo
{
	pthread_t		thread;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				hold_left_fork;
	int				hold_right_fork;
	int				fork_on_table;
	pthread_mutex_t	fork_mutex;
}		t_onephilo;

typedef struct program
{
	int				nof_philos;
	t_onephilo		*philos_arr;
	int				init_time_to_die;
	int				init_time_to_eat;
	int				init_time_to_sleep;
	pthread_mutex_t	printf_mutex;
	int				time;
	int				max_eat_rounds;
}		t_program;

// check_args.c
void	check_args(int argc, char **argv);

// init.c
void	free_t_program(t_program *program);
void	init(int argc, char **argv, t_program *program);

// libft_funcs.c
int		ft_int_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);

// philo_utils.c
void	ft_print_program_struct(t_program *program);

#endif
