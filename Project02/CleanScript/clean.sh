#!/bin/sh

cleanup() (

	myDir="$PWD"
	s=""
	q=""
	i=""
	FILE_COUNTER="0"
	for input in $*
	do
		case $input in
			-s | --stats 		)
				s=" -s"
				;;

			-q | --quiet		)
				q=" -q"
				;;

			-i | --interactive	)
				i=" -i"
				;;

			*					)
				if test -d $input;
				then
					myDir="$input"
				else
					echo "! ! ! Please enter a valid input ! ! !"
					exit 1
				fi
				;;
		esac
	done

	cd $myDir

	for item in $(ls -a)
	do

		# This case statement ensures we don't look into . or .. which sends us into
		# an infinite loop
		case $item in
			.	)
				continue
				;;
			..	)
				continue
				;;
		esac

		# This checks if it's a directory and recursively calls our function on it
		if test -d $item;
		then
			cleanup "$item$s$q$i"
			FILE_COUNTER=$(($? + $FILE_COUNTER))
			continue
		fi

		remove=false

		case $item in
			*.o 	)
				remove=true
				;;

			*~		)
				remove=true
				;;

			*#*#	)
				remove=true
				;;

			*akefile	)
				continue
		esac

		ftype=$(file -b $item)

		case $ftype in
			*core*	)
				remove=true
				;;

			*executable*	)
				remove=true
				;;
		esac

		if test "$remove" = "true";
		then

			if test "$i" != "";
			then
				echo "Would you like to delete '$item'? [Y/N]"
				read userInput
				case $userInput in
					Y | y 	)
						echo "Deleting $item"
						;;
					N | n 	)
						echo "Keeping $item"
						continue
						;;
				esac
			fi

			if test "$q$i" = "";
			then
				echo $item
			fi

			rm $item

			FILE_COUNTER=$(($FILE_COUNTER + 1))

		fi

	done

	return $FILE_COUNTER
)




INITIAL_USAGE=$(du -s -b)

cleanup $*
FILE_COUNTER=$?

FINAL_USAGE=$(du -s -b)

case $* in
	*-s* | *--stats*	)
		if test "$FILE_COUNTER" != "0";
		then
			INITIAL_USAGE=${INITIAL_USAGE%??}
			FINAL_USAGE=${FINAL_USAGE%??}

			spaceSaved=$(($INITIAL_USAGE - $FINAL_USAGE))

			echo "You saved $spaceSaved bytes"
			echo "and deleted $FILE_COUNTER files"
		else
			echo "No files found to be deleted!!"
			echo $FILE_COUNTER
		fi
		;;
esac
