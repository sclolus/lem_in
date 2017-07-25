/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 13:52:30 by sclolus           #+#    #+#             */
/*   Updated: 2017/07/25 23:31:26 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdint.h>
# include <stdio.h>

/*
** DEBUG
*/


# define CHECK(x) do {ft_putendl_fd("_______", 2);ft_putendl_fd(#x, 2);ft_putendl_fd("_______", 2);}while(0);

typedef enum	e_attribute
{
	ERR = 0,
	NORMAL,
	START,
	END,
}				t_attribute;

typedef struct	s_coord
{
	uint32_t	x;
	uint32_t	y;
}				t_coord;

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
	t_coord			coords;
	t_attribute		attribute;
	uint32_t		used;
	t_mem_block		*tubes;
}				t_room;

typedef struct	s_lem_in_data
{
	t_mem_block *data;
	t_list		*lines;
	uint32_t	room_nbr;
	uint32_t	lem_nbr;
}				t_lem_in_data;

/*
** Parsing
*/

# define CHARSET_WHITESPACE " \t"
# define DECIMAL_SET "-0123456789"

typedef enum	e_parsing_case
{
	ERROR,
	BEGIN,
	NOTE,
	ROOM,
	TUBE,
	CMD,
	SUPPORTED_PARSING_CASE,
}				t_parsing_case;

typedef int32_t	(*t_case_function)(char*, t_parsing_case);
typedef struct	s_parsing_case_identifier
{
	t_case_function	f;
	t_parsing_case	identifier_case;
	char			pad[4];
}				t_parsing_case_identifier;

typedef struct	s_lem_in_cmd
{
	char		*identifier;
	t_attribute	attr;
	char		pad[4];
}				t_cmd;

typedef int32_t	(*t_parsing_action)(char *, t_lem_in_data *);

t_lem_in_data	*ft_parse(void);
t_parsing_case	ft_get_case(char *line, t_parsing_case last_case);
t_attribute		*ft_get_last_attribute(void);
int32_t			ft_get_lem_nbr(char *line, t_lem_in_data *lem_in_data);
int32_t			ft_get_new_room(char *line, t_lem_in_data *lem_in_data);
int32_t			ft_get_new_cmd(char *line, t_lem_in_data *lem_in_data);
int32_t			ft_get_new_tube(char *line, t_lem_in_data *lem_in_data);
int32_t			ft_get_new_note(char *line, t_lem_in_data *lem_in_data);
int32_t			ft_error_case(char *line, t_lem_in_data *lem_in_data);
int32_t			*ft_get_set_states(void);

/*
** Solving
*/

typedef struct	s_solve_stack
{
	t_room		*room;
	uint32_t	tube_index;
	char		pad[4];
}				t_solve_stack;

void	ft_solve(t_lem_in_data *lem_in_data);

/*
** Mem_block handling
*/

#define MEM_BLOCK_LIMIT 256
#define DEFAULT_MEM_BLOCK_SIZE (sizeof(t_room)  * sizeof(t_room*) * 100000)

void		*ft_mem_block_push_back_elem(t_mem_block *mem_block
									, void *elem, uint32_t size);
t_mem_block	*ft_create_mem_block(uint64_t capacity);


/*
** Error handling
*/

# define INVALID_MEM_CAPACITY "Invalid capacity provided to ft_create_mem_block()"
# define MALLOC_FAILURE "malloc() failed due to insufficient ressources left"
# define LEM_IN_ERR "ERROR"
#endif
