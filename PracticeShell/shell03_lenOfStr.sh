#
#
#
#获取字符串长度，使用shell命令
#

__String_01='Hello World!'
__String_02='Nihao!'
__String_03='你好!'

__Num_01=${#__String_01}
__Num_02=${#__String_02}
__Num_03=${#__String_03}

echo $__String_01"'s strlen = ["$__Num_01"]"
echo $__String_02"'s strlen = ["$__Num_02"]"
echo $__String_03"'s strlen = ["$__Num_03"]"

