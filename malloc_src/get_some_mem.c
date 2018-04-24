/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_some_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 18:27:30 by bandre            #+#    #+#             */
/*   Updated: 2018/04/24 18:38:19 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*get_tiny_memory(size_t asked_mem_size, t_mem_zone **zone, size_t size)
{
	void *retour;

	if (!(*zone))
		*zone = create_mem_zone(size * 1, NULL);
	if (!(*zone))
		return (NULL);
	retour = get_memory_position(*zone, asked_mem_size, size * 64);
	return (retour);
}

void	*get_large_memory(size_t asked_memory_size,
	t_mem_zone **zone, size_t zone_size)
{
	if (!(*zone))
		*zone = create_mem_zone(zone_size, NULL);
	return (get_memory_position(*zone, asked_memory_size, zone_size));
}
