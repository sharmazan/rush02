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

	i = 0;
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

int	main(int argc, char **argv)
{
	t_dict	*dict;

	if (argc > 3 || argc < 2)
	{
		write_error();
		return (1);
	}
	if (!check_input(argv[argc - 1]))
		return (1);
	if (argc == 2)
		dict = parse_dict("numbers.dict");
	else
		dict = parse_dict(argv[1]);
	if (!dict)
	{
		write_dict_error();
		return (1);
	}
	convert_number(argv[argc - 1], dict);
	ft_putchar('\n');
	free_dict(dict);
	return (0);
}
