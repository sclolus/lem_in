/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dijkstra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 21:19:38 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/01 12:28:49 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
# include <stdio.h> //


inline static t_room		*ft_get_start_room(t_lem_in_data *lem_in_data)
{
	t_mem_block	*data;
	uint32_t	i;

	i = 0;
	data = lem_in_data->data;
	while (i * sizeof(t_room) < data->offset)
	{
		if (((t_room*)data->block + i)->attribute == START)
		{
			((t_room*)data->block + i)->used = 1;
			((t_room*)data->block + i)->distance = 0;
			return (((t_room*)data->block + i));
		}
		i++;
		if (i * sizeof(t_room) >= data->offset && data->next)
		{
			data = data->next;
			i = 0;
		}
	}
	return (NULL);
}

static void	ft_put_heap(t_heap *heap)
{
	uint64_t	i;

	i = 1;
	printf("start of ft_put_heap\n");
	while (i < heap->i)
	{
		printf("name: %s, distance: %llu, heap_index: %llu, real_index: %llu\n", ((t_room**)heap->buffer)[i]->name, ((t_room**)heap->buffer)[i]->distance, ((t_room**)heap->buffer)[i]->heap_index, i);
		if (((t_room**)heap->buffer)[i]->heap_index != i)
			ft_error_exit(1, (char*[]){"FAILED"}, EXIT_FAILURE);
		i++;
	}
	printf("end of ft_put_heap\n");

}

static inline void	ft_make_graph_heap(t_heap *graph_heap, t_room *start
									, t_lem_in_data *lem_in_data)
{
	t_mem_block	*tmp;
	uint64_t	i;

	tmp = lem_in_data->data;
	i = 0;
	((t_room**)graph_heap->buffer)[graph_heap->i++] = start;
	start->heap_index = 1;
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
		printf("tested distance of room: %s, with new_distance: %llu, old_distance: %llu, current_index: %llu\n", (*((t_room**)tmp->block + i))->name, distance, (*((t_room**)tmp->block + i))->distance, (*((t_room**)tmp->block + i))->heap_index);
		if (!(*((t_room**)tmp->block + i))->used && distance < (*((t_room**)tmp->block + i))->distance)
		{
			(*((t_room**)tmp->block + i))->distance = distance;
			ft_min_heap_percolate_up(heap, (*((t_room**)tmp->block + i))->heap_index);
			printf("Updated distance room: %s : %llu: new index: %llu\n", (*((t_room**)tmp->block + i))->name, (*((t_room**)tmp->block + i))->distance, (*((t_room**)tmp->block + i))->heap_index);
		}
		i++;
		if (i * sizeof(t_room*) >= tmp->offset && tmp->next && !(i = 0))
			tmp = tmp->next;
	}
}

void	ft_dijsktra(t_lem_in_data *lem_in_data)
{
	t_heap	*solve_heap;
	t_heap	*graph_heap;
	t_room	*start;
	t_room	*tmp;

	solve_heap = ft_create_heap(sizeof(t_room*), lem_in_data->room_nbr);
	graph_heap = ft_create_heap(sizeof(t_room*), lem_in_data->room_nbr);
	if (!(start = ft_get_start_room(lem_in_data)))
		ft_error_exit(1, (char*[]){LEM_IN_ERR}, EXIT_FAILURE);
	ft_make_graph_heap(graph_heap, start, lem_in_data);
	t_room *test;

	test = NULL;
	printf("added room: %s: graph_heap_index: %llu\n", start->name, graph_heap->i);
	while (graph_heap->i > 1)
	{
		tmp = ((t_room**)graph_heap->buffer)[1];
		printf("tmp->distance: %llu\n", tmp->distance);
		ft_put_heap(graph_heap);
		ft_min_heap_remove_elem(graph_heap);
		ft_put_heap(graph_heap);
		tmp->used = 1;
		printf("added room: %s: graph_heap_index: %llu\n", tmp->name, graph_heap->i);
		ft_update_neighbour_distances(graph_heap, tmp);
//		ft_max_heap_add_elem(solve_heap, &tmp);
		if (tmp->attribute == END)
			test = tmp;
	}
	if (test)
		printf("end_name: %s end distance: %llu\n", test->name, test->distance);
}
