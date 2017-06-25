/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_mem_block.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 13:56:03 by sclolus           #+#    #+#             */
/*   Updated: 2017/06/25 14:10:31 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_mem_block	*ft_create_mem_block(uint64_t capacity)
{
	t_mem_block	*mem_block;

	if (capacity % sizeof(t_room))
	{
		ft_error(1, (char*[]){INVALID_MEM_CAPACITY}, 0);
		return (NULL);
	}
	while (!(mem_block = (t_mem_block*)ft_memalloc(capacity
			+ sizeof(t_mem_block))))
	{
		capacity >>= 2;
		if (MEM_BLOCK_LIMIT > capacity)
		{
			ft_error(1, (char*[]){MALLOC_FAILURE}, 0);
			exit(EXIT_FAILURE);
		}
	}
	mem_block->capacity = capacity;
	mem_block->block = mem_block + sizeof(t_mem_block);
	return (mem_block);
}
