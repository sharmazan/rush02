#include "rush02.h"

void	convert_hundreds(int num, t_dict *dict, int *first)
{
	char	key[4];
	char	*value;
	int		hundreds;

	if (num >= 100)
	{
		hundreds = num / 100;
		key[0] = hundreds + '0';
		key[1] = '\0';
		value = find_value(key, dict);
		if (value)
		{
			if (!*first)
				ft_putchar(' ');
			ft_putstr(value);
			*first = 0;
		}
		value = find_value("100", dict);
		if (value)
		{
			ft_putchar(' ');
			ft_putstr(value);
		}
		num %= 100;
	}
	if (num >= 20)
	{
		key[0] = (num / 10) + '0';
		key[1] = '0';
		key[2] = '\0';
		value = find_value(key, dict);
		if (value)
		{
			if (!*first)
				ft_putchar(' ');
			ft_putstr(value);
			*first = 0;
		}
		num %= 10;
	}
	if (num > 0)
	{
		key[0] = num + '0';
		key[1] = '\0';
		value = find_value(key, dict);
		if (value)
		{
			if (!*first)
				ft_putchar(' ');
			ft_putstr(value);
			*first = 0;
		}
	}
}

void	convert_number(char *number, t_dict *dict)
{
	int		len;
	char	*value;
	int		first;

	len = ft_strlen(number);
	first = 1;
	
	if (len == 1 && number[0] == '0')
	{
		value = find_value("0", dict);
		if (value)
			ft_putstr(value);
		return;
	}
	
	// Simple implementation for numbers up to 999
	if (len <= 3)
	{
		int num = 0;
		int i = 0;
		while (number[i])
		{
			num = num * 10 + (number[i] - '0');
			i++;
		}
		convert_hundreds(num, dict, &first);
	}
	else
	{
		write_error();
	}
}
