/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_memory_place.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:18:17 by bandre            #+#    #+#             */
/*   Updated: 2018/04/24 17:39:30 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			malloc_position(t_mem_zone *place,
	size_t asked_memory_size, size_t *i)
{
	size_t position;

	*i = 0;
	position = 0;
	while ((*i) < place->list_malloc_size && place->list_malloc[*i].size)
	{
		if (place->list_malloc[*i].position == NULL
			&& place->list_malloc[*i].size >= asked_memory_size)
			return (position);
		position += place->list_malloc[*i].size;
		(*i)++;
	}
	if ((place->memory_size - position) < asked_memory_size)
		return (-1);
	return (position);
}

void		*add_malloc(t_mem_zone *place, size_t asked_memory_size,
	int position, size_t i)
{
	if (i == place->list_malloc_size)
		set_bigger_list_malloc(place);
	if (!place->list_malloc[i].size)
		place->list_malloc[i].size = asked_memory_size;
	place->list_malloc[i].position = (void*)place->mem_zone + position;
	place->memory_used = asked_memory_size + place->memory_used;
	return (place->mem_zone + position);
}

void		*search_allocated_zone(t_mem_zone *zone, size_t asked_memory_size)
{
	size_t	i;
	int		position;

	i = 0;
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
