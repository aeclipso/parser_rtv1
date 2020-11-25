/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeclipso <aeclipso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 04:23:10 by aeclipso          #+#    #+#             */
/*   Updated: 2020/11/24 04:37:16 by aeclipso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		check_plane(t_obj *plane)
{
	if (plane->color[0] < 0 || plane->color[0] > 255 ||
	plane->color[1] < 0 || plane->color[1] > 255 ||
	plane->color[2] < 0 || plane->color[2] > 255)
		error_plane();
}

void		parse_param_plane(t_rt *r, char *line)
{
	if (ft_strnequ(line, "    point-x:", 12))
		r->obj[r->count].center.x = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    point-y:", 12))
		r->obj[r->count].center.y = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    point-z:", 12))
		r->obj[r->count].center.z = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    rot-x:", 10))
		r->obj[r->count].rot.x = ft_atoi(&line[11]);
	else if (ft_strnequ(line, "    rot-y:", 10))
		r->obj[r->count].rot.y = ft_atoi(&line[11]);
	else if (ft_strnequ(line, "    rot-z:", 10))
		r->obj[r->count].rot.z = ft_atoi(&line[11]);  //тут нет нормализации после ввоода
	else if (ft_strnequ(line, "    red:", 8))
		r->obj[r->count].color[0] = (ft_atoi(&line[9]));
	else if (ft_strnequ(line, "    green:", 10))
		r->obj[r->count].color[1] = (ft_atoi(&line[11]));
	else if (ft_strnequ(line, "    blue:", 9))
		r->obj[r->count].color[2] = (ft_atoi(&line[10]));
	else if (ft_strnequ(line, "    specular:", 13))
		r->obj[r->count].specular = ft_atoi(&line[14]); //не добавляется имя
	else
		error_param(line);
}

void		parse_plane(t_rt *r, int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 10)
	{
		if (get_next_line(fd, &line) > 0)
			parse_param_plane(r, line);
		else
			error_read(fd);
		free(line);
	}
	r->obj[r->count].rot = vec_norm(r->obj[r->count].rot);
	check_plane(&r->obj[r->count]);
	r->obj[r->count].name = "plane";    //??
	r->count++;
}
