
#
#https://github.com/ataima/qxmlc.git
#


define remove_file   
    $(shell rm -rf  $1 | true )
endef


all: compile 

camainconf.cpp: camainconf.xml
	ca_qxmlc --verbose 7  camainconf.xml
	@cp ./camainconf.cpp ../ca_libcake/src/.
	@cp ./camainconf.h   ../ca_libcake/inc/.

compile: camainconf.cpp 




clean:
	$(call remove_file , "../ca_libcake/src/camainconf.cpp")
	$(call remove_file , "../ca_libcake/inc/camainconf.h")
	$(call remove_file , "./camainconf.cpp")
	$(call remove_file , "./camainconf.h")



