#!/bin/bash

git log --pretty=format:'commit: %h %x0A %ci %x0A %s%- ' master..log_test
echo ----- change files -----
git diff --name-status master...log_test

