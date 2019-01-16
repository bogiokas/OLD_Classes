#!/bin/bash
value=1;

while [ $value -le 25 ]
do
./../strategicgame < "input$value.txt"
# > "tempout"
value=`expr $value + 1`;
done

#while read line
#do
#echo $value;
#done < "myfile"

#echo $value;
