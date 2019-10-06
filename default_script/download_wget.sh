#
#####################
#--> WGET DOWNLOAD
#####################
#default download.sh : populate source path via wget
#go to sources file

pushd ${SOURCE}

# check exist .git
if [ ! -e "./src" ] || [ ${FORCE} == "Y" ]
then 
    local_log "$SOURCE from ${URL}/${FILE}"
    wget --show-progress -q "${URL}/${FILE}" -O "${FILE}"
    RESULT=$?
    if [ ${RESULT} -ne 0 ]
    then        
        rm -f "${FILE}"
        local_log "ERROR on download source from ${URL}/${FILE}"
    else
        local_log "Downloaded source from ${URL}/${FILE}" 
        [ ${FORCE} == "Y" ] && rm -rf "src"
        mkdir -p "src"
        if [ ${PACKEXT} != "" ]
        then
            local_log "Expand source from ${URL}/${FILE} to ./src"
            expand_to "${FILE}" "./src"
            [ ${RESULT} -ne 0 ] && rm -rf "./src" && rm -f "${FILE}"
        else  
            #have downloaded a directory
            if [ -d "${FILE}" ]  
            then
                local_log "Copy source from ${URL}/${FILE} to ./src"
                mv "${FILE}/*" "./src/."
                rm -rf "${FILE}"
                RESULT=0
            fi
            if [ -f "${FILE}" ]  
            then
                local_log "Copy source from ${URL}/${FILE} to ./src"
                mv "${FILE}" "./src/."
                rm -f "${FILE}"
                RESULT=0;
            fi            
        fi
    fi
fi

popd 

pushd ${SOURCE}

if [ ${RESULT} -eq 0 ] && [ -e "./src" ]
then
    if [ ${PACKEXT} != "" ]
    then
        if [ -f "${STORE}/${FILE}" ]
        then 
            chmod 666 "${STORE}/${FILE}"
            chmod 666 "${STORE}/${FILE}.md5"
            rm -rf "${STORE}/${FILE}"
            rm -rf "${STORE}/${FILE}.md5"
        fi
        mv "${FILE}" "${STORE}/${FILE}"
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
#return main root
popd 
# if OK stop download phase and NOT continue script
if [ ${RESULT} -eq  0 ]
then 
    local_log_close
fi