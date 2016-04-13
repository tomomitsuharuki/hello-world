#!/bin/bash
echo git archive
rm -rf tmp/*
cd ..
git archive --verbose --format=tar master test_app | tar -C merge/tmp -xf -
git log > merge/tmp/log.txt
