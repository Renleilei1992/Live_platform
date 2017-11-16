
FileName=$1
cp $1 $1.bak
sort -nk 1 -t\| > $1
if [ $? -eq 1 ]; then echo "sort success!";fi


