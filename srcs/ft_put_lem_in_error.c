/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_lem_in_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 23:21:34 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/08 23:24:27 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline NORETURN	ft_put_lem_in_error(void)
{
	ft_putendl_fd(LEM_IN_ERR, 2);
	exit(EXIT_FAILURE);
}
