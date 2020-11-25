/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeclipso <aeclipso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 05:02:58 by aeclipso          #+#    #+#             */
/*   Updated: 2020/11/24 06:28:03 by aeclipso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		parse_param_cam(t_rt *r, char *line)
{
	if (ft_strnequ(line, "    point-x:", 12))
		r->cam.point.x = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    point-y:", 12))
		r->cam.point.y = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    point-z:", 12))
		r->cam.point.z = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    angle-x:", 12))
		r->cam.angles.x = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    angle-y:", 12))
		r->cam.angles.y = ft_atoi(&line[13]);
	else if (ft_strnequ(line, "    angle-z:", 12))
		r->cam.angles.z = ft_atoi(&line[13]);
	else
		error_param(line);
}

void		parse_cam(t_rt *r, int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 6)
	{
		if (get_next_line(fd, &line) > 0)
			parse_param_cam(r, line);
		else
			error_read(fd);
		free(line);
	}
}
