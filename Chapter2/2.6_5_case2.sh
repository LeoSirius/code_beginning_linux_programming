#/bin/bash

# 这个例子在case中使用 | 和正则来进行选择

echo "Is it morning? Please answer yes or no"
read timeofday

case "$timeofday" in
    yes | y | Yes | YES )
        echo "Good Morning"
        echo "Up bright and early this morning"
        ;;
    [nN]* )
        echo "Good afternoon"
        ;;
    * )
        echo "Sorry, answer not recognized"
        echo "Please answer yes or no"
        exit 1
        ;;
esac

# leo@ubuntu:~/c_test$ ./t.sh 
# Is it morning? Please answer yes or no
# never
# Good afternoon