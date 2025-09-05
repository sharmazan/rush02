#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct dictionary
{
    char *number;
    char *wording;
    size_t len;
    struct dictionary *prev;
    struct dictionary *next;
};

int count_len(char *str)
{
    int count = 0;
    while (str[count])
    {
        count++;
    }
    return (count);
}

void print_digit(char c, int position, struct dictionary *dict)
{
    int digit = c - '0';
    char *word = dict[digit].wording;
    write(1, word, strlen(word));
    if (position > 1)
        write(1, " ", 1);
}

void print_number(char *str, struct dictionary *dict)
{
    int len = count_len(str);
    print_digit(str[0], len, dict);
    if (*(str + 1))
        print_number(str + 1, dict);
}

int is_number(char *str)
{
    while (*str)
    {
        if (*str < '0' || *str > '9')
            return (0);
        str++;
    }
    return (1);
}

int main(int ac, char **av)
{
    struct dictionary dict[100];
    dict[0].number = "0";
    dict[0].wording = "zero";
    dict[0].len = 1;
    dict[0].prev = NULL;
    dict[0].next = &dict[1];
    dict[1].number = "1";
    dict[1].wording = "one";
    dict[1].len = 1;
    dict[1].prev = &dict[0];
    dict[1].next = &dict[2];
    dict[2].number = "2";
    dict[2].wording = "two";
    dict[2].len = 1;
    dict[2].prev = &dict[1];
    dict[2].next = &dict[3];
    dict[3].number = "3";
    dict[3].wording = "three";
    dict[3].len = 1;
    dict[3].prev = &dict[2];
    dict[3].next = NULL;
    
    if (ac != 2)
    {
        write(2, "Usage: ./program_name <argument>\n", 34);
        return 1;
    }
    if (!is_number(av[1]))
    {
        write(2, "Error: Argument is not a valid number\n", 38);
        return 1;
    }
    print_number(av[1], dict);
    return 0;
}