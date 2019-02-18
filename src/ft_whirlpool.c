/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whirlpool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 06:31:33 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/25 05:25:56 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_whirlpool.h"

static const unsigned char	g_pad[64] =
{
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

int							ft_whirlpoolcalc(const void *data, size_t len,
												unsigned char *digest)
{
	t_whirlpool		*msg;

	msg = ft_whirlpoolinit();
	if (msg == NULL)
		return (1);
	ft_whirlpoolword(msg, data, len);
	ft_whirlpoolend(msg, digest);
	ft_memdel((void **)&msg);
	return (0);
}

t_whirlpool					*ft_whirlpoolinit(void)
{
	t_whirlpool		*msg;
	size_t			i;

	msg = ft_memalloc(sizeof(t_whirlpool));
	i = 0;
	while (i < 8)
		msg->hash.h[i++] = 0;
	msg->size = 0;
	msg->total = 0;
	return (msg);
}

void						ft_whirlpoolword(t_whirlpool *msg,
												const void *data, size_t len)
{
	size_t n;

	while (len > 0)
	{
		n = 64 - msg->size;
		n = (n > len) ? len : n;
		ft_memcpy(msg->word.buff + msg->size, data, n);
		msg->size += n;
		msg->total += n;
		data = (unsigned char *)data + n;
		len -= n;
		if (msg->size == 64)
		{
			ft_whirlpoolloop(msg);
			msg->size = 0;
		}
	}
}

void						ft_whirlpoolend(t_whirlpool *msg,
											unsigned char *digest)
{
	int					i;
	size_t				padsize;
	unsigned long long	total;

	total = msg->total * 8;
	if (msg->size < 32)
		padsize = 32 - msg->size;
	else
		padsize = 64 + 32 - msg->size;
	ft_whirlpoolword(msg, g_pad, padsize);
	msg->word.x[4] = 0;
	msg->word.x[5] = 0;
	msg->word.x[6] = 0;
	msg->word.x[7] = ft_htob(total, sizeof(long long));
	ft_whirlpoolloop(msg);
	i = -1;
	while (++i < 8)
		msg->hash.h[i] = ft_htob(msg->hash.h[i], sizeof(long long));
	if (digest != NULL)
		ft_memcpy(digest, msg->hash.dig, WHIRLPOOL_HASHSIZE);
}
