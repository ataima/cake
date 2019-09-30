#default pre_download.sh : system set env -> default create the source path  and log 
#check ENV SOURCE is SET
if [ $SOURCE == "" ]
then
    exit 1
fi
#check ENV LOG is SET
if [ $LOG == "" ] 
then 
    exit 2
fi

#Go
#test exist SOURCE DIR
if [ ! -e $SOURCE ]
then 
    echo $(date) " : pre_download.sh : CREATE SOURCE PATH : " $SOURCE > $LOG
    mkdir -p $SOURCE
    exit $?
fi

#done 
exit 0


