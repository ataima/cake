#
#####################
#--> APT POST DOWNLOAD
#####################
#default download.sh : populate source path via svn

if [ -e "./src" ]
then
    cd src
    verify_store_backup "${STORE}/${PROJECT}_APT.tar.bz2"
else
    RESULT=1    
fi

# @cake
#####################