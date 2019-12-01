# @cake
#####################
#--> GIT POST DOWNLOAD
#####################
#default download_git.sh : populate source path via git
#go to sources file


if [ -e "./src/.git" ]
then
    cd src
    CURRENT=$(git rev-parse HEAD)
    local_log "current status 'HEAD' ${CURRENT}" 
    if [ "${COMMIT}" != "none" ] && [ "${CURRENT}" != "${COMMIT}" ]
    then 
        RESULT=1
    else
        verify_store_backup "${STORE}/${PROJECT}_${BRANCH}_${COMMIT}.tar.bz2"
    fi 
else
    RESULT=1    
fi

# @cake
#####################