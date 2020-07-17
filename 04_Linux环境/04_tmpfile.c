/*
 * NOTES:
 * tmpnam返回一个随机生成的临时文件名。
 * tmpfile返回一个随机生成了临时文件名，并打开这个文件
 * 
 * 为了保证操作的原子性，最好使用tmpfile，避免使用tmpnam
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    char tmpname[L_tmpnam];
    char *filename;
    FILE *tmpfp;

    filename = tmpnam(tmpname);

    printf("filename = %s\ntmpname = %s\n", filename, tmpname);

    tmpfp = tmpfile();
    if (!tmpfp)
        perror("tmpfile");
    printf("Opend a temporary file OK\n");

    exit(0);
}