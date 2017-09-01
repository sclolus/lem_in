/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_heap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 19:06:55 by sclolus           #+#    #+#             */
/*   Updated: 2017/08/31 23:18:22 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

inline void	ft_make_min_heap(t_heap *heap, void *elems, uint32_t nbr_elem)
{
	uint64_t	i;

	ft_memcpy((unsigned char*)heap->buffer + heap->type_size, elems
			, heap->type_size * nbr_elem);
	heap->i += nbr_elem * heap->type_size;
	i = heap->i - 1;
	while (i > 0)
		ft_min_heap_percolate_down(heap, i--);
}

inline void	ft_make_max_heap(t_heap *heap, void *elems, uint32_t nbr_elem)
{
	uint64_t	i;

	ft_memcpy((unsigned char*)heap->buffer + heap->type_size, elems
			, heap->type_size * nbr_elem);
	heap->i += nbr_elem * heap->type_size;
	i = heap->i - 1;
	while (i > 0)
		ft_max_heap_percolate_down(heap, i--);
}
