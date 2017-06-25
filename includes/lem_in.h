/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 13:52:30 by sclolus           #+#    #+#             */
/*   Updated: 2017/06/25 14:12:13 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

typedef struct	s_mem_block
{
	uint64_t			capacity;
	uint64_t			offset;
	void				*block;
	struct s_mem_block	*next;
}				t_mem_block;

typedef struct	s_room
{
	char			*name;
	uint32_t		capacity;
	uint32_t		nbr_tube;
	struct s_room	**rooms;
}				t_room;

/*
** Mem_block handling
*/

#define MEM_BLOCK_LIMIT 256
#define DEFAULT_MEM_BLOCK_SIZE 1U << 32

void		*ft_mem_block_push_back_elem(t_mem_block *mem_block
									, void *elem, uint32_t size);
t_mem_block	*ft_create_mem_block(uint64_t capacity);


/*
** Error handling
*/

# define INVALID_MEM_CAPACITY "Invalid capacity provided to ft_create_mem_block()"
# define MALLOC_FAILURE "malloc() failed due to insufficient ressources left"
#endif
