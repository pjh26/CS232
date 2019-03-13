#!/bin/sh


for input in $*
do
	case $input in
		-s | --stats 		)
			echo "Stats"
			;;

		-q | --quiet		)
			echo "Quiet"
			;;

		-i | --interactive	)
			echo "Interactive"
			;;

		*					)
			echo $input
			;;
	esac

done