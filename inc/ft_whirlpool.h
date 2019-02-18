/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whirlpool.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 06:49:18 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/23 06:49:25 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WHIRLPOOL_H
# define FT_WHIRLPOOL_H

# include <stddef.h>
# include <stdint.h>

# define WHIRLPOOL_HASHSIZE 64
# define WHIRLPOOL_BUFFSIZE	64

typedef union			s_whirlpoolhash
{
	unsigned long long	h[8];
	unsigned char		dig[WHIRLPOOL_HASHSIZE];
}						t_whirlpoolhash;

typedef union			s_whirlpoolword
{
	unsigned long long	x[8];
	unsigned char		buff[WHIRLPOOL_BUFFSIZE];
}						t_whirlpoolword;

typedef	struct			s_whirlpool
{
	t_whirlpoolhash		hash;
	t_whirlpoolword		word;
	size_t				size;
	unsigned long long	total;
	unsigned long long	k[8];
	unsigned long long	l[8];
	unsigned long long	state[8];
}						t_whirlpool;

t_whirlpool				*ft_whirlpoolinit(void);
int						ft_whirlpoolcalc(const void *data, size_t len,
										unsigned char *digest);
void					ft_whirlpoolword(t_whirlpool *msg, const void *data,
										size_t len);
void					ft_whirlpoolloop(t_whirlpool *msg);
void					ft_whirlpoolend(t_whirlpool *message,
										unsigned char *digest);

#endif
