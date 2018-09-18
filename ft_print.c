/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smbonan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 08:57:18 by smbonan           #+#    #+#             */
/*   Updated: 2018/08/31 09:14:03 by smbonan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_print_tree(t_btree *tree, t_dir *d)
{
	if (tree->left)
		ft_print_tree(tree->left, d);
	if (d->opt[0] == 1)
	{
		tree->line_list = ft_strnew(1024);
		ft_padding(tree->line_list, tree->long_list, d->max_len);
		ft_putendl(tree->line_list);
		free(tree->line_list);
	}
	else
		ft_putendl(tree->name);
	if (tree->right)
		ft_print_tree(tree->right, d);
}

void				ft_print_tree_rev(t_btree *tree, t_dir *d)
{
	if (tree->right)
		ft_print_tree_rev(tree->right, d);
	if (d->opt[0] == 1)
	{
		tree->line_list = ft_strnew(1024);
		ft_padding(tree->line_list, tree->long_list, d->max_len);
		ft_putendl(tree->line_list);
		free(tree->line_list);
	}
	else
		ft_putendl(tree->name);
	if (tree->left)
		ft_print_tree_rev(tree->left, d);
}

void				ft_print_error(t_dir *d, char *current, char *name)
{
	char			*tmp;

	tmp = ft_strnew(ft_strlen(name) + 5);
	ft_strcpy(tmp, "ls: ");
	ft_strcpy(&tmp[ft_strlen(tmp)], name);
	if (errno == 2)
		perror(tmp);
	if (errno == 13)
	{
		if (d->first_result == 1)
		{
			ft_putstr("\n");
			ft_create_path(d->path, current, name);
			ft_putstr(d->path);
			ft_putstr(":\n");
			if (d->dil == 1)
				ft_perm_error(d);
		}
		else
		{
			if (d->dil == 1)
				ft_perm_error(d);
		}
		perror(tmp);
	}
	if (!d->node || d->dil != 0)
	{
		if (d->first_result == 1)
		{
			ft_putstr("\n");
			ft_create_path(d->path, current, name);
			ft_putstr(d->path);
			ft_putstr(":\n");
		}
	}
	free(tmp);
}

void				ft_print(t_dir *d, char *current)
{
	if (d->first_result == 1 || (d->opt[1] == 1 && d->first_result == 1))
	{
		ft_putstr("\n");
		ft_putstr(current);
		ft_putstr(":\n");
	}
	d->first_result = 1;
	if (d->opt[0] == 1)
	{
		ft_putstr("total ");
		ft_putnbr(d->blocksize);
		ft_putstr("\n");
	}
	if (d->opt[3] == 0)
		ft_print_tree(d->node, d);
	else
		ft_print_tree_rev(d->node, d);
}
