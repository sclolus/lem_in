/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/30 23:22:51 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/08 06:11:10 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEAP_H
# define FT_HEAP_H

# include "libft.h"
# include <stdint.h>
# include <unistd.h>
# include "lem_in.h"

/*
** index 0 is skipped to make indexation calculation faster with bitwise ops
*/

typedef struct	s_heap
{
	void		*buffer;
	uint64_t	i;
	uint64_t	type_size;
	uint64_t	capacity;
}				t_heap;

/*
** Heap Allocation
*/

t_heap			*ft_create_heap(uint64_t type_size, uint64_t elem_nbr);

/*
** Heap operations
*/

void			ft_max_heap_add_elem(t_heap *heap, void *elem);
void			ft_max_heap_remove_elem(t_heap *heap);
void			ft_min_heap_add_elem(t_heap *heap, void *elem);
void			ft_min_heap_remove_elem(t_heap *heap);
void			ft_min_heap_percolate_up(t_heap *heap, uint64_t index);
void			ft_max_heap_percolate_up(t_heap *heap, uint64_t index);
void			ft_min_heap_percolate_down(t_heap *heap, uint64_t index);
void			ft_max_heap_percolate_down(t_heap *heap, uint64_t index);
void			ft_make_max_heap(t_heap *heap, void *elems, uint32_t nbr_elem);
void			ft_make_min_heap(t_heap *heap, void *elems, uint32_t nbr_elem);

/*
** Free functions
*/

void			ft_free_heap(t_heap *heap);

/*
** Error Handling
*/

# define ERR_CREATE_HEAP "ft_create_heap() allocation failed"

#endif
