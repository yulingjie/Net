#include <stdio.h>

struct ts{
    union{
        int a;
        int b;
    }tsu;
};
#define tsa tsu.a
#define tsb tsu.b

int main(int argc, const char *argv[])
{
   struct ts t;
   t.tsa = 10;
   printf("%d\n",t.tsb);
    return 0;
}
