# C语言字符串处理库函数

## 1. 字符串拷贝函数：

```c
char *strcpy(char *dest, const char *src) ; // 将源字符串复制到目标字符串中。

char *strncpy(char *dest, const char *src, size_t n); // 将源字符串的前n个字符复制到目标字符串中。

void *memcpy(void *dest, const void *src, size_t n); // 将源内存块的前n个字节复制到目标内存块中。

void *memmove(void *dest, const void *src, size_t n); // 与memcpy函数类似，但可以处理源内存块与目标内存块重叠的情况。
```
## 2. 字符串连接函数：
```c
char *strcat(char *dest, const char *src); // 将源字符串连接到目标字符串的末尾。

char *strncat(char *dest, const char *src, size_t n); // 将源字符串的前n个字符连接到目标字符串的末尾。
```
## 3 .字符串比较函数：
```c
int strcmp(const char *s1, const char *s2); // 比较两个字符串是否相等。

int strncmp(const char *s1, const char *s2, size_t n); // 比较两个字符串的前n个字符是否相等。

int memcmp(const void *s1, const void *s2, size_t n); // 比较两个内存块的前n个字节是否相等。
```
## 4 .字符串搜索函数：
```c
char *strchr(const char *s, int c); // 在字符串中查找第一个出现c字符的位置。

char *strrchr(const char *s, int c); // 在字符串中查找最后一个出现c字符的位置。

char *strstr(const char *haystack, const char *needle); // 在字符串中查找子字符串的位置。

char *strpbrk(const char *s1, const char *s2); // 在字符串中查找s2中任意一个字符第一次出现的位置。

size_t strspn(const char *s1, const char *s2); // 返回字符串s1中包含s2中字符的最长前缀的长度。

size_t strcspn(const char *s1, const char *s2); // 返回字符串s1中不包含s2中任何字符的最长前缀的长度。
```
## 5 .字符串长度函数：
```c
size_t strlen(const char *s); // 返回字符串的长度。

size_t strnlen(const char *s, size_t maxlen); // 返回字符串s的长度，但最多只计算前maxlen个字符。
```
## 6. 字符串转换函数：
```c
int atoi(const char *nptr); // 将字符串转换为整数。

long atol(const char *nptr); // 将字符串转换为长整数。

double atof(const char *nptr); // 将字符串转换为浮点数。

long strtol(const char *nptr, char **endptr, int base); // 将字符串转换为长整数，并返回转换后的值和指向转换后的字符串的指针。

unsigned long strtoul(const char *nptr, char **endptr, int base); // 将字符串转换为无符号长整数，并返回转换后的值和指向转换后的字符串的指针。

char *strtok(char *str, const char *delim); // 将字符串分割成一个个单词，每次调用返回下一个单词。
```
## 7. 字符串格式化函数：
```c
int sprintf(char *str, const char *format, ...); // 将格式化的数据写入字符串中。

int snprintf(char *str, size_t size, const char *format, ...); // 与sprintf函数类似，但可以限制写入的字符数量。

int vsprintf(char *str, const char *format, va_list ap); // 与sprintf函数类似，但使用可变参数列表。

int vsnprintf(char *str, size_t size, const char *format, va_list ap); // 与snprintf函数类似，但使用可变参数列表。
```



> 请分別用代码列举实例说明以下C语言函数的用途：
```C
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);

char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);

int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
char *strstr(const char *haystack, const char *needle);
char *strpbrk(const char *s1, const char *s2);
size_t strspn(const char *s1, const char *s2);
size_t strcspn(const char *s1, const char *s2);

size_t strlen(const char *s);
size_t strnlen(const char *s, size_t maxlen);

int atoi(const char *nptr);
long atol(const char *nptr);
double atof(const char *nptr);
long strtol(const char *nptr, char **endptr, int base);
unsigned long strtoul(const char *nptr, char **endptr, int base);
char *strtok(char *str, const char *delim);

int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);
int vsprintf(char *str, const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);
```

### ChatGPT

## 1.字符串拷贝函数：

### 1. char *strcpy(char *dest, const char *src)：将字符串src复制到dest中，包括字符串结束符'\0'。

示例：

```c
char str1[] = "Hello, world!";
char str2[20];
strcpy(str2, str1);
printf("%s\n", str2); // 输出：Hello, world!
```

