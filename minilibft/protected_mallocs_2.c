/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_mallocs_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:24:15 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:24:16 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*safe_strjoin(t_minishell *ms, char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
		error_handler(ms, string_array(ms, "strjoin", NULL, NULL), errno, true);
	ft_memcpy(res, s1, len1);
	ft_memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	return (res);
}

char	*safe_substr(t_minishell *ms, char const *s, unsigned int start,
		size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	sub_len;
	char	*sub;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		sub = malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	sub_len = s_len - start;
	if (sub_len > len)
		sub_len = len;
	sub = (char *)malloc(sizeof(char) * (sub_len + 1));
	if (!sub)
		error_handler(ms, string_array(ms, "substr", NULL, NULL), errno, true);
	i = 0;
	while (i < sub_len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

/* LISTE DES FONCTIONS UTILISÉES

--> penser à regarder aussi la minilibft

fonctions avec malloc :
ft_strjoin
ft_itoa
ft_substr

fonctions sans malloc :
ft_putstr_fd
ft_strlen
ft_isdigit
ft_isalpha
ft_isalnum
ft_strchr
ft_memcpy
ft_strnstr

*/
