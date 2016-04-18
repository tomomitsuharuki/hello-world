#!/bin/bash
echo git archive
#rm -rf tmp/*
git archive --format=tar master test_app | tar -C merge -xf -
git log > merge/log.txt
