/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:22:22 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/16 14:27:02 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <stdio.h>

int		ft_flagparse(int ac, char **av, char *flags)
{
	int		i;
	int		stat;

	i = 2;
	while (i < ac)
	{
		if ((stat = ft_strequ(av[i], "-p")) == 1)
			*flags |= FLAG_P;
		else if ((stat = ft_strequ(av[i], "-q")) == 1)
			*flags |= FLAG_Q;
		else if ((stat = ft_strequ(av[i], "-r")) == 1)
			*flags |= FLAG_R;
		else if ((stat = ft_strequ(av[i], "-s")) == 1)
		{
			*flags |= FLAG_S;
			return (i + stat);
		}
		else
			return (i);
		i += stat;
	}
	return (i);
}

int		main(int ac, char **av)
{
	t_hash		hash;

	if (ac < 1)
		ft_printf("usage: %s command [command opts] [command args]\n", av[0]);
	else
	{
		hash = ft_hashchoose(av[0], av[1]);
		ft_hashing(ac, av, hash);
	}
//	system("leaks ft_ssl");
	return (0);
}
