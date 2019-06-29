
if [ "$1" == "" ]
then 
	echo "usage ./do_release 32 or 64 Linux or Windows"
	exit 1
fi

if [ "$2" == "" ]
then
        echo "usage ./do_release 32 or 64 Linux or Windows"
        exit 1
fi


#rm -rf Release$2$1

#mkdir Release$2$1
#cd Release$2$1
cmake -DCMAKE_INSTALL_PREFIX=Release$2$1  -DCMAKE_BUILD_TYPE=Release  -DCMAKE_TOOLCHAIN_FILE=./$1_$2_i686.toolchain.cmake   .
make -j8 all install

rm -rf install_manifest.txt
