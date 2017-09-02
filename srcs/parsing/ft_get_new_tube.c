/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_new_tube.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 05:13:25 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/02 11:43:59 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline static t_room	*ft_find_room(char *name
									, t_mem_block *data)
{
	uint32_t	i;

	i = 0;
	while (i * sizeof(t_room) < data->offset)
	{
		if (ft_strequ(name, ((t_room*)data->block + i)->name))
			return (((t_room*)data->block + i));
		i++;
		if (i * sizeof(t_room) >= data->offset && data->next)
		{
			i = 0;
			data = data->next;
		}
	}
	return (NULL);
}

inline static void		ft_add_new_tube(t_room *room1, t_room *room2)
{
	ft_mem_block_push_back_elem(room1->tubes, &room2, sizeof(t_room *));
	room1->nbr_tube++;
	ft_mem_block_push_back_elem(room2->tubes, &room1, sizeof(t_room *));
	room2->nbr_tube++;
}

inline static uint32_t	ft_get_new_tube_name_len(char *line)
{
	uint32_t	i;

	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	return (i);
}
#include <stdio.h>
int32_t					ft_get_new_tube(char *line, t_lem_in_data *lem_in_data)
{
	t_room		*tab[2];
	uint32_t	len;

	len = ft_get_new_tube_name_len(line);
	line[len] = '\0';
	if (!(tab[0] = ft_find_room(line, lem_in_data->data)))
		return (0);
	line[len] = '-';
	line += len + 1;
	len = ft_get_new_tube_name_len(line);
	line[len] = '\0';
	if (!(tab[1] = ft_find_room(line, lem_in_data->data)))
		return (0);
	ft_add_new_tube(tab[0], tab[1]);
	return (1);
}
