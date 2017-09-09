/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_one_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 05:15:35 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/09 05:19:50 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline void		ft_add_one_path_sort(t_list *tmp, t_list **lst)
{
	t_list		*current;
	t_list		*prev;

	current = *lst;
	prev = NULL;
	while (current && ((t_path*)tmp->content)->path_len
			> ((t_path*)current->content)->path_len)
	{
		prev = current;
		current = current->next;
	}
	if (prev)
	{
		prev->next = tmp;
		tmp->next = current;
	}
	else
	{
		*lst = tmp;
		tmp->next = current;
	}
}

inline void		ft_add_one_path(t_list **lst, t_solve_stack *stack
								, uint32_t path_len)
{
	t_path		*path;
	t_list		*tmp;
	uint32_t	i;

	if (!(path = (t_path*)malloc(sizeof(t_path) + sizeof(t_room**) * path_len))
		|| !(tmp = ft_lstnew(NULL, 0)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	i = 0;
	path->path_len = path_len;
	path->rooms = (t_room**)((unsigned char *)path + sizeof(t_path));
	while (i < path_len)
	{
		path->rooms[i] = stack[path_len - i - 1].room;
		i++;
	}
	tmp->content = path;
	ft_add_one_path_sort(tmp, lst);
}
