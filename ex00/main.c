/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsirelkh <hsirelkh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:29:15 by hsirelkh          #+#    #+#             */
/*   Updated: 2025/09/06 20:43:08 by hsirelkh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"
#include <stdlib.h>
#include <unistd.h>

void	write_error(void)
{
	write(1, "Error\n", 6);
}

void	write_dict_error(void)
{
	write(1, "Dict Error\n", 12);
}

int check_input(char *input)
{
	int	i;

	while (input[i])
	{
		if (!ft_isdigit(input[i]))
		{
			write_error();
			return (0);
		}
		i++;
	}
	return (1);
}

char	*find_value(char *key, t_dict *dict)
{
	t_dict	*cur;

	cur = dict;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_dict	*dict;
	t_dict	*cur;

	if (argc > 3 || argc < 2)
	{
		write_error();
		return (1);
	}
	if (!check_input(argv[argc - 1]))
		return (1);
	if (argc == 2)
		dict = parse_dict("numbers.txt");
	else
		dict = parse_dict(argv[1]);
	if (!dict)
		write_dict_error();
	cur = dict;
	while (cur)
	{
		ft_putstr("Key: ");
		ft_putstr(cur->key);
		ft_putstr(" | Value: ");
		ft_putstr(cur->value);
		ft_putchar('\n');
		cur = cur->next;
	}
	free_dict(dict);
	return (0);
}
