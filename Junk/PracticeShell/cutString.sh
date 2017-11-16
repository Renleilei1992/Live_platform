

##截取字符串

String="ESSDAS Cost: 3"

cost=`echo ${String#*:}`

echo "cost:"$cost
