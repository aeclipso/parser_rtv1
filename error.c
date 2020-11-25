/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeclipso <aeclipso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 04:06:41 by aeclipso          #+#    #+#             */
/*   Updated: 2020/11/24 04:07:39 by aeclipso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
