#default download_git.sh : populate source path via git
#go to sources file
pushd ${SOURCE}

# check exist .git
if [ ! -e "./src" ]
then 
if [ ${BRANCH} == "" ] || [ ${BRANCH} == "master" ]
then 
    echo $(date) " : download_git.sh  $SOURCE from ${URL}/${FILE}" > $LOG  2>&1
    git clone "${URL}/${FILE}" src >> ${LOG}
    RESULT=$?
else
    echo $(date) " : download_git.sh  $SOURCE  from ${URL}/${FILE} with branch ${BRANCH}" > $LOG  2>&1
    git clone "${URL}/${FILE}"  -b ${BRANCH} >> ${LOG} 2>&1
    RESULT=$?
fi
cd src
if [ ${COMMIT} != "" ] && [ ${RESULT} -eq 0 ]
then
    git checkout ${COMMIT} >> ${LOG} 2>&1
    RESULT=$?
    [ ${RESULT} -eq 0 ] &&  echo $(date) " : download_git.sh  : checking out ${COMMIT}" >>  $LOG  2>&1
fi
fi
popd 
pushd ${SOURCE}

if [ -e "./src/.git" ]
then
    cd src
        CURRENT=$(git rev-parse HEAD)
        echo $(date) " : download_git.sh  current status 'HEAD' ${CURRENT}" >> $LOG  2>&1
    if [ "${CURRENT}" != "${COMMIT}" ]
    then 
        RESULT=1
    else
        if [ ! -e "${STORE}/${PROJECT}_${COMMIT}.tar.bz2" ]
        then 
            tar -cjvSf "${STORE}/${PROJECT}_${COMMIT}.tar.bz2"  * >/dev/null
            RESULT=$?
            if [ ${RESULT} -eq 0 ]
            then
                md5sum "${STORE}/${PROJECT}_${COMMIT}.tar.bz2" > "${STORE}/${PROJECT}_${COMMIT}.tar.bz2.md5"     
                chmod 444 "${STORE}/${PROJECT}_${COMMIT}.tar.bz2"
                chmod 444 "${STORE}/${PROJECT}_${COMMIT}.tar.bz2.md5"
                echo $(date) " : download_git.sh : create backup at : ${STORE}/${PROJECT}_${COMMIT}.tar.bz2" >> $LOG  2>&1
            fi
        fi
    fi 
else
    RESULT=1    
fi
#return main root
popd 
# if OK stop download
if [ ${RESULT} -eq  0 ]
then 
    echo $(date) " : download_git.sh : done" >> $LOG  2>&1	
    exit 0
fi