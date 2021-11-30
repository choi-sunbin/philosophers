/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:19:34 by gsmets            #+#    #+#             */
/*   Updated: 2021/11/30 18:30:02 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	philo_print(rules, philo->id, STR_FORK);
	pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
	philo_print(rules, philo->id, STR_FORK);
	pthread_mutex_lock(&(rules->meal_check));
	philo_print(rules, philo->id, STR_EAT);
	philo->t_last_meal = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	smart_sleep(rules->time_to_eat, rules);
	(philo->eaten_cnt)++;
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
	pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
}

void	*p_thread(void *void_philosopher)
{
	int				loop;
	t_philo			*philo;
	t_rules			*rules;

	loop = 0;
	philo = (t_philo *)void_philosopher;
	rules = philo->rules;
	if (philo->id % 2)
		usleep(15000);
	while (!(rules-> dieded))
	{
		philo_eats(philo);
		if (rules->finish_meal)
			break ;
		philo_print(rules, philo->id, STR_SLEEP);
		smart_sleep(rules->time_to_sleep, rules);
		philo_print(rules, philo->id, STR_THINK);
		loop++;
	}
	return (NULL);
}

void	exit_launcher(t_rules *rules, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < rules->num_of_philo)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < rules->num_of_philo)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->writing));
}

void	death_checker(t_rules *rule, t_philo *phi)
{
	int	lp;

	while (!(rule->finish_meal))
	{
		lp = -1;
		while (++lp < rule->num_of_philo && !(rule->dieded))
		{
			pthread_mutex_lock(&(rule->meal_check));
			if (time_diff(phi[lp].t_last_meal, timestamp()) > rule->time_to_die)
			{
				philo_print(rule, lp, STR_DIED);
				rule->dieded = 1;
			}
			pthread_mutex_unlock(&(rule->meal_check));
			usleep(100);
		}
		if (rule->dieded)
			break ;
		lp = 0;
		while (rule->must_eat_cnt != -1 && lp < rule->num_of_philo
			&& phi[lp].eaten_cnt >= rule->must_eat_cnt)
			lp++;
		if (lp == rule->num_of_philo)
			rule->finish_meal = 1;
	}
}

int	launcher(t_rules *rules)
{
	int		loop;
	t_philo	*philo;

	loop = 0;
	philo = rules->philos;
	rules->first_timestamp = timestamp();
	while (loop < rules->num_of_philo)
	{
		if (pthread_create(&(philo[loop].thread_id), NULL, \
			p_thread, &(philo[loop])))
			return (1);
		philo[loop].t_last_meal = timestamp();
		loop++;
	}
	death_checker(rules, rules->philos);
	exit_launcher(rules, philo);
	return (0);
}
