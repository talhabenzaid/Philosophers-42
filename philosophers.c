#include <stdio.h>
// ./a.out 3 500 200 200 | ./a.out 3 500 200 200 5
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
            if(str[i][j] <= '0' || str[i][j] >= '9')
            {
                printf("invalide argument\n");
                return(1);
            }
            j++;
        }
        i++;
    }

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