#include <stdio.h>

int main(void)
{
    FILE *fp = fdopen(1, "w+");
    fprintf(fp, "%s\n", "hello");
    fclose(fp);
    return 0;
}