/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:13:54 by bandre            #+#    #+#             */
/*   Updated: 2018/04/24 14:46:49 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free_ptr(void *ptr, size_t size)
{
	munmap(ptr, size);
}

void	delete_mem_zone(t_mem_zone *zone)
{
	if (zone->before)
	{
		zone->before->next = zone->next;
		if (zone->next)
		{
			zone->next->before = zone->before;
		}
		free_ptr((void*)zone->list_malloc,
			sizeof(t_allocated) * zone->list_malloc_size);
	}
}

void	clean_zone(t_mem_zone *zone, size_t pos)
{
	zone->memory_used -= zone->list_malloc[pos].size + 1;
	zone->list_malloc[pos].position = NULL;
	if (zone->memory_used == 0)
	{
		delete_mem_zone(zone);
	}
}

int		search_in_malloc(void *ptr, t_mem_zone *zone)
{
	size_t i;

	i = 0;
	while (i < zone->list_malloc_size)
	{
		if (zone->list_malloc[i].position == ptr)
		{
			clean_zone(zone, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int		ft_search_ptr(void *ptr, t_mem_zone **first_zone)
{
	int			result;
	t_mem_zone	*tmp;

	tmp = *first_zone;
	result = 0;
	while (tmp && result == 0)
	{
		result = search_in_malloc(ptr, tmp);
		if (!result)
			tmp = tmp->next;
	}
	return (result);
}
