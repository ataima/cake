
#function to expand tar zip files
# $1 input file ex pippo.tar.bz2
# $2 output
# var PACKEXT must be defined from c++
function expand_to(){
    if [ $1 != "" ] && [ $2 != "" ] && [ ${PACKEXT} != "" ]
    then
        if [ ${PACKEXT} == "tar" ]
        then 
            local_log "Untar $1 to $2"
            tar -xf "$1" -C "$2" >> $LOG 2>&1
            RESULT=$?
        else
            if [ ${PACKEXT} == "zip" ]
            then 
                local_log "Unzip $1 to $2 "
                unzip -u "$1"  -d "$2" >> $LOG 2>&1
                RESULT=$?
            fi
        fi        
    else
        RESULT=1
    fi
}
