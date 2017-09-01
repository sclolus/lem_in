/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_heap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 23:25:48 by sclolus           #+#    #+#             */
/*   Updated: 2017/08/30 23:36:30 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_heap.h"

inline t_heap	*ft_create_heap(uint64_t type_size, uint64_t elem_nbr)
{
	t_heap	*heap;

	if (!(heap = ft_memalloc(type_size * (elem_nbr + 1) + sizeof(t_heap))))
		ft_error_exit(1, (char*[]){ERR_CREATE_HEAP}, EXIT_FAILURE);
	heap->buffer = ((char*)heap) + sizeof(t_heap);
	heap->i = 1;
	heap->type_size = type_size;
	heap->capacity = elem_nbr;
	return (heap);
}
