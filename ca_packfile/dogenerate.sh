#!/bin/sh



PWD=$(pwd)
mkdir -p ${PWD}/generated
make -C ../build/ca_packfile install
../Debuglinux64/ca_packfile --out ${PWD}/generated/capackedfile ../default_script




