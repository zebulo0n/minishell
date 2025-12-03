/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoeschne <zoeschne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:25:28 by zoeschne          #+#    #+#             */
/*   Updated: 2025/11/07 10:34:06 by zoeschne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_ideal(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[0] = '-';
	i = 1;
	while (i < len)
	{
		str[i] = 'n';
		i++;
	}
	str[len] = '\0';
	return (str);
}

bool	has_newline(char **args, int *i)
{
	char	*good_str;

	good_str = create_ideal(args[*i]);
	if (strict_strcmp(good_str, args[*i]) != 0)
	{
		free(good_str);
		return (true);
	}
	free(good_str);
	(*i)++;
	while (args[*i])
	{
		good_str = create_ideal(args[*i]);
		if (strict_strcmp(good_str, args[*i]) != 0)
		{
			free(good_str);
			return (false);
		}
		free(good_str);
		(*i)++;
	}
	return (false);
}

int	exec_echo(char **args)
{
	int (i) = 1;
	bool (newline) = true;
	if (args[i])
	{
		if (has_newline(args, &i) == false)
		{
			if (!args[2])
				return (0);
			newline = false;
		}
		if (args[i])
		{
			if (args[i + 1])
			{
				while (args[i + 1])
					printf("%s ", args[i++]);
			}
			printf("%s", args[i]);
		}
	}
	if (newline == true)
		printf("\n");
	return (0);
}
