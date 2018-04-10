/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:10:39 by bandre            #+#    #+#             */
/*   Updated: 2018/04/10 21:13:57 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	search_size_in_malloc(void *ptr, t_mem_zone *zone)
{
	size_t	i;

	i = 0;
	while (i < zone->list_malloc_size)
	{
		if (zone->list_malloc[i].position == ptr)
			return (zone->list_malloc[i].size);
		i++;
	}
	return (0);
}

size_t	ft_search_size(void *ptr, t_mem_zone *first_zone)
{
	size_t	result;

	result = 0;
	while (first_zone && result == 0)
	{
		result = search_size_in_malloc(ptr, first_zone);
		if (!result)
			first_zone = first_zone->next;
	}
	return (result);
}
