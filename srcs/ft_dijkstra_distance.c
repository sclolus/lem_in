/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dijkstra_distance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 16:04:23 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/09 06:34:58 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void			ft_make_graph_heap(t_heap *graph_heap
											, t_room *start
											, t_lem_in_data *lem_in_data)
{
	t_mem_block	*tmp;
	uint64_t	i;

	tmp = lem_in_data->data;
	i = 0;
	((t_room**)graph_heap->buffer)[graph_heap->i++] = start;
	start->heap_index = 1;
	start->distance = 0;
	while (i * sizeof(t_room) < tmp->offset)
	{
		if (((t_room*)tmp->block + i)->attribute != START)
		{
			((t_room**)graph_heap->buffer)[graph_heap->i] = ((t_room*)tmp->block
														+ i);
			((t_room*)tmp->block + i)->heap_index = graph_heap->i++;
		}
		i++;
		if (i * sizeof(t_room) >= tmp->offset && tmp->next && !(i = 0))
			tmp = tmp->next;
	}
}

static inline void			ft_update_neighbour_distances(t_heap *heap
														, t_room *room)
{
	t_mem_block	*tmp;
	uint64_t	i;
	uint64_t	distance;

	if (!(tmp = room->tubes))
		return ;
	i = 0;
	while (i * sizeof(t_room*) < tmp->offset)
	{
		distance = room->distance + ft_distance(room->coords.x
	, (*((t_room**)tmp->block + i))->coords.x) + ft_distance(room->coords.y
	, (*((t_room**)tmp->block + i))->coords.y);
		if (!(*((t_room**)tmp->block + i))->used && distance
			< (*((t_room**)tmp->block + i))->distance)
		{
			(*((t_room**)tmp->block + i))->distance = distance;
			(*((t_room**)tmp->block + i))->shortest = room;
			ft_min_heap_percolate_up(heap, (*((t_room**)tmp->block
											+ i))->heap_index);
		}
		i++;
		if (i * sizeof(t_room*) >= tmp->offset && tmp->next && !(i = 0))
			tmp = tmp->next;
	}
}

NORETURN					ft_dijkstra_distance(t_lem_in_data *lem_in_data)
{
	t_heap			*graph_heap;
	t_room			*start;
	t_room			*tmp;

	graph_heap = ft_create_heap(sizeof(t_room*), lem_in_data->room_nbr);
	start = lem_in_data->start;
	ft_make_graph_heap(graph_heap, start, lem_in_data);
	while (graph_heap->i > 1)
	{
		tmp = ((t_room**)graph_heap->buffer)[1];
		ft_min_heap_remove_elem(graph_heap);
		tmp->used = 1;
		ft_update_neighbour_distances(graph_heap, tmp);
	}
	ft_free_heap(graph_heap);
	ft_put_solution(lem_in_data);
}
