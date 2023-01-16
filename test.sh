#!/bin/bash

## PATH VARS
BIN_PATH=./cub3D
MAKE_PATH=./
ASSETS_PATH=./assets

RED='\033[031m'
GREEN='\033[032m'
YELLOW='\033[033m'
BLUE='\033[034m'
MAGENTA='\033[035m'
MAGENTA_2='\033[095m'
CYAN='\033[036m'
RE='\033[0m'

OK="${GREEN} [OK] ${RE}"
KO="${RED} [KO] ${RE}"

HAS_ERROR=0

## TEST FUNCTION DEFINITION
run_test_case() {
	CASE=$1
    EXPECT=$2

    OUTPUT=$($BIN_PATH $CASE | tr -d '\n')

    if [ "$OUTPUT" == "$EXPECT" ]; then
        echo -en ${GREEN} "[OK]" ${RE}
    else
        echo -en ${RED} "[KO]" ${RE}
        HAS_ERROR=1
    fi
}

run_norminette() {
    if which norminette > /dev/null; then
        norminette */*.c */*.h >&-
        if [ `echo $?` == "1" ]; then
            echo -en "\n Test norminette: $KO"
            HAS_ERROR=1
        else
            echo -en "\n Test norminette: $OK"
        fi
    else
        echo "\n Norminette not installed"
        HAS_ERROR=1
    fi
}

run_valgrind() {
    valgrind --leak-check=full $BIN_PATH &> valgrind_output.txt
    LEAK_OUTPUT=$(grep "definitely lost" valgrind_output.txt)
    if [[ $LEAK_OUTPUT == *"definitely lost"* ]]; then
        echo -en "\n Test valgrind: $KO"
        HAS_ERROR=1
    else
        echo -en "\n Test valgrind: $OK"
    fi
    rm valgrind_output.txt
}

## RUN SCRIPT

echo -e "\nTest $YELLOW STARTED $RE"

make all --no-print-directory -C $MAKE_PATH

run_norminette
run_valgrind

echo -en "\n Test file extension: "
run_test_case "$ASSETS_PATH/map.cub" "The file extension is '.cub'"
run_test_case "$ASSETS_PATH/map2.cub" "The file extension is '.cub'"
run_test_case "$ASSETS_PATH/map.cub.txt" "The file extension is NOT .cub"
run_test_case "$ASSETS_PATH/map.txt" "The file extension is NOT .cub"
echo -e "\n"

make fclean --no-print-directory -C $MAKE_PATH

if [ $HAS_ERROR == "1" ]; then
    echo -e "\n Test $RED FAILED $RE"
else
    echo -e "\n Test $GREEN SUCCEED $RE"
fi

exit $HAS_ERROR
