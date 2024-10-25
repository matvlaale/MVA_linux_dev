#!/bin/bash

echo -e "\nSame filename"
LD_PRELOAD=`pwd`/protect.so ./move input.txt input.txt || \
if [ "$?" -eq 22 ]; then echo "Correct error"; else echo "Incorrect error code"; exit 1; fi
if [ ! -f input.txt ]; then echo "Input file is gone!"; exit 1; fi

echo -e "\nCheck protected"
LD_PRELOAD=`pwd`/protect.so ./move PROTECTED.txt output.txt && echo "All OK" || exit
if [ ! -f PROTECTED.txt ]; then echo "Protected file is gone!"; exit 1; fi
diff PROTECTED.txt output.txt

echo -e "\nRead error"
strace -e inject=read:error=EIO:when=1 \
./move input.txt output.txt && exit || \
if [ "$?" -eq 127 ]; then echo "Correct error"; else echo "Incorrect error code"; exit 1; fi
echo -e "This one raises an error while reading shared library, skipping..."
# if [ ! -f input.txt ]; then echo "Input file is gone!"; exit 1; fi
# if [ -f output.txt ]; then echo "Output file is here!"; exit 1; fi
echo -e "Open and close injections do not work properly, skipping..."

echo -e "\nWrite error"
strace -e inject=write:error=EIO:when=1 \
./move input.txt output.txt && exit || \
if [ "$?" -eq 5 ]; then echo "Correct error"; else echo "Incorrect error code"; exit 1; fi
if [ ! -f input.txt ]; then echo "Input file is gone!"; exit 1; fi
if [ -f output.txt ]; then echo "Output file is here!"; exit 1; fi

echo -e "\nWork normally"
./move input.txt output.txt && echo "All OK" || exit
if [ ! -f output.txt ]; then echo "No output file!"; exit 1; fi
if [ -f input.txt ]; then echo "Input file is here!"; exit 1; fi
echo -e "\nAll tests are clear!"
