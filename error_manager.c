/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunbchoi <sunbchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:31:56 by gsmets            #+#    #+#             */
/*   Updated: 2021/11/30 18:37:52 by sunbchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	write_error(char *str)
{
	printf("\x1b[31mError: %s\n", str);
	return (1);
}

int	error_manager(int error)
{
	if (error == ERR_INIT_DATA)
		return (write_error(STR_ERR_WRONG_ARG));
	if (error == ERR_INIT_MUTEX)
		return (write_error(STR_ERR_MUTEX));
	return (1);
}
