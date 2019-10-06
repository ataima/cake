#default pre_download.sh : create the source path 

#test exist SOURCE DIR
if [ ! -e ${SOURCE} ] || [ ${FORCE} == 'Y' ]
then 
    local_log "CREATE SOURCE PATH : ${SOURCE}"
    mkdir -p ${SOURCE}
    RESULT=$?
else
    local_log   "SOURCE: ${SOURCE} PATH EXIST"    
fi

#test exist STORE DIR
if [ ! -e ${STORE} ] || [ ${FORCE} == 'Y' ]
then 
    local_log "CREATE STORE PATH : ${STORE}"
    mkdir -p ${STORE}
    RESULT=$?
else
    local_log   "STORE: ${STORE} PATH EXIST"
fi

#done 
local_log_close

