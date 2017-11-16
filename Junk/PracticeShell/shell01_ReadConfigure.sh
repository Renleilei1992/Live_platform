#####################################################################
# 脚本名称：func.sh                                                 #
# 安装路径：/home/Renleilei/Repository/Live_platform/PracticeShell  #
# 脚本功能：                                                        #
#           1.
#####################################################################




My_Shell_Name=$0

#格式化提示信息
Wlog()
{
	iTime=`date +%Y%m%d-%H:%M:%S`
	echo "${My_Shell_Name}[${iTime}]:$1"
}


#执行脚本
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


#读取配置文件
CFG_file=/home/Renleilei/Repository/Live_platform/PracticeShell/configure.cfg
Num_Environment=`cat $CFG_file | wc -l`
echo $Num_Environment
if [ $Num_Environment -lt 1 ]; then echo "配置文件中缺少环境IP！请检查！"; exit 1;fi

echo "开始读取配置文件..."
Num=0
while [ $Num -lt $Num_Environment ]
do
	Num=`expr $Num + 1`
	IP=`sed -n "${Num}p" configure.cfg | cut -d ' ' -f 1`
	UsrName=`sed -n "${Num}p" configure.cfg | cut -d ' ' -f 2`
	Password=`sed -n "${Num}p" configure.cfg | cut -d ' ' -f 3`
	echo "第"$Num"个目标环境的IP为："$IP"  用户名为："$UsrName"  密码为："$Password
done



