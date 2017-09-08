/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap_add_elem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 23:31:50 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/08 06:07:33 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

inline void	ft_min_heap_add_elem(t_heap *heap, void *elem)
{
	ft_memcpy((unsigned char*)heap->buffer + heap->i * heap->type_size, elem
			, heap->type_size);
	ft_min_heap_percolate_up(heap, heap->i++);
}

inline void	ft_max_heap_add_elem(t_heap *heap, void *elem)
{
	ft_memcpy((unsigned char*)heap->buffer + heap->i * heap->type_size, elem
			, heap->type_size);
	ft_max_heap_percolate_up(heap, heap->i++);
}
