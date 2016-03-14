#!/bin/bash
TEST_VALS=(
"Skakal pes přes pes přes oves.\n"
"Word Word\n"
"Hi I'm Jakub. Hi I'm Jakub.\n"
"First. Second. First\n"
"Hi I'm \nJakub. Hi \nI'm Jakub.\n"
"Skakal pes          pres oves. Skakal pes pres oves.\n"
)
CORR_VALS=(
"Skakal pes přes oves.\n"
"Word \n"
"Hi I'm Jakub. \n"
"First. Second. First\n"
"Hi I'm \nJakub. \n"
"Skakal pes pres oves. \n"
)

IDX=1

for i in ${!TEST_VALS[*]} ; do
    echo -ne "${TEST_VALS[$i]}" > /tmp/test_input.txt
    echo -ne "${CORR_VALS[$i]}" > /tmp/test_right.txt
    ./replace /tmp/test_input.txt /tmp/test_output.txt
    if ! diff /tmp/test_right.txt /tmp/test_output.txt > /dev/null ; then
        echo "Test $IDX failed"
        exit 1
    fi
    echo "Test $IDX OK"
    (( IDX++ ))
done
rm /tmp/test_input.txt /tmp/test_right.txt /tmp/test_output.txt

