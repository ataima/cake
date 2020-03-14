#default pre_patch.sh : create the patch path 

#test exist SOURCE PATCH DIR
if [ ! -e ${PATCH} ] || [ ${FORCE} == 'Y' ]
then 
    local_log "CREATE SOURCE PATCH PATH : ${PATCH}"
    [ ${FORCE} == 'Y' ] && rm -rf ${PATCH}
    mkdir -p ${PATCH}
    RESULT=$?
else
    local_log   "PATCH SOURCE: ${PATCH} PATH EXIST"    
fi

#done 
local_log_close

