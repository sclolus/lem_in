/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_lem_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 23:12:03 by sclolus           #+#    #+#             */
/*   Updated: 2017/07/26 19:09:16 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline uint32_t	ft_atoi_unsigned(const char *str)
{
	uint32_t	nbr;

	nbr = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\v' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
		nbr = nbr * 10 + (uint32_t)*str++ - '0';
	return (nbr);
}

int32_t					ft_get_lem_nbr(char *line, t_lem_in_data *lem_in_data)
{
	uint32_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("0123456789", line[i]))
			return (0);
		i++;
	}
	lem_in_data->lem_nbr = ft_atoi_unsigned(line);
	return (1);
}
