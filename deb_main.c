/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deb_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeclipso <aeclipso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 06:31:37 by aeclipso          #+#    #+#             */
/*   Updated: 2020/11/24 06:33:36 by aeclipso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void            ft_debuger(t_rt *r)
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

int main(int ac, char **av)
{
	t_rt			r;
	ft_bzero(&r, sizeof(t_rt));
	ft_parser(av[1], &r);
	ft_debuger(&r);
	exit(0);
}