#!/bin/sh

cleanup() (
	myDir="$PWD"
	s=""
	q=""
	i=""
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
			echo $item
		fi

	done
)

cleanup $*
