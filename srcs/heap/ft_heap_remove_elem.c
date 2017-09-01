/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap_remove_elem.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 19:00:06 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/01 12:07:11 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

inline void		ft_min_heap_remove_elem(t_heap *heap)
{
	((t_room**)heap->buffer)[1] = ((t_room**)heap->buffer)[heap->i - 1];
	heap->i--;
	((t_room**)heap->buffer)[1]->heap_index = 1;
	ft_min_heap_percolate_down(heap, 1);
}

inline void		ft_max_heap_remove_elem(t_heap *heap)
{

	ft_memcpy((unsigned char *)heap->buffer + (1 * heap->type_size)
	, (unsigned char *)heap->buffer + ((heap->i - 1) * heap->type_size)
	, heap->type_size);
	heap->i--;
	ft_max_heap_percolate_down(heap, 1);
}
