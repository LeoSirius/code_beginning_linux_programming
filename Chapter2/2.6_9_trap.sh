#/bin/bash

# trap command signal
# signal是要处理的信号名
# command是收到该信号时，要执行的指令

trap 'rm -f /tmp/tmp_file_$$' INT  # $$是当前shell的pid，INT是中断信号，即ctrl+c
echo "creating file /tmp/tmp_file_$$"
date > /tmp/tmp_file_$$

echo "press interrupt (CTRL-C) to interrupt..."
while [ -f /tmp/tmp_file_$$ ]; do
    echo "file exists"
    sleep 1
done
echo "The file no longer exists"

trap INT # 不指定任命令，则执行默认行为，即中断。注意，如果是command是空字符串，则会跳过INT信号
echo "creating file /tmp/tmp_file_$$"
date > /tmp/tmp_file_$$

echo "press interrupt (CTRL-C) to interrupt..."
while [ -f /tmp/tmp_file_$$ ]; do
    echo "file exists"
    sleep 1
done
echo "We never get here"

exit 0

# leo@ubuntu:~/c_test$ ./t.sh 
# creating file /tmp/tmp_file_22609
# press interrupt (CTRL-C) to interrupt...
# file exists
# ^CThe file no longer exists
# creating file /tmp/tmp_file_22609
# press interrupt (CTRL-C) to interrupt...
# file exists
# file exists
# ^C
