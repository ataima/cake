# @cake
#####################
#--> GIT DOWNLOAD
#####################
#default download_git.sh : populate source path via git
#go to sources file

pushd ${SOURCE}

# check exist .git
if [ ! -e "./src" ] || [ ${FORCE} == "Y" ]
then 
    if [ ${BRANCH} == "" ] || [ ${BRANCH} == "master" ]
    then 
        local_log "$SOURCE from ${URL}/${FILE}"
        git clone --progress "${URL}/${FILE}" src >> ${LOG} 2>&1
        RESULT=$?
    else
        locaL-log "$SOURCE  from ${URL}/${FILE} with branch ${BRANCH}"
        git clone --progress "${URL}/${FILE}"  -b ${BRANCH} src >> ${LOG} 2>&1
        RESULT=$?
    fi

    if [ ${RESULT} -eq 0 ] 
    then
        remove_store_backup "${STORE}/${PROJECT}_${COMMIT}.tar.bz2"    
        if [ ${COMMIT} != "" ] 
        then
            cd src
            git checkout ${COMMIT} >> ${LOG} 2>&1
            RESULT=$?
            [ ${RESULT} -eq 0 ] &&  local_log "checking out ${COMMIT}"
        fi
    else 
        local_log " FAIL to DOWNLOAD GIT FILE : ${URL}/${FILE}"
    fi
fi
popd 

pushd ${SOURCE}

if [ -e "./src/.git" ]
then
    cd src
    CURRENT=$(git rev-parse HEAD)
    local_log "current status 'HEAD' ${CURRENT}" 
    if [ "${CURRENT}" != "${COMMIT}" ]
    then 
        RESULT=1
    else
        verify_store_backup "${STORE}/${PROJECT}_${COMMIT}.tar.bz2"
    fi 
else
    RESULT=1    
fi
#return main root
popd 
# if OK stop download phase and NOT continue script
if [ ${RESULT} -eq  0 ]
then 
    local_log_close
fi