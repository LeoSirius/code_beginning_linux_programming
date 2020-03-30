#/bin/bash

echo "Is it morning? Please answer yes or no"
read timeofday

case "$timeofday" in
    yes)   echo "Good Morning";;
    no )   echo "Good Afternoon";;
    y  )   echo "Good Morning";;
    n  )   echo "Good Afternoon";;
    *  )   echo "Sorry, answer not recognized";;
esac

exit 0

# leo@ubuntu:~/c_test$ ./t.sh 
# Is it morning? Please answer yes or no

# Sorry, answer not recognized
# leo@ubuntu:~/c_test$ ./t.sh
# Is it morning? Please answer yes or no
# y
# Good Morning