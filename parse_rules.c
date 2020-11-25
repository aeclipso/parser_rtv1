/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeclipso <aeclipso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 06:28:38 by aeclipso          #+#    #+#             */
/*   Updated: 2020/11/24 06:37:42 by aeclipso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			space_end(char *line)
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
	if (ft_strequ(line, "cone:") || ft_strequ(line, "sphere:")
		|| ft_strequ(line, "plane:") || ft_strequ(line, "cylinder:")
		|| ft_strequ(line, "cam:") || ft_strequ(line, "light:"))
	{
		return (1);
	}
	else if (ws_count(line) == 4)
		return (1);
	else
		error_param(line);
	return (0);
}

int			valid_line(char *line)
{
	if (space_end(line) && space_before(line) && check_param(line))
		return (1);
	return (0);
}