### 2. char *strncpy(char *dest, const char *src, size_t n)：将字符串src的前n个字符复制到dest中，如果src的长度小于n，则dest剩余的字符会用'\0'填充。

示例：

```c
char str1[] = "Hello, world!";
char str2[20];
strncpy(str2, str1, 5);
printf("%s\n", str2); // 输出：Hello
```

### 3. void *memcpy(void *dest, const void *src, size_t n)：将src中的n个字节复制到dest中。

示例：

```c
char str1[] = "Hello, world!";
char str2[20];
memcpy(str2, str1, 5);
printf("%s\n", str2); // 输出：Hello
```

### 4. void *memmove(void *dest, const void *src, size_t n)：将src中的n个字节复制到dest中，与memcpy不同的是，memmove可以处理重叠的内存区域。

示例：

```c
char str[] = "Hello, world!";
memmove(str+7, str+1, 7);
printf("%s\n", str); // 输出：Hello, Hello!
```

## 2.字符串连接函数：

### 5. char *strcat(char *dest, const char *src)：将字符串src追加到dest的末尾，包括字符串结束符'\0'。

示例：

```c
char str1[] = "Hello, ";
char str2[] = "world!";
strcat(str1, str2);
printf("%s\n", str1); // 输出：Hello, world!
```

### 6. char *strncat(char *dest, const char *src, size_t n)：将字符串src的前n个字符追加到dest的末尾，如果src的长度小于n，则只会追加src的全部字符。

示例：

```c
char str1[] = "Hello, ";
char str2[] = "world!";
strncat(str1, str2, 3);
printf("%s\n", str1); // 输出：Hello, wor
```

## 3.字符串比较函数：

### 7. int strcmp(const char *s1, const char *s2)：比较字符串s1和s2的大小，如果s1>s2，则返回正数，如果s1<s2，则返回负数，如果s1=s2，则返回0。

示例：

```c
char str1[] = "abc";
char str2[] = "def";
int result = strcmp(str1, str2);
printf("%d\n", result); // 输出：-3
```

### 8. int strncmp(const char *s1, const char *s2, size_t n)：比较字符串s1和s2的前n个字符的大小，如果s1>s2，则返回正数，如果s1<s2，则返回负数，如果s1=s2，则返回0。

示例：

```c
char str1[] = "abc";
char str2[] = "ade";
int result = strncmp(str1, str2, 2);
printf("%d\n", result); // 输出：-1
```

### 9. int memcmp(const void *s1, const void *s2, size_t n)：比较内存区域s1和s2的前n个字节的大小，如果s1>s2，则返回正数，如果s1<s2，则返回负数，如果s1=s2，则返回0。

示例：

```c
char str1[] = "abc";
char str2[] = "ade";
int result = memcmp(str1, str2, 2);
printf("%d\n", result); // 输出：-1
```

## 4.字符串搜索函数：

### 10. char *strchr(const char *s, int c)：在字符串s中查找字符c的第一个出现位置，如果找到，则返回该位置的指针，否则返回NULL。

示例：

```c
char str[] = "Hello, world!";
char *result = strchr(str, 'w');
printf("%s\n", result); // 输出：world!
```

### 11. char *strrchr(const char *s, int c)：在字符串s中查找字符c的最后一个出现位置，如果找到，则返回该位置的指针，否则返回NULL。

示例：

```c
char str[] = "Hello, world!";
char *result = strrchr(str, 'o');
printf("%s\n", result); // 输出：orld!
```

### 12. char *strstr(const char *haystack, const char *needle)：在字符串haystack中查找字符串needle的第一个出现位置，如果找到，则返回该位置的指针，否则返回NULL。

示例：

```c
char str[] = "Hello, world!";
char *result = strstr(str, "world");
printf("%s\n", result); // 输出：world!
```

### 13. char *strpbrk(const char *s1, const char *s2)：在字符串s1中查找s2中任意字符的第一个出现位置，如果找到，则返回该位置的指针，否则返回NULL。

示例：

```c
char str[] = "Hello, world!";
char *result = strpbrk(str, "ow");
printf("%s\n", result); // 输出：orld!
```

### 14. size_t strspn(const char *s1, const char *s2)：返回字符串s1中前缀连续包含s2中任意字符的长度。

示例：

