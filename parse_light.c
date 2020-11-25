/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeclipso <aeclipso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 04:49:17 by aeclipso          #+#    #+#             */
/*   Updated: 2020/11/24 04:59:24 by aeclipso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		parse_param_light(t_rt *r, char *line)
{
	if (ft_strnequ(line, "    light-type:", 15))
		r->light->type = ft_strdup(&line[16]);
	else if (ft_strnequ(line, "    intensity:", 14))
		r->light->intensity = ((double)ft_atoi(&line[15])) / 100;
	else if (ft_strnequ(line, "    point-x:", 12))
		r->light->position.x = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    point-y:", 12))
		r->light->position.y = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    point-z:", 12))
		r->light->position.z = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    direction-x:", 16))
		r->light->direction.x = ft_atoi(&line[17]);
	else if (ft_strnequ(line, "    direction-y:", 16))
		r->light->direction.y = ft_atoi(&line[17]);
	else if (ft_strnequ(line, "    direction-z:", 16))
		r->light->direction.z = ft_atoi(&line[17]);
	else
		error_param(line);
}

void		parse_new_light(t_rt *r, int fd)
{
	int		i;
	char	*line;

	i = -1;
	if (!(r->light = (t_light *)malloc(sizeof(t_light))))     //не забыть почистить объект
		error_malloc(fd, line);
	while (++i < 8)
	{
		if (get_next_line(fd, &line) > 0)
			parse_param_light(r, line);
		else
			error_read(fd);
		free(line);
	}
	r->light->next = NULL;
}

void		parse_old_light(t_rt *r, int fd)
{
	int		i;
	char	*line;
	t_light	*begin;

	begin = r->light;
	i = -1;
	if (!(r->light = (t_light *)malloc(sizeof(t_light))))     //не забыть почистить объект
		error_malloc(fd, line);
	r->light->next = begin;
	while (++i < 8)
	{
		if (get_next_line(fd, &line) > 0)
			parse_param_light(r, line);
		else
			error_read(fd);
		free(line);
	}
}

void		parse_light(t_rt *r, int fd)
{
	if (r->light == NULL)
		parse_new_light(r, fd);
	else
	{
		// r->light = r->light->next;
		parse_old_light(r, fd);
	}
}
