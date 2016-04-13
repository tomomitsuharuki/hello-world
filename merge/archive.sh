#!/bin/bash
echo git archive
#rm -rf tmp/*
cd ..
git archive --verbose --format=tar master test_app | tar -C merge -xf -
git log > merge/log.txt
