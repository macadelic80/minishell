/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-azz <aben-azz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 04:41:17 by aben-azz          #+#    #+#             */
/*   Updated: 2019/03/28 04:49:21 by aben-azz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		ft_setenv(t_data *data)
{
	if (!data->argv[1])
		return (ft_env(data));
	else if (data->argv[2] && data->argv[3])
		return (ft_printf("setenv: Too many arguments.") > 0);
	set_env_var(data->argv[1], data->argv[2]);
	return (0);
}

char	**realloc_env(int new_size)
{
	char	**new;
	int		i;

	new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1));
	i = -1;
	while (g_env[++i] && i < new_size)
	{
		new[i] = ft_strdup(g_env[i]);
		free(g_env[i]);
	}
	free(g_env);
	return (new);
}

void	set_env_var(char *key, char *value)
{
	int		index;
	char	*tmp;

	tmp = ft_strjoin("=", value);
	if (~(index = get_env_index(key)))
	{
		if (g_env[index])
			free(g_env[index]);
		else
			g_env = realloc_env(index + 1);
		g_env[index] = ft_strjoin(key, value ? tmp : "=");
	}
	else
		ft_printf("setenv: value: %s does not exist\n", key);
	free(tmp);
}