/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:47:47 by gsmets            #+#    #+#             */
/*   Updated: 2021/11/30 18:14:20 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_rules *rules)
{
	int	loop;

	loop = 0;
	while (loop < rules->num_of_philo)
	{
		if (pthread_mutex_init(&(rules->forks[loop]), NULL))
			return (ERROR);
		loop++;
	}
	if (pthread_mutex_init(&(rules->writing), NULL))
		return (ERROR);
	if (pthread_mutex_init(&(rules->meal_check), NULL))
		return (ERROR);
	return (0);
}

int	init_philo(t_rules *rules)
{
	int	loop;

	loop = 0;
	while (loop < rules->num_of_philo)
	{
		rules->philos[loop].id = loop;
		rules->philos[loop].eaten_cnt = 0;
		rules->philos[loop].left_fork_id = loop;
		rules->philos[loop].right_fork_id = (loop + 1) % rules->num_of_philo;
		rules->philos[loop].t_last_meal = 0;
		rules->philos[loop].rules = rules;
		loop++;
	}
	return (0);
}

int	init_all(t_rules *rules, char **argv)
{
	rules->num_of_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->finish_meal = 0;
	rules->dieded = 0;
	if (rules->num_of_philo < 2 || rules->time_to_die < 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0
		|| rules->num_of_philo > 250)
		return (ERR_INIT_DATA);
	if (argv[5])
	{
		rules->must_eat_cnt = ft_atoi(argv[5]);
		if (rules->must_eat_cnt <= 0)
			return (ERR_INIT_DATA);
	}
	else
		rules->must_eat_cnt = -1;
	if (init_mutex(rules))
		return (ERR_INIT_MUTEX);
	init_philo(rules);
	return (0);
}
