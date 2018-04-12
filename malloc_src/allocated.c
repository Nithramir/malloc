/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocated.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:21:06 by bandre            #+#    #+#             */
/*   Updated: 2018/04/12 19:58:25 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*create_initialized_memory(size_t size)
{
	char	*mem;
	size_t	i;

	i = 0;
	mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (mem == (void *)-1)
		return (NULL);
	while (i < size)
	{
		mem[i] = '\0';
		i++;
	}
	return (mem);
}

int			free_memory(void *ptr, size_t size)
{
	if (munmap(ptr, size) == -1)
		return (0);
	return (1);
}

void		ft_copy(char *dest, char *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
}

t_allocated	*set_bigger_list_malloc(t_mem_zone *zone)
{
	size_t		new_list_malloc_size;
	t_allocated	*new_list_malloc;

	new_list_malloc = NULL;
	new_list_malloc_size = zone->list_malloc_size + 256;
	new_list_malloc = create_initialized_memory(sizeof(t_allocated) * new_list_malloc_size);
	ft_copy((char*)new_list_malloc, (char*)zone->list_malloc,
		zone->list_malloc_size * (sizeof(t_allocated)));
	if (!free_memory(zone->list_malloc,
		sizeof(t_allocated) * zone->list_malloc_size))
		return (NULL);
	zone->list_malloc_size = new_list_malloc_size;
	zone->list_malloc = new_list_malloc;
	return (new_list_malloc);
}

/*
** Create a new allocated zone
** In which we can store malloc
*/

t_mem_zone	*create_mem_zone(size_t size, t_mem_zone *before)
{
	t_mem_zone *zone;

	zone = create_initialized_memory(getpagesize());
	if (!zone)
		return (NULL);
	zone->mem_zone = create_initialized_memory(size);
	zone->list_malloc = create_initialized_memory(sizeof(t_allocated) * 256);
	if (!zone->mem_zone || !zone->list_malloc)
		return (NULL);
	zone->list_malloc_size = 256;
	zone->memory_size = size;
	zone->memory_used = 0;
	zone->next = NULL;
	zone->before = before;
	return (zone);
}

int			malloc_position(t_mem_zone *place, size_t asked_memory_size, size_t *i)
{
	size_t position;

	*i = 0;
	position = 0;
	while ((*i) < place->list_malloc_size && place->list_malloc[*i].size)
	{
		if (place->list_malloc[*i].position == NULL && place->list_malloc[*i].size >= asked_memory_size)
			return (position);
		position += place->list_malloc[*i].size;
		(*i)++;
	}
	if ((place->memory_size - position) < asked_memory_size){
		return (-1);
	}
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
