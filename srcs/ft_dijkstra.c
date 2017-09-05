/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dijkstra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 21:19:38 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/05 09:35:33 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline void	ft_make_graph_heap(t_heap *graph_heap, t_room *start
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
		if (((t_room*)tmp->block + i) != start)
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

static inline void	ft_update_neighbour_distances(t_heap *heap, t_room *room)
{
	t_mem_block	*tmp;
	uint64_t	i;
	uint64_t	distance;

	if (!(tmp = room->tubes))
		return ;
	i = 0;
	distance = room->distance + 1;
	while (i * sizeof(t_room*) < tmp->offset)
	{
		if (!(*((t_room**)tmp->block + i))->used
			&& distance < (*((t_room**)tmp->block + i))->distance)
		{
			(*((t_room**)tmp->block + i))->distance = distance;
			(*((t_room**)tmp->block + i))->shortest = room;
			ft_min_heap_percolate_up(heap, (*((t_room**)tmp->block + i))->heap_index);
		}
		i++;
		if (i * sizeof(t_room*) >= tmp->offset && tmp->next && !(i = 0))
			tmp = tmp->next;
	}
}


static void	ft_swap_target(t_lem_in_data *lem_in_data)
{
	t_room	*tmp;
	lem_in_data->start->attribute = END;
	lem_in_data->end->attribute = START;
	tmp = lem_in_data->end;
	lem_in_data->end = lem_in_data->start;
	lem_in_data->start = tmp;
}

void		ft_dijkstra(t_lem_in_data *lem_in_data, t_room *start)
{
	t_heap			*graph_heap;
	t_room			*tmp;

	graph_heap = ft_create_heap(sizeof(t_room*), lem_in_data->room_nbr);
	(void)ft_swap_target;
	ft_make_graph_heap(graph_heap, start, lem_in_data);
	while (graph_heap->i > 1)
	{
		tmp = ((t_room**)graph_heap->buffer)[1];
		ft_min_heap_remove_elem(graph_heap);
		tmp->used = 1;
		ft_update_neighbour_distances(graph_heap, tmp);
	}
	ft_free_heap(graph_heap);
}
