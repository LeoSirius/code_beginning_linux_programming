#/bin/bash

# 函数内部的$开头的参数变量是函数local的，不同于整个脚本的参数变量

yes_or_no () {
    echo "Is your name $* ?"  # 这里已$*其实就是整个脚本的$1参数
    while true
    do
        echo -n "Enter yes or no: "
        read x
        case "$x" in
            y | yes ) return 0;;
            n | no  ) return 1;;
            *       ) echo "Answer yes or no"
        esac
    done
}

echo "Original parameters are $*"

if yes_or_no "$1"
then
    echo "Hi $1, nice name"
else
    echo "Never mind"
fi
exit 0

# leo@ubuntu:~/c_test$ ./t.sh leo sirius
# Original parameters are leo sirius
# Is your name leo ?
# Enter yes or no: y
# Hi leo, nice name
