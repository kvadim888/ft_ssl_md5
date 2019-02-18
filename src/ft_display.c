/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 05:48:25 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/22 05:48:28 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*ft_hashtostr(unsigned char *dig, t_hash hash)
{
	char		*str;
	char		buff[3];
	size_t		i;

	str = ft_strnew(hash.hashsize * 2);
	i = 0;
	while (i < hash.hashsize)
	{
		ft_bzero(buff, 3);
		ft_sprintf(buff, "%.2x", dig[i]);
		str = ft_strcat(str, buff);
		i++;
	}
	return (str);
}

void	ft_display(t_hash hash, char *msg, unsigned char *dig, char *flag)
{
	char	*str;
	char	*name;
	char	*tmp;

	str = ft_hashtostr(dig, hash);
	name = ft_strtoupper(hash.name);
	if (*flag & FLAG_S)
	{
		tmp = ft_strnew(ft_strlen((const char *)msg) + 2);
		ft_sprintf(tmp, "\"%s\"", msg);
		*flag &= ~FLAG_S;
	}
	else
		tmp = msg;
	if (*flag & FLAG_Q)
		ft_printf("%s\n", str);
	else if (*flag & FLAG_R)
		ft_printf("%s %s\n", str, tmp);
	else
		ft_printf("%s (%s) = %s\n", name, tmp, str);
	ft_strdel(&str);
	if (tmp != msg)
		ft_strdel(&tmp);
	ft_strdel(&name);
}
