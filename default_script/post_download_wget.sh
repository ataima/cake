#
#####################
#--> WGET DOWNLOAD
#####################
#default download.sh : populate source path via wget
#go to sources file



if  [ -e "./src" ]
then
    if [ ${PACKEXT} != "" ]
    then
        if [ -f "${FILE}" ] && [ -f "${STORE}/${FILE}" ]
        then 
            chmod 666 "${STORE}/${FILE}"
            rm -rf "${STORE}/${FILE}"
        fi
        if [ -f "${STORE}/${FILE}.md5" ]
        then 
            chmod 666 "${STORE}/${FILE}.md5"
            rm -rf "${STORE}/${FILE}.md5"
        fi
        [ -f "${FILE}" ] && mv "${FILE}" "${STORE}/${FILE}"
        md5sum "${STORE}/${FILE}" > "${STORE}/${FILE}.md5"     
            chmod 444 "${STORE}/${FILE}"
            chmod 444 "${STORE}/${FILE}.md5"
            local_log "create backup at : ${STORE}/${FILE}"
    else    
        cd src
        verify_store_backup "${STORE}/${PROJECT}_WGET.tar.bz2"
    fi    
else
    RESULT=1    
fi



# @cake
#####################