#!/bin/bash

# 这里展示 $x的用法

salution="Hello"
echo $salution
echo "The program $0 is now running"
echo "The first param is $1"
echo "The second param is $2"
echo "The parameter list is $*"
echo "The user's home directory is $HOME"

echo "Please enter a new greeting"
read salution

echo $salution
echo "The script is now complete"
exit 0

# 这是输入和输出
# leo@ubuntu:~/c_test$ ./2.6_2_try_var.sh foo bar baz
# Hello
# The program ./2.6_2_try_var.sh is now running
# The first param is foo
# The second param is bar
# The parameter list is foo bar baz
# The user's home directory is /home/leo
# Please enter a new greeting
# Hello2
# Hello2
# The script is now complete