/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_lem_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 23:12:03 by sclolus           #+#    #+#             */
/*   Updated: 2017/07/25 23:13:44 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int32_t	ft_get_lem_nbr(char *line, t_lem_in_data *lem_in_data)
{
	uint32_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("0123456789", line[i]))
			return (0);
		i++;
	}
	lem_in_data->lem_nbr = (uint32_t)ft_atoi(line); // uint32_t ?
	return (1); // (uint32_t) ?
}
