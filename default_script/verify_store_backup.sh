#
# VERIFY / REMOVE SOURCE STORE IN STORE PATH

#$1 STORE FULLPATH NAME
function remove_store_backup(){
    if [ -e "$1" ]
    then 
        chmod 666 "$1"
        chmod 666 "$1.md5"
        rm -f "$1.md5"
        rm -f "$1"
        RESULT=$?
        if [ ${RESULT} -eq 0 ]
        then
            local_log  "remove old backup at : $1"
        else
            local_log "ERROR on remove old source backup $1"     
        fi
    fi
}

#$1 STORE FULLPATH NAME
function verify_store_backup(){
    if [ ! -e "$1" ]
    then 
        tar -cjvSf "$1"  * >/dev/null
        RESULT=$?
        if [ ${RESULT} -eq 0 ]
        then
            md5sum "$1" > "$1.md5"     
            chmod 444 "$1"
            chmod 444 "$1.md5"
            local_log "create backup at : $1"
        else
            local_log "ERROR on create source backup $1"     
        fi
    fi
}

