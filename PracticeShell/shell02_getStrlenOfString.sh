##
##使用shell命令获取字符串长度
##
##

PATH_LSTASK=`pwd`
NUM_SpaceLength=18
NUM_=1


sql_ywk()
{
dbaccess gafeywk<<! 2>/dev/null
$1;
!
}

sql_csk()
{
dbaccess gafecsk<<! 2>/dev/null
$1;
!
}

##获取 gafecsk:batchtaskinfo 参数表中的 transcode
iRet=`sql_csk "select transcode from batchtaskinfo where status='1'" | sed "1,4d" | awk NF | sort -u > $PATH_LSTASK/transcode.txt`
if [ $? -ne 0 ];  then echo "gafecsk:batchtaskinfo 数据库查询操作失败!";exit -1;fi

echo "Transcode       |    flow_name       |    step_name" >> $PATH_LSTASK/lstask.txt
for Transcode in `cat $PATH_LSTASK/transcode.txt`
do
	Space="                 "
	
	Flow_name=`sql_csk "select flowname from batchtaskinfo where transcode='$Transcode'" | sed "1,4d"`
	if [ $? -ne 0 ]; then echo "gafecsk:batchtaskinfo.flowname 数据库查询失败!";exit -1;fi
	Flow_name=`echo $Flow_name | tr -d '[ \t]'`
	if [ "$Flow_name" = "" ]
	then
			Flow_name="    ";
	elif [ ${#Flow_name} -gt 4 ]
	then
			num_01=`expr ${#Flow_name} - 4`
			num_SpaceLen=`expr $NUM_SpaceLength - $num_01`
			Space=""
			while [ "$num_SpaceLen" -ge "1" ]
			do
				SpaceLength=$SpaceLength" "
				num_SpaceLen=`expr $num_SpaceLen - 1`
			done
	fi

	Step_name=`sql_ywk "select step_name from clr_task_cfg where step_no='Transcode'" | sed "1,4d"`
	if [ $? -ne 0 ]; then echo "gafeywk:clr_task_cfg.step_name 数据库查询失败!";exit -1;fi
	Step_name=`echo $Step_name | tr -d '[ \t]'`
	echo "$Trancode        |   $Flow_name$SpaceLength|$Step_name" >> $PATH_LSTASK/lstask.txt
done
