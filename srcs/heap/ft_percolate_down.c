/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percolate_down.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 23:43:17 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/01 12:17:51 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

inline void	ft_max_heap_percolate_down(t_heap *heap, uint64_t index)
{
	t_room		*tmp;
	t_room		**to_swap;
	uint64_t	new_index;

	while (index < heap->i)
	{
		to_swap = NULL;
		if ((index << 1) >= heap->i)
			break ;
		else if ((index << 1) + 1 >= heap->i)
			to_swap = ((t_room **)heap->buffer + (new_index = (index << 1)));
		else
			to_swap = (*((t_room **)heap->buffer + (index << 1)))->distance
				> (*((t_room **)heap->buffer + ((index << 1) + 1)))->distance
				? ((t_room **)heap->buffer + (new_index = (index << 1)))
				: ((t_room **)heap->buffer + (new_index = ((index << 1) + 1)));
		if (!to_swap || (*to_swap)->distance > (*((t_room **)heap->buffer
												+ (index)))->distance)
			break;
		tmp = *to_swap;
		*to_swap = *((t_room **)heap->buffer + (index));
		*((t_room **)heap->buffer + (index)) = tmp;
		index = new_index;
	}
}

inline void	ft_min_heap_percolate_down(t_heap *heap, uint64_t index)
{
	t_room		*tmp;
	t_room		**to_swap;
	uint64_t	new_index;

	while (index < heap->i)
	{
		to_swap = NULL;
		if ((index << 1) >= heap->i)
			break ;
		else if ((index << 1) + 1 >= heap->i)
			to_swap = ((t_room **)heap->buffer + (new_index = (index << 1)));
		else
			to_swap = (*((t_room **)heap->buffer + (index << 1)))->distance
				< (*((t_room **)heap->buffer + ((index << 1) + 1)))->distance
				? ((t_room **)heap->buffer + (new_index = (index << 1)))
				: ((t_room **)heap->buffer + (new_index = ((index << 1) + 1)));
		if (!to_swap || (*to_swap)->distance > (*((t_room **)heap->buffer
												+ (index)))->distance)
			break;
		(*((t_room **)heap->buffer + (index)))->heap_index = new_index;
		(*to_swap)->heap_index = index;
		tmp = *to_swap;
		*to_swap = *((t_room **)heap->buffer + (index));
		*((t_room **)heap->buffer + (index)) = tmp;
		index = new_index;
	}
}
