/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_last_attr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 04:56:01 by sclolus           #+#    #+#             */
/*   Updated: 2017/07/10 04:56:38 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_attribute		*ft_get_last_attribute(void)
{
	static t_attribute	last_attribute = NORMAL;

	return (&last_attribute);
}
