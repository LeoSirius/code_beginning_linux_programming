#/bin/bash

if [ -f /bin/bash ]
then
    echo "file /bin/bash exist"
fi

if [ -d /bin/bash ]
then
    echo "/bin/bash is a directory"
else
    echo "/bin/bash is NOT a directory"
fi

# leo@ubuntu:~/c_test$ ./t.sh 
# file /bin/bash exist
# /bin/bash is NOT a directory