```c
char str[] = "Hello, world!";
size_t result = strspn(str, "Helo, wrd");
printf("%zu\n", result); // 输出：12
```

### 15. size_t strcspn(const char *s1, const char *s2)：返回字符串s1中前缀连续不包含s2中任意字符的长度。

示例：

```c
char str[] = "Hello, world!";
size_t result = strcspn(str, "o");
printf("%zu\n", result); // 输出：1
```

## 5.字符串长度函数：

### 16. size_t strlen(const char *s)：返回字符串s的长度，不包括字符串结束符'\0'。

示例：

```c
char str[] = "Hello, world!";
size_t len = strlen(str);
printf("%zu\n", len); // 输出：13
```

### 17. size_t strnlen(const char *s, size_t maxlen)：返回字符串s的长度，但最多只计算前maxlen个字符，不包括字符串结束符'\0'。

示例：

```c
char str[] = "Hello, world!";
size_t len = strnlen(str, 5);
printf("%zu\n", len); // 输出：5
```

## 6.字符串转换函数：

### 18. int atoi(const char *nptr)：将字符串nptr转换为整数。

示例：

```c
char str[] = "123";
int num = atoi(str);
printf("%d\n", num); // 输出：123
```

### 19. long atol(const char *nptr)：将字符串nptr转换为长整数。

示例：

```c
char str[] = "123456789";
long num = atol(str);
printf("%ld\n", num); // 输出：123456789
```

### 20. double atof(const char *nptr)：将字符串nptr转换为双精度浮点数。

示例：

```c
char str[] = "3.14";
double num = atof(str);
printf("%lf\n", num); // 输出：3.140000
```

### 21. long strtol(const char *nptr, char **endptr, int base)：将字符串nptr转换为长整数，base指定进制，endptr用于存储转换后第一个非数字字符的指针。

示例：

```c
char str[] = "101010";
char *end;
long num = strtol(str, &end, 2);
printf("%ld\n", num); // 输出：42
printf("%s\n", end); // 输出：(空字符串)
```

### 22. unsigned long strtoul(const char *nptr, char **endptr, int base)：将字符串nptr转换为无符号长整数，base指定进制，endptr用于存储转换后第一个非数字字符的指针。

示例：

```c
char str[] = "0x2a";
char *end;
unsigned long num = strtoul(str, &end, 16);
printf("%lu\n", num); // 输出：42
printf("%s\n", end); // 输出：(空字符串)
```

### 23. char *strtok(char *str, const char *delim)：将字符串str按照分隔符delim进行分割，返回分割后的第一个子串的指针，下一次调用时传入NULL作为参数继续分割，直到所有子串都被分割完毕。

示例：

```c
char str[] = "Hello, world!";
char *token = strtok(str, ", ");
while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, ", ");
}
// 输出：
// Hello
// world!
```

## 7.字符串格式化函数：

### 24. int sprintf(char *str, const char *format, ...)：将格式化的字符串输出到str中，返回输出的字符数。

示例：

```c
char str[20];
int num = 42;
sprintf(str, "%d", num);
printf("%s\n", str); // 输出：42
```

### 25. int snprintf(char *str, size_t size, const char *format, ...)：将格式化的字符串输出到str中，最多输出size-1个字符，返回输出的字符数。

示例：

```c
char str[10];
int num = 123456;
int len = snprintf(str, 10, "%d", num);
printf("%s\n", str); // 输出：12345
printf("%d\n", len); // 输出：5
```

### 26. int vsprintf(char *str, const char *format, va_list ap)：将格式化的字符串输出到str中，参数列表由va_list类型的ap指定，返回输出的字符数。

示例：

```c
char str[20];
int num = 42;
va_list ap;
va_start(ap, num);
int len = vsprintf(str, "%d", ap);
va_end(ap);
printf("%s\n", str); // 输出：42
printf("%d\n", len); // 输出：2
```

### 27. int vsnprintf(char *str, size_t size, const char *format, va_list ap)：将格式化的字符串输出到str中，最多输出size-1个字符，参数列表由va_list类型的ap指定，返回输出的字符数。

示例：

```c
char str[10];
int num = 123456;
va_list ap;
va_start(ap, num);
int len = vsnprintf(str, 10, "%d", ap);
va_end(ap);
printf("%s\n", str); // 输出：12345
printf("%d\n", len); // 输出：5
```
