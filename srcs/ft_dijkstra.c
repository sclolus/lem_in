/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dijkstra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 21:19:38 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/05 06:59:28 by sclolus          ###   ########.fr       */
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

static inline t_solve_stack	*ft_make_solve_stack(t_lem_in_data *data)
{
	t_solve_stack	*stack;
	t_room			*current_room;
	uint64_t		i;

	if ((i = (data->end->distance)) == ~0U)
		ft_error_exit(1, (char*[]){LEM_IN_ERR}, EXIT_FAILURE);
	if (!(stack = (t_solve_stack*)ft_memalloc(sizeof(t_solve_stack)
						* data->room_nbr)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	stack[0].room = data->start;
	current_room = data->end;
	while (i > 0)
	{
		stack[i].room = current_room;
		current_room = current_room->shortest;
		i--;
	}
	return (stack);
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

void	__attribute__((noreturn)) ft_dijsktra(t_lem_in_data *lem_in_data)
{
	t_solve_stack	*stack;
	t_heap			*graph_heap;
	t_room			*start;
	t_room			*tmp;

	graph_heap = ft_create_heap(sizeof(t_room*), lem_in_data->room_nbr);
	(void)ft_swap_target;
//	ft_swap_target(lem_in_data);
	start = lem_in_data->start;
	ft_make_graph_heap(graph_heap, start, lem_in_data);
	while (graph_heap->i > 1)
	{
		tmp = ((t_room**)graph_heap->buffer)[1];
/* 		if (tmp->attribute == START) */
/* 			break ; */
		ft_min_heap_remove_elem(graph_heap);
		tmp->used = 1;
		ft_update_neighbour_distances(graph_heap, tmp);
	}
	stack = ft_make_solve_stack(lem_in_data);
	ft_put_solution(lem_in_data, stack, lem_in_data->end->distance);
}
