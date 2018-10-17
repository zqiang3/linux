#include <stdio.h>
#include <string.h>

int strindex(char *s, char *t, int pos);

int main(int argc, char** argv)
{
    char *s = "fabfcabcefg";
    char *t = "abc";
    int index = strindex(s, t, 0);
    printf("index = %d\n", index);

}

int strindex(char *s, char *t, int pos)
{
    if(!s || !t)
        return -1;

    int lens = strlen(s);
    int lent = strlen(t);

    if(lens == 0 || lent == 0)
        return -1;

    int i;
    int j;
    int index = -1;
    for(i=pos; i<=lens-lent; i++)
    {
        if(s[i] != t[0])
            continue;

        j = 0;
        for(j=1; j<lent; j++)
        {
            if(s[i+j] != t[j])  // 子串某个字符不匹配
                break;
        }

        if(j == lent)   // 子串匹配
        {
            index = i;
            break;
        }
    }

    return index;
}
