# test and download a key sign  to check source code
function download_key_sign(){
if [ ${RESULT} -eq 0 ] && [ "${KEYURL}" != "N" ] 
then
    if [ ! -e "./sign" ] || [ ${FORCE} == "Y" ]
    then
        local_log "KEYSIGN from ${KEYURL}"
        if [ -e "./sign" ]
        then 
            local_log "remove old keysign file"
            # force = Y
            chmod 0666  "./sign/*"
            rm -rf "./sign"
        fi
        mkdir -p "./sign"
        wget --show-progress -q "${KEYURL}" -O "./sign/signature.${KEYEXT}"
        RESULT=$?
        if [ ${RESULT} -ne 0 ]
        then
            local_log "fail to download keysign file  ${KEYURL}"
            rm -rf "./sign"
        else
            local_log "download keysign file  ${KEYURL} done"
            chmod 0444  "./sign/signature.${KEYEXT}"
        fi
    fi
fi
}

