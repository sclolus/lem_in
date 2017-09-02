/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 03:50:38 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/02 14:01:12 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			main(int argc, char **argv)
{
	t_lem_in_data	*lem_in_data;
	t_lem_flags		flags;

	flags.flags = 0;
	if (argc == 2)
		flags = ft_parse_flags(argv[1]);
	else if (argc > 2)
	{
		ft_putendl_fd(LEM_IN_ERR, 2);
		return (EXIT_FAILURE);
	}
	lem_in_data = ft_parse();
	lem_in_data->flags = flags;
	ft_check_integrity(lem_in_data);
	ft_dijsktra(lem_in_data);
	ft_putendl_fd(LEM_IN_ERR, 2);
	return (0);
}
