/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_not_in_libft.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:24:11 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:24:12 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	x;

	x = 0;
	if (!s1 || !s2 || !s1[x] || !s2[x])
		return (-1);
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0')
		x++;
	return (s1[x] - s2[x]);
}

char	*ft_strjoin_three(t_minishell *ms, char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*result;

	tmp = safe_strjoin(ms, s1, s2);
	if (!tmp)
		error_handler(ms, string_array(ms, "strjoin_three", NULL, NULL), errno,
			true);
	result = safe_strjoin(ms, tmp, s3);
	if (!result)
		error_handler(ms, string_array(ms, "strjoin_three", NULL, NULL), errno,
			true);
	free(tmp);
	return (result);
}

int	strict_strcmp(char *s1, char *s2)
{
	int	x;

	x = 0;
	if (!s1 || !s2 || !s1[x] || !s2[x])
		return (-1);
	while (s1[x] == s2[x] && s1[x] != '\0' && s2[x] != '\0')
		x++;
	return (s1[x] - s2[x]);
}

int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	else
		return (nb);
}
