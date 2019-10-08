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

