/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeclipso <aeclipso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:52:25 by aeclipso          #+#    #+#             */
/*   Updated: 2020/11/24 06:37:42 by aeclipso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			check_param(char *line)
{
	if (ft_strequ(line, "cone:") || ft_strequ(line, "sphere:")
		|| ft_strequ(line, "plane:") || ft_strequ(line, "cylinder:")
		|| ft_strequ(line, "cam:") || ft_strequ(line, "light:") ||
	ft_strnequ(line, "    light-type:", 15) ||
	ft_strnequ(line, "    intensity:", 14) ||
	ft_strnequ(line, "    point-x:", 12) || ft_strnequ(line, "    point-y:", 12) ||
	ft_strnequ(line, "    point-z:", 12) ||
	ft_strnequ(line, "    direction-x:", 16) ||
	ft_strnequ(line, "    direction-y:", 16) ||
	ft_strnequ(line, "    direction-z:", 16) ||
	ft_strnequ(line, "    angle-x:", 12) ||
	ft_strnequ(line, "    angle-y:", 12) ||
	ft_strnequ(line, "    angle-z:", 12) ||
	ft_strnequ(line, "    rot-x:", 10) ||
	ft_strnequ(line, "    rot-y:", 10) ||
	ft_strnequ(line, "    rot-z:", 10) ||
	ft_strnequ(line, "    red:", 8) ||
	ft_strnequ(line, "    green:", 10) ||
	ft_strnequ(line, "    blue:", 9) ||
	ft_strnequ(line, "    specular:", 13) ||
	ft_strnequ(line, "    radius:", 11))
		return (1);
	else
		error_param(line);
	return (0);
}

void		counter_obj(t_rt *r, char *arg)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	if ((fd = open(arg, O_RDONLY)) < 0)
		error_open();
	while (get_next_line(fd, &line) > 0)
	{
		valid_line(line);
		if (ft_strequ(line, "cone:") || ft_strequ(line, "sphere:")
		|| ft_strequ(line, "plane:") || ft_strequ(line, "cylinder:"))
			r->amount_obj++;
		if (ft_strequ(line, "light:"))
			r->s++;
		if (ft_strequ(line, "cam:"))
			i++;
		free(line);
	}
	close(fd);
}

void		parse_param(t_rt *r, char *arg)
{
	int		fd;
	char	*line;

	if ((fd = open(arg, O_RDONLY)) < 0)
		error_open();
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strequ("cam:", line))
			parse_cam(r, fd);
		else if (ft_strequ("light:\0", line))
			parse_light(r, fd);
		else if (ft_strequ("cone:\0", line))
			parse_cone(r, fd);
		else if (ft_strequ("sphere:\0", line))
			parse_sphere(r, fd);
		else if (ft_strequ("plane:\0", line))
			parse_plane(r, fd);
		else if (!(ft_strcmp("cylinder:\0", line)))
			parse_cylinder(r, fd);
		else
			error_obj(line);
		free(line);
	}
	// free(line);
}

void		ft_parser(char *arg, t_rt *r)
{
	counter_obj(r, arg);
	if (!(r->obj = ft_memalloc(sizeof(t_obj) * r->amount_obj))) //не забыть очистить
		return ;
	parse_param(r, arg);
}
