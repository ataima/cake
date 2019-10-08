# @cake
#####################
#--> RSYNC DOWNLOAD
#####################
#default download_rsync.sh : populate source path via rsync
#go to sources file

pushd ${SOURCE}

# check exist .src
if [ ! -e "./src" ] || [ ${FORCE} == "Y" ]
then 
    mkdir -p "./src"
    rsync -ry ${URL}/${FILE} "./src/."  >> $LOG  2>&1
    RESULT=$?
    if [ ${RESULT} -ne 0 ] 
    then
        rm -rf "./src"
        local_log " FAIL to DOWNLOAD RSYNC FILE : ${URL}/${FILE}"
    else
        local_log " DOWNLOAD RSYNC FILE : ${URL}/${FILE} OK"
        if [ -e "${STORE}/${PROJECT}_RSYNC.tar.bz2" ]
        then 
            remove_store_backup "${STORE}/${PROJECT}_RSYNC.tar.bz2" 
        fi
    fi
fi

// check exist key sign to download
download_key_sign


popd 