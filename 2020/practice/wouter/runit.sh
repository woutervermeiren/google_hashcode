#!/bin/bash

EXECUTABLE="./gh_practice_2020.out"
if [ ! -x "$EXECUTABLE" -o ! -f "$EXECUTABLE" ]; then
	echo "[ERROR] No executable found!"
	exit 1
fi

INPUT_FILE="$1"

if [ $# -ne 1 ] ; then
	INPUT_FILE="../a_example.in"
fi

OUTPUT_FILE="solution_$(basename \"${INPUT_FILE%.in\"}).txt"
CMD="cat ${INPUT_FILE} | ${EXECUTABLE} > ${OUTPUT_FILE}"
echo "####################################"
echo "Running: $CMD"
echo "####################################"
eval $CMD
echo "###### START OUTPUT FILE ###########"
cat "$OUTPUT_FILE"
echo "####### END OUTPUT FILE ############"
