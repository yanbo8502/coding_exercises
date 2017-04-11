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
grep -E -o "\[b[[:alpha:]]+]\b" $filename | awk ' { count[$0]++ } 
END{printf("%-20s%s\n","Word","Count");
for(word in count)
{printf("%-20s%s\n",word,count[word])}
}'