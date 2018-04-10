/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:32:15 by bandre            #+#    #+#             */
/*   Updated: 2018/04/10 21:12:59 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_malloc g_malloc = {NULL, NULL, NULL, NULL, NULL};

void	*get_tiny_memory(size_t asked_memory_size,
	t_mem_zone **zone, size_t zone_size)
{
	if (!(*zone))
		*zone = new_mem_zone(asked_memory_size, NULL);
	if (!(*zone))
		return (NULL);
	return (get_memory_place(*zone, asked_memory_size, zone_size * 100));
}

void	*get_large_memory(size_t asked_memory_size,
	t_mem_zone **zone, size_t zone_size)
{
	if (!(*zone))
		*zone = new_mem_zone(zone_size, NULL);
	return (get_memory_place(*zone, asked_memory_size, zone_size));
}

void	*malloc(size_t asked_mem_size)
{
	if (asked_mem_size < (size_t)MALLOC_TINY)
		return (get_tiny_memory(asked_mem_size, &g_malloc.tiny, MALLOC_TINY));
	else if (asked_mem_size < (size_t)MALLOC_SMALL)
		return (get_tiny_memory(asked_mem_size, &g_malloc.small, MALLOC_SMALL));
	else
	{
		return (get_large_memory(asked_mem_size, &g_malloc.large,
			asked_mem_size + 1));
	}
	return (NULL);
}

void	free(void *ptr)
{
	int result;


	result = 0;
	if (g_malloc.large)
		result = ft_search_ptr(ptr, &g_malloc.large);
	if (!result && g_malloc.small)
		result = ft_search_ptr(ptr, &g_malloc.small);
	if (!result && g_malloc.tiny)
	{
		result = ft_search_ptr(ptr, &g_malloc.tiny);
	}
}

void	*realloc(void *ptr, size_t new_size)
{
	char	*new_ptr;
	size_t	size;

	size = 0;
	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
		free(ptr);
	if (g_malloc.large)
		size = ft_search_size(ptr, g_malloc.large);
	if (!size && g_malloc.small)
		size = ft_search_size(ptr, g_malloc.small);
	if (!size && g_malloc.tiny)
	{
		size = ft_search_size(ptr, g_malloc.tiny);
	}
	if (!size)
	{
		return (NULL);
	}
	
	new_ptr = (char*)malloc(new_size);
	if (!new_ptr)
	{
		return (NULL);
	}
	ft_strncpy(new_ptr, ptr, new_size);
	return (new_ptr);
}
