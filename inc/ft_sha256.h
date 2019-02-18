/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 19:32:14 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/20 19:32:20 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
# define FT_SHA256_H

# include <stddef.h>
# include <stdint.h>

# define SHA256_HASHSIZE	32
# define SHA256_BUFFSIZE	64

# define W(t) x[(t) & 0x0f]
# define CH(x, y, z) (((x) & (y)) | (~(x) & (z)))
# define M(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))

# define SUM1(x) (ROTR32(x, 2) ^ ROTR32(x, 13) ^ ROTR32(x, 22))
# define SUM2(x) (ROTR32(x, 6) ^ ROTR32(x, 11) ^ ROTR32(x, 25))
# define SUM3(x) (ROTR32(x, 7) ^ ROTR32(x, 18) ^ ((x) >> (3)))
# define SUM4(x) (ROTR32(x, 17) ^ ROTR32(x, 19) ^ ((x) >> (10)))

typedef union			s_sha256hash
{
	unsigned int		h[8];
	unsigned char		dig[SHA256_HASHSIZE];
}						t_sha256hash;

typedef union			s_sha256word
{
	unsigned int		x[16];
	unsigned char		buff[SHA256_BUFFSIZE];
}						t_sha256word;

typedef	struct			s_sha256
{
	t_sha256hash		hash;
	t_sha256word		word;
	size_t				size;
	unsigned long long	total;
}						t_sha256;

int		ft_sha256calc(const void *data, size_t len, unsigned char *dig);
void	ft_sha256init(t_sha256 *msg);
void	ft_sha256word(t_sha256 *msg, const void *data, size_t len);
void	ft_sha256loop(t_sha256 *msg);
void	ft_sha256end(t_sha256 *msg, unsigned char *dig);

#endif
