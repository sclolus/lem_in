/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percolate_up.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 23:36:14 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/08 06:10:15 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

inline void	ft_min_heap_percolate_up(t_heap *heap, uint64_t index)
{
	t_room	*tmp;

	while (index > 1
		&& (*((t_room **)heap->buffer + index))->distance
		< (*((t_room **)heap->buffer + (index >> 1)))->distance)
	{
		tmp = *((t_room **)heap->buffer + (index >> 1));
		*((t_room **)heap->buffer + (index >> 1)) =
			*((t_room **)heap->buffer + (index));
		*((t_room **)heap->buffer + (index)) = tmp;
		tmp->heap_index = index;
		index >>= 1;
	}
	(*((t_room **)heap->buffer + index))->heap_index = index;
}

inline void	ft_max_heap_percolate_up(t_heap *heap, uint64_t index)
{
	t_room	*tmp;

	while (index > 1
		&& (*((t_room **)heap->buffer + index))->distance
		> (*((t_room **)heap->buffer + (index >> 1)))->distance)
	{
		tmp = *((t_room **)heap->buffer + (index >> 1));
		*((t_room **)heap->buffer + (index >> 1)) =
			*((t_room **)heap->buffer + (index));
		*((t_room **)heap->buffer + (index)) = tmp;
		index >>= 1;
	}
}
