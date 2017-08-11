
##
##测试read line:2

FileName=configure.cfg

while read line
do
	if [ ${line} == "110" ]
	then
			echo "line:2 is 110"
	else
			echo $line
			printf "it's a printf %s\n" 'TEST!'
			printf '%s\n' '         __                                     __   '
		    printf '%s\n' '  ____  / /_     ____ ___  __  __   ____  _____/ /_  '
			printf '%s\n' ' / __ \/ __ \   / __ `__ \/ / / /  /_  / / ___/ __ \ '
			printf '%s\n' '/ /_/ / / / /  / / / / / / /_/ /    / /_(__  ) / / / '
			printf '%s\n' '\____/_/ /_/  /_/ /_/ /_/\__, /    /___/____/_/ /_/  '
			printf '%s\n' '                        /____/                       '

	fi
done <$FileName
