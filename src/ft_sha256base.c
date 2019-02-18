/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 19:31:21 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/25 05:25:54 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const unsigned char	g_pad[64] =
{
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

int							ft_sha256calc(const void *data, size_t len,
											unsigned char *dig)
{
	t_sha256	*msg;

	msg = ft_memalloc(sizeof(t_sha256));
	if (msg == NULL)
		return (1);
	ft_sha256init(msg);
	ft_sha256word(msg, data, len);
	ft_sha256end(msg, dig);
	ft_memdel((void **)&msg);
	return (0);
}

void						ft_sha256init(t_sha256 *msg)
{
	msg->hash.h[0] = 0x6A09E667;
	msg->hash.h[1] = 0xBB67AE85;
	msg->hash.h[2] = 0x3C6EF372;
	msg->hash.h[3] = 0xA54FF53A;
	msg->hash.h[4] = 0x510E527F;
	msg->hash.h[5] = 0x9B05688C;
	msg->hash.h[6] = 0x1F83D9AB;
	msg->hash.h[7] = 0x5BE0CD19;
	msg->size = 0;
	msg->total = 0;
}

void						ft_sha256word(t_sha256 *msg, const void *data,
											size_t len)
{
	size_t	n;

	while (len > 0)
	{
		n = 64 - msg->size;
		n = (len < n) ? len : n;
		ft_memcpy((msg->word.buff + msg->size), data, n);
		msg->size += n;
		msg->total += n;
		data = (unsigned char *)data + n;
		len -= n;
		if (msg->size == 64)
		{
			ft_sha256loop(msg);
			msg->size = 0;
		}
	}
}

void						ft_sha256end(t_sha256 *msg, unsigned char *dig)
{
	int						i;
	unsigned long long		total;
	size_t					padsize;

	total = msg->total * 8;
	padsize = 56 - msg->size;
	padsize += (msg->size >= 56) ? 64 : 0;
	ft_sha256word(msg, g_pad, padsize);
	msg->word.x[14] = (unsigned int)ft_htob((total >> 32), 4);
	msg->word.x[15] = (unsigned int)ft_htob(total, 4);
	ft_sha256loop(msg);
	i = -1;
	while (++i < 8)
		msg->hash.h[i] = (unsigned int)ft_htob(msg->hash.h[i], 4);
	if (dig != NULL)
		ft_memcpy(dig, msg->hash.dig, SHA256_HASHSIZE);
}
