#!/bin/bash
#enter input encoding here
FROM_ENCODING="UTF-8"
#output encoding(UTF-8)
TO_ENCODING="ASCII"
#convert
CONVERT=" iconv  -f   $FROM_ENCODING  -t   $TO_ENCODING"
#loop to convert multiple files 
for  file  in  *.csv; do
     $CONVERT   "$file"   -o  "${file%.txt}"
done
exit 0
