/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_new_room.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 14:11:31 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/09 05:09:37 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline static int32_t	ft_get_room_coords(char *line, t_coord *coords)
{
	uint32_t	i;
	uint32_t	nbr_coords;

	i = 0;
	nbr_coords = 0;
	while (line[i])
	{
		while (ft_strchr(CHARSET_WHITESPACE, line[i]))
			i++;
		if (!ft_strchr(DECIMAL_SET, line[i]))
			return (0);
		else
			nbr_coords++;
		if (nbr_coords == 1)
			coords->x = (uint32_t)ft_atoi(line + i);
		else if (nbr_coords == 2)
			coords->y = (uint32_t)ft_atoi(line + i);
		else
			return (0);
		while (ft_strchr(DECIMAL_SET, line[i]) && line[i])
			i++;
	}
	return (1);
}

static inline void		ft_new_room_attr_actions(t_lem_in_data *lem_in_data
												, t_room *room
												, t_attribute *last_attr)
{
	if (*last_attr == START)
	{
		lem_in_data->start = room;
		room->flow.capacity = ~0U;
		ft_get_set_states()[0] = 1;
	}
	else if (*last_attr == END)
	{
		room->flow.capacity = ~0U;
		lem_in_data->end = room;
		ft_get_set_states()[1] = 1;
	}
	else if (*last_attr == CAPACITY)
		room->flow.capacity = *ft_get_last_modified_capacity();
	*last_attr = NORMAL;
}

int32_t					ft_get_new_room(char *line, t_lem_in_data *lem_in_data)
{
	t_room		*room;
	uint32_t	i;
	t_coord		coords;
	t_attribute	*last_attr;
	char		*name;

	i = 0;
	last_attr = ft_get_last_attribute();
	while (line[i] && line[i] != ' ')
		i++;
	if (line[0] == 'L')
		return (0);
	if (!(name = ft_strndup(line, i)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	if (!(ft_get_room_coords(line + i, &coords)))
		return (0);
	room = ft_mem_block_push_back_elem(lem_in_data->data, &(t_room){name, i, {1
	, 0}, 0, coords, ~0UL, *last_attr, 0
	, ft_create_mem_block(DEFAULT_MEM_BLOCK_TUBE_SIZE), NULL, 0}
	, sizeof(t_room));
	ft_new_room_attr_actions(lem_in_data, room, last_attr);
	lem_in_data->room_nbr++;
	return (1);
}
