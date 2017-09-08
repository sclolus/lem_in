/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 13:52:30 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/08 06:12:02 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

/*
** DEBUG
*/ //

# define CHECK(x) do {ft_putendl_fd("_______", 2);ft_putendl_fd(#x, 2);ft_putendl_fd("_______", 2);}while(0);

# include "libft.h"
# include "ft_heap.h"
# include <stdint.h>

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

typedef struct	s_flow
{
	uint32_t	capacity;
	uint32_t	flow;
}				t_flow;

typedef struct	s_room
{
	char			*name;
	uint32_t		len;
	t_flow			flow;
	uint32_t		nbr_tube;
	t_coord			coords;
	uint64_t		distance;
	t_attribute		attribute;
	uint32_t		used;
	t_mem_block		*tubes;
	struct s_room	*shortest;
	uint64_t		heap_index;
}				t_room;

typedef struct	s_flags8
{
	char	distance_algo : 1;
	char	bits1 : 1;
	char	quiet : 1;
	char	show_path : 1;
	char	multi_path : 1;
	char	bits5 : 1;
	char	bits6 : 1;
	char	bits7 : 1;
}				t_flags8;

typedef union	u_lem_flags
{
	t_flags8	bits;
	char		flags;
}				t_lem_flags;

typedef struct	s_lem_in_data
{
	t_mem_block *data;
	t_mem_block	*lines;
	t_room		*start;
	t_room		*end;
	uint32_t	room_nbr;
	uint32_t	lem_nbr;
	t_lem_flags	flags;
	char		pad[7];
}				t_lem_in_data;

typedef struct	s_lem
{
	t_room		*room;
	uint32_t	index;
	uint32_t	path_index;
	uint32_t	lem_number;
}				t_lem;

typedef struct	s_path
{
	t_room		**rooms;
	uint32_t	path_len;
}				t_path;

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

/*
** Flags parsing
*/

# define NORETURN __attribute__((noreturn)) void
# define LEM_SHOW_PATH "===============Path===============\n"

t_lem_flags		ft_parse_flags(char *flags);
NORETURN		ft_flags_usage(char invalid_flag);

/*
** I hate the norme for this
*/

int32_t			ft_is_case_start(char __attribute__((unused)) *line
								, t_parsing_case last_case);

/*
** Fuck the norme
*/

t_attribute		*ft_get_last_attribute(void);
int32_t			ft_get_lem_nbr(char *line
							, t_lem_in_data *lem_in_data) __attribute__((cold));
int32_t			ft_get_new_room(char *line
							, t_lem_in_data *lem_in_data) __attribute__((hot));
int32_t			ft_get_new_cmd(char *line
							, t_lem_in_data *lem_in_data) __attribute__((hot));
int32_t			ft_get_new_tube(char *line
							, t_lem_in_data *lem_in_data) __attribute__((hot));
int32_t			ft_get_new_note(char *line
							, t_lem_in_data *lem_in_data) __attribute__((hot));
int32_t			ft_error_case(char *line
							, t_lem_in_data *lem_in_data);
int32_t			*ft_get_set_states(void);
void			ft_check_integrity(t_lem_in_data *lem_in_data);

/*
** Solving
*/

typedef struct	s_solve_stack
{
	t_room		*room;
	uint64_t	index;
}				t_solve_stack;

void			ft_solve(t_lem_in_data *lem_in_data);
void			ft_dijkstra(t_lem_in_data *lem_in_data, t_room *start);
NORETURN		ft_dijkstra_distance(t_lem_in_data *lem_in_data);
void			ft_put_lines(t_mem_block *lines);
NORETURN		ft_put_solution(t_lem_in_data *lem_in_data, t_solve_stack *stack
								, uint64_t index);
void			ft_multi_path(t_lem_in_data *lem_in_data);
void			ft_put_multi_path(t_lem_in_data *lem_in_data
								, t_list *paths_list, uint32_t nbr_path);

void			ft_reset_dijkstra_values(t_mem_block *data, uint32_t value);

/*
** Mem_block handling
*/

# define MEM_BLOCK_LIMIT 256
# define DEFAULT_MEM_BLOCK_SIZE (sizeof(t_room) * sizeof(t_room*) * 50)
# define DEFAULT_MEM_BLOCK_TUBE_SIZE (sizeof(t_room*) * 10)
# define DEFAULT_MEM_BLOCK_ROOM_SIZE (sizeof(t_room) * 10000)
# define DEFAULT_MEM_BLOCK_LINES_SIZE (sizeof(char*) * 100000)

void			*ft_mem_block_push_back_elem(t_mem_block *mem_block
									, void *elem, uint32_t size);
t_mem_block		*ft_create_mem_block(uint64_t capacity);

/*
** Error handling
*/

# define INVALID_MEM_CAPACITY "Invalid size provided to ft_create_mem_block()"
# define MALLOC_FAILURE "malloc() failed due to insufficient ressources left"
# define LEM_IN_ERR "ERROR"
# define ERR_INVALID_FLAG "Invalid flags: "
# define FLAG_USAGE "Supported flags are: -v, -q, -d, -s"
# define INVALID_FLAGS_FORMAT "Invalid flag format: '-[flags]'"
#endif
