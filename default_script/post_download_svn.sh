#
#####################
#--> SVN POST DOWNLOAD
#####################
#default download.sh : populate source path via svn


if [ -e "./src/.svn" ]
then
    cd src
    CURRENT=$(svn info --show-item revision)
    local_log "current status 'HEAD' ${CURRENT}"
    if [ "${REVISION}" == "HEAD" ]
    then
         verify_store_backup "${STORE}/${PROJECT}_${CURRENT}.tar.bz2"
    else
    if [ "${CURRENT}" != "${REVISION}" ]
    then
        local_log "Errore request revision ${REVISION} , actual ${CURRENT}"
        RESULT=1
    else
        verify_store_backup "${STORE}/${PROJECT}_${REVISION}.tar.bz2"
    fi
    fi
else
    RESULT=1
fi



# @cake
#####################