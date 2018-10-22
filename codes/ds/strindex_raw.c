#include <stdio.h>
#include <string.h>

int strindex(char *s, char *t, int pos);
int strindex_v2(char *s, char *t, int pos);

int main(int argc, char** argv)
{
    char *s = "abc";
    char *t = "bc";
    int index = strindex_v2(s, t, 0);
    printf("index = %d\n", index);
    index = strindex(s, t, 0);
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

    if(pos < 0 || pos >= strlen(s))
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

int strindex_v2(char *s, char *t, int pos)
{
    if(!s || !t)
        return -1;

    if(strlen(t) == 0 || strlen(s) == 0)
        return -1;
    
    if(pos < 0 || pos >= strlen(s))
        return -1;


    s += pos;
    int i = 0;
    int j = 0;
    while(s[i] && t[j])
    {
        if(s[i] != t[j])
        {
            i = i -j + 1;  // 回退
            j = 0;
        }
        else
        {
            i++;
            j++;
        }
    }

    if(!t[j])
        return i - j;
    else
        return -1;
}
