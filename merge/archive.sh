#!/bin/bash
echo git archive
cd ..
git archive --verbose --format=tar master test_app | tar -C merge/archive -xf -
