#!/bin/sh
error_path="lab1_err"
cont=0
while [ $cont -ne 6 ]
	do
	echo "1 - Print name of the current directory"
	echo "2 - Change directory"
	echo "3 - Print content of the current directory"
	echo "4 - Create file link"
	echo "5 - Delete file link"
	echo "6 - Exit"
	read cont
	case $cont in
	1)
		echo "The current directory is:"
		basename "$PWD"
	;;
	2)
		echo "Enter directory"
		read directory_name
		cd "$directory_name" 2>> $error_path || echo "Directory does not exist"
	;;
	3)
		ls
	;;
	4)
		echo "Enter file name"
		read fileName
		echo "Print link name"
		read linkName
		ln "$fileName" "$linkName" 2>> $error_path || echo "Error, please see lab1_err"
	;;
	5)
		echo "Enter link name"
		read linkName
		rm "$linkName" 2>> $error_path || echo "Link does not exist"
	;;
	6)
		echo "Exit"
	;;
	*)  
		echo "This command does exist, repeat please"
	;;
	esac
done