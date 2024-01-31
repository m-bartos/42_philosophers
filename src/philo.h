/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:44:43 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 10:02:41 by mbartos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_shared_info
{
	int				*table_forks;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	printf_mutex;
	long			time;
	int				nof_philos;
	long			init_time_to_die;
	long			init_time_to_eat;
	long			init_time_to_sleep;
	int				game_over;
}		t_shared_info;

typedef struct s_onephilo
{
	int				id;
	pthread_t		thread;
	long			start_of_eating;
	pthread_mutex_t	start_of_eating_mutex;
	int				hold_left_fork;
	int				hold_right_fork;
	t_shared_info	*shared;
}		t_onephilo;

typedef struct s_program
{
	t_onephilo		*philos_arr;
	t_shared_info	*shared;
	pthread_t		watch_thread;
	int				max_eat_rounds;
}		t_program;

// check_args.c
void	check_args(int argc, char **argv);

// init.c
void		free_t_program(t_program *program);
void		init(int argc, char **argv, t_program *program, t_shared_info *mutexes);
long int	get_actual_time_ms(void);
long int	get_party_time(long time);

// libft_funcs.c
int		ft_int_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);

// philo_utils.c
void	ft_print_program_struct(t_program *program);

#endif
