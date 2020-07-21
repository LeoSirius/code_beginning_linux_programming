/*
 * NOTES:
 * open和fopen的区别，参考：
 * https://stackoverflow.com/questions/1658476/c-fopen-vs-open
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c;
    FILE *in, *out;

    in = fopen("file.in", "r");
    out = fopen("file.out", "w");

    while ((c = fgetc(in)) != EOF) {
        fputc(c, out);
    }

    exit(0);
}
