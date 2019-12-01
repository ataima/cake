#
#####################
#--> SVN DOWNLOAD
#####################
#default download.sh : populate source path via svn
# go to source file



# check exist .src 
if [ ! -e "./src" ] || [ ${FORCE} == "Y" ]
then
    if  [ "${REVISION}" == "HEAD" ]
    then
        local_log "$SOURCE from ${URL}/${FILE}"
        svn  --non-interactive -q co ${URL}/${FILE} src  >> ${LOG} 2>&1
        RESULT=$?
    else
        locaL-log "$SOURCE  from ${URL}/${FILE} with revision ${REVISION}"
        svn  --non-interactive  -q co ${URL}/${FILE} -r ${REVISION} src  >> ${LOG} 2>&1
        RESULT=$?
    fi

    if [ ${RESULT} -eq 0 ]
    then
        cd src
        CURRENT=$(svn info --show-item revision)
        remove_store_backup "${STORE}/${PROJECT}_${CURRENT}.tar.bz2"
    fi
fi

# check exist key sign to download
download_key_sign


# @cake
#####################
