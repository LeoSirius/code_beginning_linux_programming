#/bin/bash

echo "Enter password"
read trythis

while [ "$trythis" != "secret" ]; do
    echo "Sorry, try again"
    read trythis
done
exit 0

# Enter password
# we
# Sorry, try again
# re
# Sorry, try again
# secret