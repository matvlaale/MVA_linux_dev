#!/bin/bash

ch_sha1=$(sha1sum rhasher.c | awk '{ print $1 }')
ch_md5=$(md5sum rhasher.c | awk '{ print $1 }')

my_sha1=$(echo "SHA1 rhasher.c" | ./rhasher | tail -n 2 | head -n 1)
my_md5=$(echo "MD5 rhasher.c" | ./rhasher | tail -n 2 | head -n 1)

echo "$my_sha1"
echo "$ch_sha1"
echo "$my_md5"
echo "$ch_md5"

if [ "$my_sha1" != "$ch_sha1" ]; then
    echo "SHA1 hashes do not match!"
    exit 0
fi
if [ "$my_md5" != "$ch_md5" ]; then
    echo "MD5 hashes do not match!"
    exit 0
fi
echo "All hashes match"
