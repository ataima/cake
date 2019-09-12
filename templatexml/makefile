
#
#https://github.com/ataima/qxmlc.git
#


define remove_file   
    $(shell rm -rf  $1 | true )
endef
.PHONY: all clean compile

all: compile 

camainconf.cpp: camainconf.xml
	ca_qxmlc --verbose 7   --out_path  ./mainconf   camainconf.xml
	@cp ./mainconf/camainconf.cpp ../ca_libcake/src/.
	@cp ./mainconf/camainconf.h   ../ca_libcake/inc/.
	@cp ./mainconf/camainconf.cpp .


calayerconf.cpp: calayerconf.xml	
	ca_qxmlc --verbose 7  --out_path  ./layerconf   calayerconf.xml
	@cp ./layerconf/calayerconf.cpp ../ca_libcake/src/.
	@cp ./layerconf/calayerconf.h   ../ca_libcake/inc/.
	@cp ./layerconf/calayerconf.cpp .


castatusconf.cpp: castatusconf.xml
	ca_qxmlc --verbose 7  --out_path  ./statusconf   castatusconf.xml
	@cp ./statusconf/castatusconf.cpp ../ca_libcake/src/.
	@cp ./statusconf/castatusconf.h   ../ca_libcake/inc/.
	@cp ./statusconf/castatusconf.cpp .


caprojectconf.cpp: caprojectconf.xml
	ca_qxmlc --verbose 7  --out_path  ./projectconf   caprojectconf.xml
	@cp ./projectconf/caprojectconf.cpp ../ca_libcake/src/.
	@cp ./projectconf/caprojectconf.h   ../ca_libcake/inc/.
	@cp ./projectconf/caprojectconf.cpp .


compile: camainconf.cpp calayerconf.cpp castatusconf.cpp caprojectconf.cpp




clean:
	@rm -f camainconf.cpp
	@rm -f calayerconf.cpp
	@rm -f castatusconf.cpp
	@rm -f caprojectconf.cpp
	$(call remove_file , "../ca_libcake/src/camainconf.cpp")
	$(call remove_file , "../ca_libcake/inc/camainconf.h")
	$(call remove_file , "../ca_libcake/src/calayerconf.cpp")
    $(call remove_file , "../ca_libcake/inc/calayerconf.h")
    $(call remove_file , "../ca_libcake/src/castatusconf.cpp")
    $(call remove_file , "../ca_libcake/inc/castatusconf.h")
    $(call remove_file , "../ca_libcake/src/caprojectconf.cpp")
    $(call remove_file , "../ca_libcake/inc/caprojectconf.h")
    $(call remove_file , "./mainconf")
    $(call remove_file , "./layerconf")
    $(call remove_file , "./statusconf")
    $(call remove_file , "./projectconf")

	

