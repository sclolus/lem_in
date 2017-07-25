/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_new_tube.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 05:13:25 by sclolus           #+#    #+#             */
/*   Updated: 2017/07/25 18:20:06 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*ft_find_room(char *name, uint32_t len, t_mem_block *data)
{
	uint32_t	i;

	i = 0;
	while (i * sizeof(t_room) < data->offset)
	{
		if (ft_strnequ(name, ((t_room*)data->block + i)->name, len))
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

static void		ft_add_new_tube(t_room *room1, t_room *room2)
{
	ft_mem_block_push_back_elem(room1->tubes, &room2, sizeof(t_room *));
//	printf("added a tube: %s to room: %s, new_offset: %llu\n", room2->name, room1->name, room1->tubes->offset);
	room1->nbr_tube++;
	ft_mem_block_push_back_elem(room2->tubes, &room1, sizeof(t_room *));
//	printf("added a tube: %s to room: %s, new_offset: %llu\n", room1->name, room2->name, room2->tubes->offset);
	room2->nbr_tube++;
}

static uint32_t	ft_get_new_tube_name_len(char *line)
{
	uint32_t	i;

	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	return (i);
}

int32_t			ft_get_new_tube(char *line, t_lem_in_data *lem_in_data)
{
	t_room		*tab[2];
	uint32_t	len;

	len = ft_get_new_tube_name_len(line);
	if (!(tab[0] = ft_find_room(line, len, lem_in_data->data)))
		return (0);
	line += len + 1;
	len = ft_get_new_tube_name_len(line);
	if (!(tab[1] = ft_find_room(line, len, lem_in_data->data)))
		return (0);
	ft_add_new_tube(tab[0], tab[1]);
	return (1);
}
