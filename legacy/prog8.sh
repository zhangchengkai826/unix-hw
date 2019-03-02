#!/bin/bash
cc -g ct2awk.c apue.c -o ct2awk
./ct2awk prog8.ct prog8.awk
cat prog8.awk

