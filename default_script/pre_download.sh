#default pre_download.sh : create the source path 
#check ENV SOURCE is SET
if [ ${SOURCE} == "" ]
then
    exit 1
fi
#check ENV STORE is SET
if [ ${STORE} == "" ]
then
    exit 1
fi
#check ENV LOG is SET
if [ ${LOG} == "" ] 
then 
    exit 1
fi

#test exist SOURCE DIR
if [ ! -e ${SOURCE} ]
then 
    echo $(date) " : pre_download.sh : CREATE SOURCE PATH : ${SOURCE}" > $LOG  2>&1
    mkdir -p ${SOURCE}
    RESULT=$?
fi

#test exist SOURCE DIR
if [ ! -e ${STORE} ]
then 
    echo $(date) " : pre_download.sh : CREATE STORE PATH : ${STORE}" >> $LOG  2>&1
    mkdir -p ${STORE}
    RESULT=$?
fi

#done 
exit ${RESULT}


