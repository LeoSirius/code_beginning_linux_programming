#/bin/bash

touch file_one
rm -f file_two

if [ -f file_one ] && echo "hello" && [ -f file_two ] && echo " there"
then
    echo "in if"
else
    echo "in else"
fi

exit 0

# leo@ubuntu:~/c_test$ ./t.sh 
# hello
# in else