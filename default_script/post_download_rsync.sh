# @cake
#####################
#--> RSYNC POST DOWNLOAD
#####################
#default download_rsync.sh : populate source path via rsync
#go to sources file

if [ -e "./src" ]
then
    cd src
    verify_store_backup "${STORE}/${PROJECT}_RSYNC.tar.bz2"
else
    RESULT=1    
fi

# @cake
#####################
