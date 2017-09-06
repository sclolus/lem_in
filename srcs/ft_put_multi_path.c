/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_multi_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 04:39:40 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/06 04:26:02 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline static void		ft_put_lem_move(t_lem *lem)
{
	static char	buffer[11];
	uint32_t	index;
	int64_t		divider;
	uint32_t	len;
	uint32_t	nbr;

	index = 0;
	divider = 1;
	len = 1;
	nbr = lem->lem_number;
	while (divider * 10 <= nbr)
	{
		divider *= 10;
		len++;
	}
	while (nbr != 0 || !index)
	{
		buffer[len - index - 1] = nbr % 10 + '0';
		nbr /= 10;
		index++;
	}
	buffer[index] = '\0';
	ft_static_put("L", 1, 0);
	ft_static_put(buffer, index, 0);
	ft_static_put("-", 1, 0);
	ft_static_put(lem->room->name, lem->room->len, 0);
	ft_static_put(" ", 1, 0);

}

inline static void		ft_send_lem_to_path(t_lem *lem, t_room *room)
{
	if (!room || !room->flow.capacity)
		return ;
	lem->room->flow.capacity++;
	lem->room = room;
	lem->index++;
	room->flow.capacity--;
	ft_put_lem_move(lem);
}

inline static t_path **ft_make_paths_tab(t_list *paths_list, uint32_t nbr_path)
{
	t_path			**paths;
	t_list			*tmp;
	uint32_t		i;

	if (!(paths = (t_path**)ft_memalloc(sizeof(t_path*) * nbr_path)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	i = 0;
	while (i < nbr_path)
	{
		paths[i] = paths_list->content;
		tmp = paths_list;
		paths_list = paths_list->next;
		free(tmp);
		i++;
	}
	return (paths);
}

void					ft_put_multi_path(t_lem_in_data *lem_in_data, t_list *paths_list, uint32_t nbr_path)
{
	t_lem			*lems;
	t_path			**paths;
	uint32_t		i;
	uint32_t		u;

	if (!(lems = ft_memalloc(sizeof(t_lem) * lem_in_data->lem_nbr)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	paths = ft_make_paths_tab(paths_list, nbr_path);
	i = 0;
	while (i < lem_in_data->lem_nbr)
	{
		lems[i].room = lem_in_data->start;
		lems[i].index = 0;
		lems[i].lem_number = i + 1;
		lems[i].path_index = i % nbr_path;
		i++;
	}
	i = 0;
	while (i < lem_in_data->lem_nbr)
	{
		u = 0;
		while (u < lem_in_data->lem_nbr)
		{
			if (lems[u].index == (paths[lems[u].path_index])->path_len - 1)
			{
				u++;
				continue ;
			}
			ft_send_lem_to_path(lems + u, (paths[lems[u].path_index])->rooms[lems[u].index + 1]);
			if (lems[u].room->attribute == END)
				i++;
			u++;
		}
		ft_static_put("\n", 1, 0);
	}
	ft_static_put(NULL, 0, STATIC_PUT_FLUSH);
}
