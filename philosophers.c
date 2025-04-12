#include <pthread.h>
#include <stdio.h>

void *test(void *add)
{
    long *add_num = (long *) add;
    printf("add: %ld\n",*add_num);
}

int main()
{
    pthread_t t1;
    // pthread_t t2;
    long value1 = 1;
    pthread_create(&t1,NULL,test,(void *) &value1);
    // pthread_create(&t2,NULL,test,NULL);
    pthread_join(t1,NULL);
    // pthread_join(t2,NULL);
}