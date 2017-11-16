_A=tb_1
_B=tb_2
_A_count=10000
_B_count=10001

echo "$_A 's count(*):$_A_count"

LOG()
{
echo $1;
}

LOG "$_A's NIHAO"$_A_count
