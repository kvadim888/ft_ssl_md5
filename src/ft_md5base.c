/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 19:04:20 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/25 05:22:44 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const unsigned char	g_pad[64] =
{
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

int							ft_md5calc(const void *data, size_t len,
										unsigned char *digest)
{
	t_md5	*msg;

	msg = ft_md5init();
	if (msg == NULL)
		return (1);
	ft_md5word(msg, data, len);
	ft_md5end(msg, digest);
	ft_memdel((void **)&msg);
	return (0);
}

t_md5						*ft_md5init(void)
{
	t_md5	*msg;

	msg = ft_memalloc(sizeof(t_md5));
	if (msg == NULL)
		return (NULL);
	msg->hash.h[0] = 0x67452301;
	msg->hash.h[1] = 0xEFCDAB89;
	msg->hash.h[2] = 0x98BADCFE;
	msg->hash.h[3] = 0x10325476;
	msg->size = 0;
	msg->total = 0;
	return (msg);
}

void						ft_md5word(t_md5 *msg, const void *data, size_t len)
{
	size_t	n;

	while (len > 0)
	{
		n = 64 - msg->size;
		n = (len < n) ? len : n;
		ft_memcpy((msg->word.buff + msg->size), (unsigned char *)data, n);
		msg->size += n;
		msg->total += n;
		data = (unsigned char *)data + n;
		len -= n;
		if (msg->size == 64)
		{
			ft_md5loop(msg);
			msg->size = 0;
		}
	}
}

void						ft_md5end(t_md5 *msg, unsigned char *dig)
{
	unsigned char		i;
	unsigned long long	total;
	size_t				padsize;

	total = msg->total * 8;
	padsize = 56 - msg->size;
	padsize += (msg->size >= 56) ? 64 : 0;
	ft_md5word(msg, g_pad, padsize);
	msg->word.x[14] = (unsigned int)ft_htol((uintmax_t)total, 4);
	msg->word.x[15] = (unsigned int)ft_htol((uintmax_t)(total >> 32), 4);
	ft_md5loop(msg);
	i = 0;
	while (i < 4)
	{
		msg->hash.h[i] = (unsigned int)ft_htol(msg->hash.h[i], 4);
		i++;
	}
	if (dig != NULL)
		ft_memcpy(dig, msg->hash.dig, MD5_HASHSIZE);
}
