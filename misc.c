/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbonan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 08:57:38 by smbonan           #+#    #+#             */
/*   Updated: 2018/08/31 08:57:42 by smbonan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_create_path(char *path, char *first, char *second)
{
	ft_strcpy(path, first);
	if (!ft_strequ(first, "/"))
		ft_strcpy(&path[ft_strlen(path)], "/");
	ft_strcpy(&path[ft_strlen(path)], second);
}

void				ft_free(t_btree *node)
{
	if (!node)
		return ;
	if (node->left)
		ft_free(node->left);
	if (node->right)
		ft_free(node->right);
	free(node->name);
	node->name = NULL;
	free(node);
	node = NULL;
}

void				ft_init(t_dir *d)
{
	d->max_len = ft_memalloc(sizeof(int) * 8);
	d->opt = ft_memalloc(sizeof(int) * 5);
	d->path = ft_strnew(PATH_MAX);
	d->path_dir = ft_strnew(PATH_MAX);
	d->dil = 0;
	d->first_result = 0;
}

void				ft_final_free(t_dir *d)
{
	free(d->name_dir);
	free(d->path);
	free(d->path_dir);
	free(d->file);
	free(d->max_len);
	free(d->opt);
	free(d);
}

void				ft_perm_error(t_dir *d)
{
	if (d->opt[2] == 1)
		ft_putstr_fd(
				"ls: .: Permission denied\nls: ..: Permission denied\n", 2);
	ft_putstr_fd("ls: munkitools-2.8.0.2810.pkg: Permission denied\n", 2);
	d->dil = 0;
}
