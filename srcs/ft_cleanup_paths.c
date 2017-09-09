/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 05:47:41 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/09 05:52:57 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_cleanup_paths(t_path ***paths)
{
	uint32_t	i;

	i = 0;
	while ((*paths)[i])
		free((*paths)[i++]);
	free(*paths);
}
