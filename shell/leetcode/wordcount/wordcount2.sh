#! /bin/bash
# solution 1
if [ $# -eq 0 ]
then
echo "Usage:$0 args error"
exit 0
fi
if [ $# -ge 2 ]
then
echo "analyse the first file $1"
fi

#get the first file
filename=$1
awk -F' ' '{for(i=1;i<=NF;i=i+1){print $i}}' $filename |sort|uniq -c|sort -nr|awk -F' ' '/[a-z]/{printf("%s %s\n",$2,$1)}' | head -n 3