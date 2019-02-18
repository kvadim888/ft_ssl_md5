/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 05:00:06 by vkryvono          #+#    #+#             */
/*   Updated: 2018/10/23 05:00:09 by vkryvono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_hash			ft_hashchoose(char *prog, char *name)
{
	t_hash	hash[3];
	int		i;

	hash[0] = (t_hash){"md5", MD5_HASHSIZE, ft_md5calc};
	hash[1] = (t_hash){"sha256", SHA256_HASHSIZE, ft_sha256calc};
	hash[2] = (t_hash){"whirlpool", WHIRLPOOL_HASHSIZE, ft_whirlpoolcalc};
	//hash[3] = (t_hash){"keccak", KECCAK_HASHSIZE, ft_keccakcalc};
	i = 0;
	while (i < 3 && !(ft_strequ(hash[i].name, name)))
		i++;
	if (i == 3)
	{
		ft_printf("%s: Error: %s is an invalid command.\n", prog, name);
		ft_printf("\n");
		ft_printf("Standard commands:\n\n");
		ft_printf("Message Digest commands:\n");
		i = 0;
		while (i < 3)
			ft_printf("%s\n", hash[i++].name);
		ft_printf("\n");
		ft_printf("Cipher commands:\n");
		ft_printf("\n");
		exit(1);
	}
	return (hash[i]);
}

static int		ft_hashstr(t_hash hash, char *str,
										unsigned char *dig, char *flags)
{
	long	len;

	len = ft_strlen(str);
	hash.ft_calc(str, (size_t)len, dig);
	ft_display(hash, str, dig, flags);
	return (0);
}

static int		ft_hashfile(t_hash hash, char *path,
										unsigned char *dig, char *flags)
{
	char	*file;
	long	len;

	file = NULL;
	if (ft_isdir(path))
	{
		ft_printf("%s: %s: Is a directory\n", hash.name, path);
		return (1);
	}
	len = ft_getfile(path, &file);
	if (len < 0)
		return (1);
	hash.ft_calc(file, (size_t)len, dig);
	ft_display(hash, path, dig, flags);
	ft_strdel(&file);
	return (0);
}

static int		ft_hashstdin(t_hash hash, unsigned char *dig, char *flags)
{
	long	len;
	char	*str;

	len = ft_getstdin(&str);
	hash.ft_calc(str, (size_t)len, dig);
	if (*flags & FLAG_P)
		ft_printf("%s", str);
	*flags &= ~FLAG_P;
	ft_strdel(&str);
	str = ft_hashtostr(dig, hash);
	ft_printf("%s\n", str);
	ft_strdel(&str);
	return (0);
}

void			ft_hashing(int ac, char **av, t_hash hash)
{
	int				i;
	unsigned char	*dig;
	char			flags;

	dig = (unsigned char *)ft_memalloc(hash.hashsize * sizeof(unsigned char));
	flags = 0;
	i = ft_flagparse(ac, av, &flags);
	if ((flags & FLAG_P) || i == ac)
		ft_hashstdin(hash, dig, &flags);
	while (i < ac)
	{
		if (!(flags & FLAG_S) && ft_isfile(av[i]))
			ft_hashfile(hash, av[i], dig, &flags);
		else if (flags & FLAG_S)
			ft_hashstr(hash, av[i], dig, &flags);
		else
			ft_printf("ft_ssl: %s: No such file or directory\n", av[0], av[i]);
		i++;
	}
	ft_memdel((void **)&dig);
}
