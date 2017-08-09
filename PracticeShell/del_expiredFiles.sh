#!/bin/ksh

FILEPATH="/home/Renleilei/July-2017/test_expiredFiles"
DAYS=1

################################################################################
################################################################################
main()
{
	echo "开始删除过期文件..."
	ls -lrt
    find $FILEPATH -name "*.c" -ctime +$DAYS -type f -exec rm -rf {} \;
	echo "删除中..."
	ls -lrt
	echo "删除过期文件结束..."
}

## Execute main function
main $*
