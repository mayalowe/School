#! /bin/bash
# Eric Lowe and Ivan Hernandez
# uncomp.sh
# Script takes names of files to be decompressed
# on command line and decompresses them appropriately
# according to their file extension

# print usage statement and exit if no arguments given
[ $# -eq 0 ] && { echo "usage: uncomp.sh {filelist}+" ; exit 1; } 

for arg in $@ ; do
    case $arg in 
	*.tar) tar -xvf $arg ;;
	*.tar.gz) tar -xvzf $arg ;;
	*.tar.Z) tar -xvf $arg ;;
	*.tgz) tar -xvzf $arg ;;
	*.gz) gunzip -d $arg ;;
	*.Z) uncompress $arg ;;
	*.zip) unzip $arg ;;
	*) echo "uncomp: $arg has no compression extension" ;;
    esac # case $arg in
done # for arg in $@ ; 