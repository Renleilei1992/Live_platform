
My_Shell_Name=$0

Wlog()
{
	iTime=`date +%Y%m%d-%H:%M:%S`
	echo "${My_Shell_Name}[${iTime}]:$1"
}



exec_script()
{
	Wlog "正在执行 [ $1 ] ...";
	$1 ;
	if test $? -ne 0; then
		Wlog "Error: excuting [ $1 ]"
		exit 1
	fi
	Wlog "执行完成 [ $1 ] !";
}

Wlog "显示脚本名------"
exec_script "echo $My_Shell_Name"
