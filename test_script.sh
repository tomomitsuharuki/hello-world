#!/bin/bash

echo Test[$TEST_ENV]
if [ "$TEST_ENV" == "" ]; then
    echo Test Env Emplty!
    exit
fi


