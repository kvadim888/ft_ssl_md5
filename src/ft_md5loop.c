/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 22:37:48 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/25 05:22:38 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		ft_md5rnd1(t_md5hash *tmp, const unsigned int *x)
{
	const int	noise[16] = {0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE,
							0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501,
							0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE,
							0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821};

	R1(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[0], 7, noise[0]);
	R1(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[1], 12, noise[1]);
	R1(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[2], 17, noise[2]);
	R1(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[3], 22, noise[3]);
	R1(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[4], 7, noise[4]);
	R1(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[5], 12, noise[5]);
	R1(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[6], 17, noise[6]);
	R1(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[7], 22, noise[7]);
	R1(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[8], 7, noise[8]);
	R1(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[9], 12, noise[9]);
	R1(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[10], 17, noise[10]);
	R1(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[11], 22, noise[11]);
	R1(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[12], 7, noise[12]);
	R1(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[13], 12, noise[13]);
	R1(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[14], 17, noise[14]);
	R1(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[15], 22, noise[15]);
}

static void		ft_md5rnd2(t_md5hash *tmp, const unsigned int *x)
{
	const int	noise[16] = {0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA,
							0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8,
							0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED,
							0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A};

	R2(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[1], 5, noise[0]);
	R2(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[6], 9, noise[1]);
	R2(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[11], 14, noise[2]);
	R2(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[0], 20, noise[3]);
	R2(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[5], 5, noise[4]);
	R2(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[10], 9, noise[5]);
	R2(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[15], 14, noise[6]);
	R2(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[4], 20, noise[7]);
	R2(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[9], 5, noise[8]);
	R2(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[14], 9, noise[9]);
	R2(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[3], 14, noise[10]);
	R2(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[8], 20, noise[11]);
	R2(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[13], 5, noise[12]);
	R2(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[2], 9, noise[13]);
	R2(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[7], 14, noise[14]);
	R2(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[12], 20, noise[15]);
}

static void		ft_md5rnd3(t_md5hash *tmp, const unsigned int *x)
{
	const int	noise[16] = {0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C,
							0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70,
							0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x04881D05,
							0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665};

	R3(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[5], 4, noise[0]);
	R3(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[8], 11, noise[1]);
	R3(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[11], 16, noise[2]);
	R3(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[14], 23, noise[3]);
	R3(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[1], 4, noise[4]);
	R3(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[4], 11, noise[5]);
	R3(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[7], 16, noise[6]);
	R3(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[10], 23, noise[7]);
	R3(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[13], 4, noise[8]);
	R3(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[0], 11, noise[9]);
	R3(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[3], 16, noise[10]);
	R3(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[6], 23, noise[11]);
	R3(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[9], 4, noise[12]);
	R3(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[12], 11, noise[13]);
	R3(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[15], 16, noise[14]);
	R3(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[2], 23, noise[15]);
}

static void		ft_md5rnd4(t_md5hash *tmp, const unsigned int *x)
{
	const int	noise[16] = {0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039,
							0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1,
							0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1,
							0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391};

	R4(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[0], 6, noise[0]);
	R4(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[7], 10, noise[1]);
	R4(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[14], 15, noise[2]);
	R4(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[5], 21, noise[3]);
	R4(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[12], 6, noise[4]);
	R4(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[3], 10, noise[5]);
	R4(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[10], 15, noise[6]);
	R4(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[1], 21, noise[7]);
	R4(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[8], 6, noise[8]);
	R4(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[15], 10, noise[9]);
	R4(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[6], 15, noise[10]);
	R4(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[13], 21, noise[11]);
	R4(tmp->h[0], tmp->h[1], tmp->h[2], tmp->h[3], x[4], 6, noise[12]);
	R4(tmp->h[3], tmp->h[0], tmp->h[1], tmp->h[2], x[11], 10, noise[13]);
	R4(tmp->h[2], tmp->h[3], tmp->h[0], tmp->h[1], x[2], 15, noise[14]);
	R4(tmp->h[1], tmp->h[2], tmp->h[3], tmp->h[0], x[9], 21, noise[15]);
}

void			ft_md5loop(t_md5 *context)
{
	int				i;
	unsigned int	*x;
	t_md5hash		tmp;

	i = -1;
	while (++i < 4)
		tmp.h[i] = context->hash.h[i];
	x = context->word.x;
	i = 0;
	while (i < 16)
	{
		x[i] = (unsigned int)ft_ltoh(x[i], sizeof(x[i]));
		i++;
	}
	ft_md5rnd1(&tmp, x);
	ft_md5rnd2(&tmp, x);
	ft_md5rnd3(&tmp, x);
	ft_md5rnd4(&tmp, x);
	i = -1;
	while (++i < 4)
		context->hash.h[i] += tmp.h[i];
}
