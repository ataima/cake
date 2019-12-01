#
#####################
#--> APT DOWNLOAD
#####################
#default download.sh : populate source path via svn


# check exist .src or force from param input
if [ ! -e "./src" ] || [ ${FORCE} == "Y" ]
then 
    local_log "$SOURCE from ${FILE}"
    pushd /tmp
    apt-get source "${FILE}" >> ${LOG} 2>&1
    RESULT=$?
    if [ ${RESULT} -ne 0 ]
    then        
        rm -f "${FILE}"
        local_log "ERROR on download source from ${FILE}"
    else
        local_log "Downloaded source from ${FILE}" 
        popd
        [ ${FORCE} == "Y" ] && rm -rf "src"
        mkdir -p "src"
        mv "/tmp/${FILE}"  "./src"
        RESULT=$?
    fi
fi

if [ ${RESULT} -eq 0 ]
    then
        remove_store_backup "${STORE}/${PROJECT}_${CURRENT}.tar.bz2"
        local_log " FAIL to DOWNLOAD SVN FILE : ${URL}/${FILE}"
    fi

# check exist key sign to download
download_key_sign

# @cake
#####################
