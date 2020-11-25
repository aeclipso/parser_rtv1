/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeclipso <aeclipso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 04:37:36 by aeclipso          #+#    #+#             */
/*   Updated: 2020/11/24 04:41:40 by aeclipso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		check_spere(t_obj *spere)
{
	if (spere->radius < 0.1 ||
	spere->color[0] < 0 || spere->color[0] > 255 ||
	spere->color[1] < 0 || spere->color[1] > 255 ||
	spere->color[2] < 0 || spere->color[2] > 255)
		error_spere();
}

void		parse_param_sphere(t_rt *r, char *line)
{
	if (ft_strnequ(line, "    point-x:", 12))
		r->obj[r->count].center.x = (double)ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    point-y:", 12))
		r->obj[r->count].center.y = (double)ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    point-z:", 12))
		r->obj[r->count].center.z = (double)ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    radius:", 11))
		r->obj[r->count].radius = (double)ft_atoi(&line[12]);
	else if (ft_strnequ(line, "    red:", 8))
		r->obj[r->count].color[0] = (unsigned char)(ft_atoi(&line[9]));
	else if (ft_strnequ(line, "    green:", 10))
		r->obj[r->count].color[1] = (unsigned char)(ft_atoi(&line[11]));
	else if (ft_strnequ(line, "    blue:", 9))
		r->obj[r->count].color[2] = (unsigned char)(ft_atoi(&line[10]));
	else if (ft_strnequ(line, "    specular:", 13))
		r->obj[r->count].specular = (double)ft_atoi(&line[14]);
	else
		error_param(line);
}

void		parse_sphere(t_rt *r, int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 8)
	{
		if (get_next_line(fd, &line) > 0)
			parse_param_sphere(r, line);
		else
			error_read(fd);
		free(line);
	}
	check_spere(&r->obj[r->count]);
	r->obj[r->count].name = "sphere";
	r->count++;
}
