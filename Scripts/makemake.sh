#! /bin/bash
# Eric Lowe and Ivan Hernandez
# makemake.sh [executableName]
# Script takes the name of an executable to be made on the
# command line and creates a Makefile based on the .cpp
# files in the current directory

# if no arguments given, print usage and exit
if [ $# -eq 0 ] ; then
    echo "Executable name required." 
    echo "usage: makemake.sh executable_name" 
    exit 1 
# else if more than one argument given, set test to 1
elif [ $# -gt 1 ] ; then
    test=1
else
    test=0
fi # if [ $# -eq 0 ]

executable="$1" 
shift

# prints executable dependency line
echo -n "$executable : " > Makefile
for file in *.cpp ; do
    echo -n "${file%.cpp}.o " >> Makefile
done # for file in *.cpp

echo " " >> Makefile

echo -e -n "\tg++ -ansi -Wall -g -o $executable " >> Makefile
# if more than one argument given, print them in order
if [ $test -eq 1 ] ; then
    for arg in $@ ; do
	echo -n "$arg " >> Makefile
    done # for arg in $@
fi # if [ test -eq 1 ]

for file in *.cpp ; do
    echo -n "${file%.cpp}.o " >> Makefile
done # for file in *.cpp

echo -e "\n" >> Makefile

# prints .o file dependency lines
for file in *.cpp ; do
    echo -n "${file%.cpp}.o : $file " >> Makefile
    sed -n '/#include ".*"/p' $file | awk -F\" '{ printf("%s ", $2) }' >> Makefile
    echo " " >> Makefile
    echo -e -n "\tg++ -ansi -Wall -g -c " >> Makefile
    # if more than one argument given, print them in order
    if [ $test -eq 1 ] ; then
	for arg in $@ ; do
	    echo -n "$arg " >> Makefile
	done # for arg in $@
    fi # if [ $test -eq 1 ]
    
    echo -e "$file\n" >> Makefile
done # for file in *.cpp

# prints clean statement
echo "clean :" >> Makefile
echo -e -n "\trm -f $executable " >> Makefile

for file in *.cpp ; do
    echo -n "${file%.cpp}.o " >> Makefile
done # for file in *.cpp

echo -e "\n" >> Makefile