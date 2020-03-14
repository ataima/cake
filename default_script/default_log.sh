
#
# DEFAULT LOG 

FORCE=$1

[ ! ${FORCE} ] && FORCE="N"

declare -i start_time
declare -i stop_time
declare -i total_time

start_time=$(date +%s)

# print simple log 
# $1..$n param
function local_log(){
    if [ ${FORCE} == "Y" ]
    then
        echo $(date) " : ${SCRIPTNAME} : FORCED! " >> ${LOG}  2>&1
        echo "      --> $@" >> ${LOG}  2>&1
    else
        echo $(date) " : ${SCRIPTNAME}  :" >> ${LOG}  2>&1
        echo "      --> $@" >> ${LOG}  2>&1
    fi
}

# limit max num line log to 1000
function check_limit_log(){
if [ -e ${LOG} ]
then
    LOGSZ=$(wc -l ${LOG} | awk '{ print $1 }')
    if [ ${LOGSZ} -gt 1000 ]
    then
        tmplog=$(mktemp /tmp/cake_log.XXXXXX)
        echo "-------- WARNING LOG TOO LONG ---> TRUNCATE TO 100 LINES --------" > ${tmplog}
        tail -n 200 ${LOG} >>  ${tmplog}
        mv ${tmplog} ${LOG}
    fi
fi
}

# function log close script
function local_log_close(){
stop_time=$(date +%s)
total_time=$((stop_time-start_time))
local_log "done : " "${total_time} sec"
exit ${RESULT}
}


check_limit_log
local_log " START : $@"



