/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeclipso <aeclipso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 04:42:51 by aeclipso          #+#    #+#             */
/*   Updated: 2020/11/24 04:48:27 by aeclipso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		check_cone(t_obj *cone)
{
	if (cone->radius < 0.1 ||
	cone->color[0] < 0 || cone->color[0] > 255 ||
	cone->color[1] < 0 || cone->color[1] > 255 ||
	cone->color[2] < 0 || cone->color[2] > 255)
		error_cone();
}

void		parse_param_cone(t_rt *r, char *line)
{
	if (ft_strnequ(line, "    point-x:", 12))
		r->obj[r->count].center.x = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    point-y:", 12))
		r->obj[r->count].center.y = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    point-z:", 12))
		r->obj[r->count].center.z = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    radius:", 11))
		r->obj[r->count].radius = ft_atoi(&line[12]);
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

void		parse_cone(t_rt *r, int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 11)
	{
		if (get_next_line(fd, &line) > 0)
			parse_param_cone(r, line);
		else
			error_read(fd);
		free(line);
	}
	//normalize_vec
	r->obj[r->count].rot = vec_norm(r->obj[r->count].rot);
	check_cone(&r->obj[r->count]);
	r->obj[r->count].name = "cone";    //??
	r->count++;
}
