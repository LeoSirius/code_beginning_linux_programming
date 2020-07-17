#/bin/bash

rm -f file_one

if [ -f file_one ] || echo "hello" || echo " there"
then
    echo "in if"
else
    echo "in else"
fi

exit 0

# leo@ubuntu:~/c_test$ ./t.sh 
# hello
# in if