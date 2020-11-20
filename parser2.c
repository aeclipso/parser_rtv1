/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeclipso <aeclipso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:52:25 by aeclipso          #+#    #+#             */
/*   Updated: 2020/11/20 19:44:06 by aeclipso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int					ft_strequ3(char const *s1, char const *s2)
{
if (s1 == NULL || s2 == NULL)
		return (0);
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}

void		error_plane(void)
{
	ft_printf("Wrong input for plane\n");
	exit(1);
}

void		error_cone(void)
{
	ft_printf("Wrong input for cone\n");
	exit(1);
}

void		error_cyl(void)
{
	ft_printf("Wrong input for cylinder\n");
	exit(1);
}

void		error_spere(void)
{
	ft_printf("Wrong input for spere\n");
	exit(1);
}

void		error_open(void)
{
	ft_printf("Bad file");
	exit(1);
}

void		error_read(int fd)
{
	close(fd);
	ft_printf("Error read");
	exit(1);
}

void		error_malloc(int fd, char *line)
{
	close(fd);
	// free(line);
	ft_printf("Error allocation\n");
	exit(1);
}

void		error_param(char *line)
{
	ft_printf("%s\n", line);
	ft_printf("Wrong parameter or bad identation(need 0 or 4 spaces)\n");
	// free(line);
	exit(1);
}

void		error_obj(char *line)
{
	ft_printf("%s\n", line);
	ft_printf("ERROR OBJECT\n");
	// free(line);
	exit(1);
}

int		space_end(char *line)
{
	int		len;

	len = ft_strlen(line);
	if (len > 0 && (ft_isalnum(line[len - 1]) || line[len - 1] == ':'))
		return (1);
	else
		error_param(line);
	return (0);
}

int			ws_count(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

int			space_before(char *line)
{
	if (ft_strequ3(line, "cone:") || ft_strequ3(line, "sphere:")
		|| ft_strequ3(line, "plane:") || ft_strequ3(line, "cylinder:") 
		|| ft_strequ3(line, "cam:") || ft_strequ3(line, "light:"))
		{
			return (1);
		}
	else if(ws_count(line) == 4)
		return (1);
	else
		error_param(line);
	return (0);
}

int		check_param(char *line)
{
	if (ft_strequ3(line, "cone:") || ft_strequ3(line, "sphere:")
		|| ft_strequ3(line, "plane:") || ft_strequ3(line, "cylinder:") 
		|| ft_strequ3(line, "cam:") || ft_strequ3(line, "light:") ||
	ft_strnequ(line, "    light-type:", 15) ||
	ft_strnequ(line, "    intensity:", 14) ||
	ft_strnequ(line, "    point-x:", 12) ||
	ft_strnequ(line, "    point-y:", 12) ||
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

int		valid_line(char *line)
{
	if (space_end(line) && space_before(line) && check_param(line))
		return (1);
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
		if (ft_strequ3(line, "cone:") || ft_strequ3(line, "sphere:")
		|| ft_strequ3(line, "plane:") || ft_strequ3(line, "cylinder:"))
			r->amount_obj++;
		if (ft_strequ3(line, "light:"))
			r->s++;
		if (ft_strequ3(line, "cam:"))
			i++;
		free(line);
	}
	close(fd);
}

void		parse_cam(t_rt *r, int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 6)
	{
		if(get_next_line(fd, &line) > 0)
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
		else
			error_read(fd);
	free(line);
	}
}

void		parse_new_light(t_rt *r, int fd)
{
	int		i;
	char	*line;

	i = -1;
	if(!(r->light = (t_light *)malloc(sizeof(t_light))))     //не забыть почистить объект
		error_malloc(fd, line);
	while (++i < 8)
	{
		if(get_next_line(fd, &line) > 0)
		{
			if (ft_strnequ(line, "    light-type:", 15))
				r->light->type = ft_strdup(&line[16]);
			else if(ft_strnequ(line, "    intensity:", 14))
				r->light->intensity = ((double)ft_atoi(&line[15])) / 100;
			else if (ft_strnequ(line, "    point-x:", 12))
				r->light->position.x = ft_atoi(&line[13]);
			else if (ft_strnequ(line, "    point-y:", 12))
				r->light->position.y = ft_atoi(&line[13]);
			else if (ft_strnequ(line, "    point-z:", 12))
				r->light->position.z = ft_atoi(&line[13]);
			else if(ft_strnequ(line, "    direction-x:", 16))
				r->light->direction.x = ft_atoi(&line[17]);
			else if(ft_strnequ(line, "    direction-y:", 16))
				r->light->direction.y = ft_atoi(&line[17]);
			else if(ft_strnequ(line, "    direction-z:", 16))
				r->light->direction.z = ft_atoi(&line[17]);
			else
				error_param(line);
		}
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
	if(!(r->light = (t_light *)malloc(sizeof(t_light))))     //не забыть почистить объект
		error_malloc(fd, line);
	r->light->next = begin;
	while (++i < 8)
	{
		if(get_next_line(fd, &line) > 0)
		{
			if (ft_strnequ(line, "    light-type:", 15))
				r->light->type = ft_strdup(&line[16]);
			else if(ft_strnequ(line, "    intensity:", 14))
				r->light->intensity = ((double)ft_atoi(&line[15])) / 100;
			else if (ft_strnequ(line, "    point-x:", 12))
				r->light->position.x = ft_atoi(&line[13]);
			else if (ft_strnequ(line, "    point-y:", 12))
				r->light->position.y = ft_atoi(&line[13]);
			else if (ft_strnequ(line, "    point-z:", 12))
				r->light->position.z = ft_atoi(&line[13]);
			else if(ft_strnequ(line, "    direction-x:", 16))
				r->light->direction.x = ft_atoi(&line[17]);
			else if(ft_strnequ(line, "    direction-y:", 16))
				r->light->direction.y = ft_atoi(&line[17]);
			else if(ft_strnequ(line, "    direction-z:", 16))
				r->light->direction.z = ft_atoi(&line[17]);
			else
				error_param(line);
		}
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
	int kek = 9;
}

void		check_cone(t_obj *cone)
{
	if (cone->radius < 0.1
	|| cone->color[0] < 0 || cone->color[1] < 0
	|| cone->color < 0)
		error_cone();
}

void		parse_cone(t_rt *r, int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 11)
	{
		if (get_next_line(fd, &line) > 0)
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

void		check_spere(t_obj *spere)
{
	if (spere->radius < 0.1 ||
	spere->color[0] < 0 || spere->color[1] < 0 || spere->color[2] < 0)
		error_spere();
}

void		parse_sphere(t_rt *r, int fd)
{
	int		i;
	char	*line;

	i = -1;
	while(++i < 8)
	{
		if(get_next_line(fd, &line) > 0)
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
		free(line);
	}
	check_spere(&r->obj[r->count]);
	r->obj[r->count].name = "sphere";
	r->count++;
}

void		check_plane(t_obj *plane)
{
	if (plane->color[0] < 0 || plane->color[1] < 0 || plane->color[2] < 0)
		error_plane();
}

void		parse_plane(t_rt *r, int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 10)
	{
		if (get_next_line(fd, &line) > 0)
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
		else
			error_read(fd);
		free(line);
	}
	r->obj[r->count].rot = vec_norm(r->obj[r->count].rot);
	check_plane(&r->obj[r->count]);
	r->obj[r->count].name = "plane";    //??
	r->count++;
}

void		check_cylinder(t_obj *cyl)
{
	if (cyl->color[0] < 0 || cyl->color[1] < 0 || cyl->color[2] < 0 || cyl->radius < 0.1)
		error_cyl();
}

void		parse_cylinder(t_rt *r, int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < 11)
	{
		if (get_next_line(fd, &line) > 0)
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
		else
			error_read(fd);
	free(line);
	}
	r->obj[r->count].rot = vec_norm(r->obj[r->count].rot);
	check_cylinder(&r->obj[r->count]);
	r->obj[r->count].name = "cylinder";    //??
	r->count++;
}


void		parse_param(t_rt *r, char *arg)
{
	int		fd;
	char	*line;

	if ((fd = open(arg, O_RDONLY)) < 0)
		error_open();
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strequ3("cam:", line))
			parse_cam(r, fd);
		else if (ft_strequ3("light:\0", line))
			parse_light(r, fd);
		else if (ft_strequ3("cone:\0", line))
			parse_cone(r, fd);
		else if (ft_strequ3("sphere:\0", line))
			parse_sphere(r, fd);
		else if (ft_strequ3("plane:\0", line))
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

void ft_debuger(t_rt *r)
{
	t_light *nxt;

	nxt = r->light;

	while (nxt)
	{
		printf("%s\n", nxt->type);
		printf("%lf\n", nxt->intensity);
		printf("%lf\n", nxt->position.x);
		printf("%lf\n", nxt->position.y);
		printf("%lf\n", nxt->position.z);
		printf("%lf\n", nxt->direction.x);
		printf("%lf\n", nxt->direction.y);
		printf("%lf\n", nxt->direction.z);
	nxt = nxt->next;
	}
	
}

// int main(int ac, char **av)
// {
// 	t_rt			r;
// 	ft_bzero(&r, sizeof(t_rt));
// 	ft_parser(av[1], &r);
// 	ft_debuger(&r);
// 	exit(0);
// }

//TODO: подумать над универсальным парсером, потому что если есть неиспользуемые параметры, они же просто не считаются?