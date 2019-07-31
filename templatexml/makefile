
#
#https://github.com/ataima/qxmlc.git
#


define remove_file   
    $(shell rm -rf  $1 | true )
endef


all: compile 

camainconf.cpp: camainconf.xml
	ca_qxmlc --verbose 7   --out_path  ./mainconf   camainconf.xml
	@cp ./mainconf/camainconf.cpp ../ca_libcake/src/.
	@cp ./mainconf/camainconf.h   ../ca_libcake/inc/.


calayerconf.cpp: calayerconf.xml	
	ca_qxmlc --verbose 7  --out_path  ./layerconf   calayerconf.xml
	@cp ./layerconf/calayerconf.cpp ../ca_libcake/src/.
	@cp ./layerconf/calayerconf.h   ../ca_libcake/inc/.

compile: camainconf.cpp calayerconf.cpp




clean:
	$(call remove_file , "../ca_libcake/src/camainconf.cpp")
	$(call remove_file , "../ca_libcake/inc/camainconf.h")
	$(call remove_file , "../ca_libcake/src/calayerconf.cpp")
	$(call remove_file , "../ca_libcake/inc/calayerconf.h")
	$(call remove_file , "./mainconf")
	$(call remove_file , "./layerconf")



