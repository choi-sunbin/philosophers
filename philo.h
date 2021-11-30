/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:11:53 by sunbchoi          #+#    #+#             */
/*   Updated: 2021/11/30 18:11:55 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

# define ERROR -1
# define TRUE 1
# define FAIL 0

# define ERR_INIT_DATA 1
# define ERR_INIT_MUTEX 2

# define STR_FORK "has taken a fork"
# define STR_EAT "is eating"
# define STR_SLEEP "is sleeping"
# define STR_THINK "is thinking"
# define STR_DIED "died"
# define STR_ERR_ARG_CNT "Wrong amount of arguments"
# define STR_ERR_THR_FAIL "There was an error creating the threads"
# define STR_ERR_WRONG_ARG "At least one wrong argument"
# define STR_ERR_MUTEX "Fatal error when intializing mutex"

struct	s_rules;

typedef struct s_philo
{
	int					id;
	int					eaten_cnt;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_rules		*rules;
	pthread_t			thread_id;
}	t_philo;

typedef struct s_rules
{
	int					num_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat_cnt;
	int					dieded;
	int					finish_meal;
	long long			first_timestamp;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		writing;
	t_philo				philos[250];
}	t_rules;

/*
** ----- error_manager.c -----
*/

int						write_error(char *str);
int						error_manager(int error);

/*
** ----- init.c -----
*/

int						init_all(t_rules *rules, char **argv);

/*
** ----- utils.c -----
*/

int						ft_atoi(const char *str);
void					philo_print(t_rules *rules, int id, char *string);
long long				timestamp(void);
long long				time_diff(long long past, long long pres);
void					smart_sleep(long long time, t_rules *rules);

/*
** ----- launcher.c -----
*/

int						launcher(t_rules *rules);
void					exit_launcher(t_rules *rules, t_philo *philos);

/*
** checker.c
*/
void	death_checker(t_rules *rule, t_philo *philo);
#endif
