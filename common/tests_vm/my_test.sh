test()
{
	echo $2 '  ' $3 '  ' $4 '  ' $5
	for ((i=$1; i < 10000; i++))
	do
		./corewar_original -d $i $2 $3 $4 $5 | tail -64  | cut -c10- > output_original
		./corewar -dump $i $2 $3 $4 $5 | tail -64 | cut -c10- > output
		DIFF=$(diff -b output output_original)
		if [ "$DIFF" ]
		then
			printf "\e[1;31mKO\e[0m "
			echo $i
			echo "./corewar_original -d " $i $2 $3 $4 $5 
			echo "./corewar -dump " $i $2 $3 $4 $5 
			break
		else
			printf "\e[1;32mOK\e[0m "
			echo $i
		fi
	done
}

test $1 $2
