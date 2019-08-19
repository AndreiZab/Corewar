CHAMPS=$(find ./ch -name '*.cor' | cut -c 3-)
for CHAMP in $CHAMPS
do
	./corewar_original -d $1 $CHAMP | tail -64 | cut -c10- > output_original
	./corewar -dump $1 $CHAMP | tail -64 | cut -c10- > output
	DIFF=$(diff -b output output_original)
	if [ "$DIFF" ]
	then
		printf "\e[1;31mKO\e[0m "
	else
		printf "\e[1;32mOK\e[0m "
	fi
	echo $CHAMP
done
