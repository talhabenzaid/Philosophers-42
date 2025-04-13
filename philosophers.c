#include <stdio.h>
// ./a.out 3 500 200 200 | ./a.out 3 500 200 200 5
int ft_atoi(char *str)
{
    int i;
    int r;

    i = 0;
    r = 1;
    while(str[i])
    {
        r = r * 10 + str[i] - '0';
        i++;
    }
    return(r);
}
int pars(char **str)
{
    int i;
    int j;

    i = 1;
    while(str[i])
    {
        j = 0;
        while(str[i][j])
        {
            if(str[i][j] != '+' && (str[i][j] < '0' || str[i][j] > '9'))
            {
                printf("invalide argument\n");
                return(1);
            }
            j++;
        }
        i++;
    }
    if(ft_atoi(str[1]) >= 200)
    {
        printf("number_of_philosophers must be less than 200\n");
        return(1);
    }
    return(0);
}
int main(int argc ,char *argv[])
{
    if(argc != 5 && argc != 6)
    {
        printf("invalide argument\n");
        return(0);
    }
    if (pars(argv) == 1)
        return(0);
}