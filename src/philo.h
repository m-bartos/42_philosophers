/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartos <mbartos@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:44:43 by mbartos           #+#    #+#             */
/*   Updated: 2024/01/31 16:57:49 by mbartos          ###   ########.fr       */
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

typedef struct s_shared
{
	int				*table_forks;
	pthread_mutex_t	*forks_mtxs;
	pthread_mutex_t	printf_mtx;
	long			dinner_start_time;
	int				nof_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				dinner_over;
}		t_shared;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			eat_start_time;
	pthread_mutex_t	eating_start_time_mtx;
	int				hold_left_fork;
	int				hold_right_fork;
	int				nof_meals;
	pthread_mutex_t	nof_meals_mtx;
	t_shared		*shared;
}		t_philo;

typedef struct s_dinner
{
	t_philo		*philos;
	t_shared	*shared;
	pthread_t	checker_thread;
	int			max_eat_rounds;
}		t_dinner;

// check_args.c
void		check_args(int argc, char **argv);

// checker_thread.c
int			are_philos_dead(t_dinner *dinner);
int			have_all_eaten(t_dinner *dinner);
void		*checking_philos(void *dinner_void);

// eating.c
void		grab_right_fork(t_philo *philo);
void		grab_left_fork(t_philo *philo);
void		put_both_forks_on_table(t_philo *philo);
int			eating(t_philo *philo);

// init_utils.c
void		free_t_program(t_dinner *program);
void		init_one_philo(t_philo *philo, t_shared *shared, int id);
void		add_max_eat_rounds(char	*str_max_eat_rounds, t_dinner *program);

// init.c
void		free_t_program(t_dinner *program);
void		init(int argc, char **argv, t_dinner *program, t_shared *mutexes);
long int	get_time(void);
long int	get_dinner_time(long time);

// libft_funcs.c
int			ft_int_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);

// philo_utils.c
void		ft_print_program_struct(t_dinner *program);

// mutexes_utils.c
void		init_mutexes(t_dinner *dinner);
void		destroy_mutexes(t_dinner *dinner);

// sleeping_thinking.c
int			sleeping(t_philo *philo);
int			thinking(t_philo *philo);

// time.c
void		sleep_ms(long period);
long int	get_time(void);
long int	get_dinner_time(long time);

#endif
