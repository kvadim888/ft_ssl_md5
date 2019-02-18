/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 21:21:42 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/19 21:26:20 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include <stddef.h>
# include <stdint.h>
# include <limits.h>

# define MD5_HASHSIZE	16
# define MD5_BUFFSIZE	64

# define A(x, y, z) (((x) & (y)) | (~(x) & (z)))
# define B(x, y, z) (((x) & (z)) | ((y) & ~(z)))
# define C(x, y, z) ((x) ^ (y) ^ (z))
# define D(x, y, z) ((y) ^ ((x) | ~(z)))

# define R1(a, b, c, d, x, s, k) a = ROTL32(a + A(b, c, d) + (x) + (k), s) + (b)
# define R2(a, b, c, d, x, s, k) a = ROTL32(a + B(b, c, d) + (x) + (k), s) + (b)
# define R3(a, b, c, d, x, s, k) a = ROTL32(a + C(b, c, d) + (x) + (k), s) + (b)
# define R4(a, b, c, d, x, s, k) a = ROTL32(a + D(b, c, d) + (x) + (k), s) + (b)

typedef union			s_md5hash
{
	unsigned int		h[4];
	unsigned char		dig[MD5_HASHSIZE];
}						t_md5hash;

typedef union			s_md5word
{
	unsigned int		x[16];
	unsigned char		buff[MD5_BUFFSIZE];
}						t_md5word;

typedef	struct			s_md5
{
	t_md5hash			hash;
	t_md5word			word;
	size_t				size;
	unsigned long long	total;
}						t_md5;

t_md5	*ft_md5init(void);
int		ft_md5calc(const void *data, size_t len, unsigned char *dig);
void	ft_md5word(t_md5 *msg, const void *data, size_t len);
void	ft_md5loop(t_md5 *msg);
void	ft_md5end(t_md5 *msg, unsigned char *dig);

#endif
