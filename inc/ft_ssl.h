/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 14:30:47 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/16 14:31:24 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

# include <stddef.h>
# include <stdint.h>

# include "ft_md5.h"
# include "ft_sha256.h"
# include "ft_whirlpool.h"
# include "libft.h"

# define FLAG_P		(char)(1 << 0)
# define FLAG_Q		(char)(1 << 1)
# define FLAG_R		(char)(1 << 2)
# define FLAG_S		(char)(1 << 3)

# define ROTL32(val, offset) (((val) << (offset)) | ((val) >> (32 - (offset))))
# define ROTR32(val, offset) (((val) >> (offset)) | ((val) << (32 - (offset))))

# define ROTL64(val, offset) (((val) << (offset)) | ((val) >> (64 - (offset))))
# define ROTR64(val, offset) (((val) >> (offset)) | ((val) << (64 - (offset))))

typedef struct	s_hash
{
	char		*name;
	size_t		hashsize;
	int			(*ft_calc)(const void *data, size_t len, unsigned char *hash);
}				t_hash;


// TODO move to libft
int					ft_endian(void);
unsigned short		ft_swap16(unsigned short val);
unsigned int		ft_swap32(unsigned int val);
unsigned long long	ft_swap64(unsigned long long val);

uintmax_t			ft_htob(uintmax_t host, size_t size);
uintmax_t			ft_btoh(uintmax_t big, size_t size);
uintmax_t			ft_ltoh(uintmax_t little, size_t size);
uintmax_t			ft_htol(uintmax_t host, size_t size);
//

int				ft_flagparse(int ac, char **av, char *flags);

t_hash			ft_hashchoose(char *prog, char *name);
char			*ft_hashtostr(unsigned char *dig, t_hash hash);
void			ft_hashing(int ac, char **av, t_hash hash);
void			ft_display(t_hash hash, char *msg,
											unsigned char *dig, char *flag);
#endif
