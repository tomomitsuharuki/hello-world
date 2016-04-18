#!/bin/bash

git log --pretty=format:'%C(yellow)commit: %h%Creset %x0A %ci %x0A %s %x0A' master..log_test
echo ----- change files -----
git diff --name-status master...log_test

