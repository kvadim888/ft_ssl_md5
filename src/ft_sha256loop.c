/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 18:55:30 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/25 05:19:53 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_sha256.h"

static const unsigned int	g_k[64] =
{
	0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1,
	0x923F82A4, 0xAB1C5ED5, 0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
	0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174, 0xE49B69C1, 0xEFBE4786,
	0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
	0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147,
	0x06CA6351, 0x14292967, 0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
	0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85, 0xA2BFE8A1, 0xA81A664B,
	0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
	0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A,
	0x5B9CCA4F, 0x682E6FF3, 0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
	0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
};

static void					ft_sha256rnd(int i, t_sha256hash *tmp,
										unsigned int *x)
{
	unsigned int	tmp1;
	unsigned int	tmp2;

	if (i >= 16)
		W(i) += SUM4(W(i + 14)) + W(i + 9) + SUM3(W(i + 1));
	tmp1 = tmp->h[7] + SUM2(tmp->h[4]) +
						CH(tmp->h[4], tmp->h[5], tmp->h[6]) + g_k[i] + W(i);
	tmp2 = SUM1(tmp->h[0]) + M(tmp->h[0], tmp->h[1], tmp->h[2]);
	tmp->h[7] = tmp->h[6];
	tmp->h[6] = tmp->h[5];
	tmp->h[5] = tmp->h[4];
	tmp->h[4] = tmp->h[3] + tmp1;
	tmp->h[3] = tmp->h[2];
	tmp->h[2] = tmp->h[1];
	tmp->h[1] = tmp->h[0];
	tmp->h[0] = tmp1 + tmp2;
}

void						ft_sha256loop(t_sha256 *msg)
{
	int				i;
	unsigned int	*x;
	t_sha256hash	tmp;

	i = -1;
	while (++i < 8)
		tmp.h[i] = msg->hash.h[i];
	x = msg->word.x;
	i = -1;
	while (++i < 16)
		x[i] = (unsigned int)ft_btoh(x[i], sizeof(unsigned int));
	i = -1;
	while (++i < 64)
		ft_sha256rnd(i, &tmp, x);
	i = -1;
	while (++i < 8)
		msg->hash.h[i] += tmp.h[i];
}
