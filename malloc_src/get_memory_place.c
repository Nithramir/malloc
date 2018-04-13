/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_memory_place.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:18:17 by bandre            #+#    #+#             */
/*   Updated: 2018/04/13 14:28:16 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*search_allocated_zone(t_mem_zone *zone, size_t asked_memory_size)
{
	size_t i;
	int position;

	i = 0;
	// ft_putendl("search allocated wone enter");
	// ft_printf("mem_size: %zu et mem_used: %zu\n", zone->memory_size, zone->memory_used );
	while (zone)
	{
		if (zone->memory_size - zone->memory_used >= asked_memory_size)
		{
			position = malloc_position(zone, asked_memory_size, &i);
			if (position != -1)
			{
				return (add_malloc(zone, asked_memory_size, position, i));
			}
		}
		zone = zone->next;
	}
	// ft_putendl("search allocated wone out");
	return (NULL);
}

/*
** search in all allocated zone if we can stock a new memory
** else create a new allocated zone
*/

t_mem_zone	*get_memory_position(t_mem_zone *zone, size_t asked_memory_size,
	size_t zone_size)
{
	void *place;

	place = search_allocated_zone(zone, asked_memory_size);
	if (!place)
	{
		while (zone->next)
		{
			zone = zone->next;
		}
		place = create_mem_zone(zone_size, zone);
		zone->next = place;
		place = search_allocated_zone(place, asked_memory_size);
	}
	return (place);
}
