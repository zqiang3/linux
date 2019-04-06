## 原型

```c
char* fgets(char *s, int n, FILE *stream);
```

参数：

s: 字符型指针，缓冲区地址。

n: 从流中读入n-1个字符

stream: 指向读取的流

返回值：

1. n <= 0时，返回NULL
2. n = 1时，返回空串""
3. 读入成功，返回缓冲区地址
4. 读入错误或遇到文件结尾EOF， 则返回NULL

## 官方说明

char *fgets(string, count, stream) 

input string from a stream

**Purpose** 

Reads characters from stream and stores them as a C string into str until (num-1) characters have been read or either a newline or the End-of-File is reached, whichever comes first.
A newline character makes fgets stop reading, but it is considered a valid character and therefore it is included in the string copied to str.
A null character is automatically appended in str after the characters read to signal the end of the C string.

if count<=1, no input is requested. if EOF is found immediately, return NULL. if EOF found after chars read, let EOF finish the string as '\n' would. 

**Entry**

char *string - pointer to place to store string

int count - max characters to place at string (include \0)

FILE *stream - stream to read from

**Exit**

returns string with text read from file in it

if count <= 0 return NULL 

if count == 1 put null string in string

returns NULL if error or end-of-file found immediately       



## 实现

```c
char *fgets(char *s, int n,  FILE *stream)  
{  
     register int c;  
     register char *cs;  
     cs=s;  
     while(--n>0 &&(c = getc(stream))!=EOF)  
     if ((*cs++=  c) =='\n')  
           break;  
     *cs ='\0';  
     return (c == EOF && cs == s) ?NULL :s ;  
}  
```

