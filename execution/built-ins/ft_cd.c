/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:08:59 by waelhamd          #+#    #+#             */
/*   Updated: 2022/09/11 01:28:57 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_getenv(t_env *envirement, char *name)
{
	t_env	*env;

	env = envirement;
	while (env)
	{
		if (!ft_strcmp(name, env->name))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

static int	argument_dir(char *path, t_env *env)
{
	char	*str;
	char	*current;

	current = getcwd(NULL, 0);
	if (!current)
	{
		perror("cd: error retrieving current directory: \
				getcwd: cannot access parent directories");
		return (chdir(path));
	}
	else if (!ft_strcmp(path, "-"))
	{
		str = ft_getenv(env, "OLDPWD");
		if (!str)
		{
			g_exit_status = 1;
			printf("cd: OLDPWD not set\n");
			return (free(current), 0);
		}
		else
			return (free(current), printf("%s\n", str), chdir(str), 0);
	}
	else
		return (free(current), chdir(path));
	return (free(current), -1);
}

char	*get_pwd_env(t_env *list)
{
	t_env	*tmp;
	char	*pwd;

	tmp = list;
	pwd = NULL;
	while (tmp)
	{
		if (!ft_strcmp (tmp->name, "PWD"))
			pwd = ft_strdup (tmp->content);
		tmp = tmp->next;
	}
	return (pwd);
}

int	update_pwd_env(t_env **env)
{
	char	*current;
	t_env	*tmp;

	tmp = *env;
	current = getcwd(NULL, 0);
	if (!current)
		return (0);
	while (tmp)
	{
		if (!ft_strcmp (tmp->name, "PWD") || !ft_strcmp (tmp->name, "OLDPWD"))
		{
			free(tmp->content);
			if (!ft_strcmp (tmp->name, "PWD"))
				tmp->content = current;
			else
				tmp->content = get_pwd_env(*env);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	ft_cd(char **cmd, t_env *env)
{
	int		i;
	char	*path;

	i = -1;
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
	{
		path = ft_getenv(env, "HOME");
		if (!path)
		{
			g_exit_status = 1;
			printf("cd: HOME not set\n");
		}
		else
			i = chdir(path);
	}
	else
		i = argument_dir(cmd[1], env);
	if (i < 0)
	{
		g_exit_status = 1;
		perror("cd");
	}
	update_pwd_env(&env);
}
