#!/bin/bash

str='0'
while IFS= read -r line; do
    if {$line1 != $str}{
    echo "wrong!"
    echo "$line1"
    }
done < "wesley2.out"