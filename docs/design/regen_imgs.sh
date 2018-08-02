#!/bin/sh

which plantuml 2>/dev/null > /dev/null

PLANT_UML_EXISTS="${?}"

if [[ ${PLANT_UML_EXISTS} -gt 0 ]]; then
   echo "ERROR: no plantuml in system"
   exit ${PLANT_UML_EXISTS}
fi
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ${DIR}
make

echo "OK"
