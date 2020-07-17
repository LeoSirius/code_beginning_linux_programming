/*
 * NOTES:
 * pw结构体存放用户在/etc/passwd中的条目信息
 */

#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    uid_t uid;
    gid_t gid;

    struct passwd *pw;

    printf("User is %s\n", getlogin());  /* getlogin()返回登录名 */

    uid = getuid();
    gid = getgid();
    printf("User IDs: uid=%d, gid=%d\n", uid, gid);

    pw = getpwuid(uid);     /* getpwuid根据uid返回用户信息的结构体 */
    printf("UID passwd entry:\nname=%s, uid=%d, gid=%d, home=%s, shell=%s\n",
        pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);

    pw = getpwnam("root"); /* getpwnam根据username返回用户信息的结构体 */
    printf("UID passwd entry:\nname=%s, uid=%d, gid=%d, home=%s, shell=%s\n",
        pw->pw_name, pw->pw_uid, pw->pw_gid, pw->pw_dir, pw->pw_shell);

    exit(0);
}

// leo@ubuntu:~/c_test$ ./a.out 
// User is leo
// User IDs: uid=1000, gid=1000
// UID passwd entry:
// name=leo, uid=1000, gid=1000, home=/home/leo, shell=/bin/bash
// UID passwd entry:
// name=root, uid=0, gid=0, home=/root, shell=/bin/bash