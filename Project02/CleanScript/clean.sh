#!/bin/sh

########################		Title Block			############################
###		Peter Haagsma														   #
###		Project #02															   #
################################################################################
################################################################################



# cleanup()
# 	This function deletes a set of unnecessary files in a location chosen by the user
#
#	@params:	directory -	- -	- -	- Default value is the current location in the console
#				--stats | -s  -	- -	- if this modifier is used then the stats will be displayed 
#									  after the function is complete
#				--quiet | -q  -	- -	- If this modifier is used then the function will not output 
#									  to the console, this is overidden by --interactive
#				--interactive | -i 	- If this modifier is used then the fucntion will ask the user
#									  to confirm they want files deleted before they're deleted
#
cleanup() (

	myDir="$PWD"		# Initialize directory to the current location
	s=""				# Initialize s/q/i modifiers to default value
	q=""				#
	i=""				# 
	FILE_COUNTER="0"	# Initilize file count to zero
	
	# - This for loop iterates the paramaters sent to the function and determines what the
	#   user wishes to accomplish
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
				# - If the parameter is not one of the defined modifiers then we check whether it
				#   is a valid directory
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

	# Move location to the chosen directory
	cd $myDir	

	# - This loop iterates through all files discovered by the ls -a command and decides
	# 	whether to delete them or something else
	for item in $(ls -a)
	do

		# - This case statement ensures we don't look into . or .. which sends us into
		#   an infinite loop
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
			FILE_COUNTER=$(($? + $FILE_COUNTER))	# Get returned value and add it to our file counter
			continue
		fi

		remove=false
		# This case statment removes the following files
		#	intermediate object files (those ending in .o)
		#	emacs backup files (those ending in ~)
		#	emacs auto-save files (those beginning and ending in #)
		# It also ensures that make files will not be deleted
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

		# - If the file type cannot be determined using the name, then we use the file command and parse
		#   through the output of that call
		ftype=$(file -b $item)
		case $ftype in
			*core*	)
				remove=true
				;;

			*executable*	)
				remove=true
				;;
		esac

		# If the file is one of the types we want to get rid of
		if test "$remove" = "true";
		then
			# - If the user used the --interactive modifier
			#   then we ask them to confirm deletion
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

			# - If the user passed either the quiet or the interactive modifier then we don't want to
			#   echo this string
			if test "$q$i" = "";
			then
				echo $item
			fi

			# E X T E R M I N A T E >:(
			rm $item
			# E X T E R M I N A T E >:(

			# If we get this far then we increment our counter
			FILE_COUNTER=$(($FILE_COUNTER + 1))
		fi

	done

	# - I chose to always return the number of files because to not always return it would require several 
	#   new if statements which would make the benefits negligible in my opinion
	return $FILE_COUNTER
)

#######################################################
#######################################################
###############							###############
############### |\    /|   /\   | |\  | ###############
############### | \  / |  /__\  | | \ | ###############
############### |  \/  | /    \ | |  \| ###############
###############							###############
#######################################################

# Get initial disk usage (summarized and in bytes)
INITIAL_USAGE=$(du -s -b)

# Call function passing in all modifiers from the command line
cleanup $*

# Get number of files deleted by program
FILE_COUNTER=$?

# Get final disk usage (summarized and in bytes)
FINAL_USAGE=$(du -s -b)

# If the user wanted stats displayed then this block displayes the total space saved and the number of files deleted
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
