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
