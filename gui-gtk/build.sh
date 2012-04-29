binobj=wifidump
rm -rf ${binobj}
gcc wifidump.c -o ${binobj} `pkg-config --cflags --libs gtk+-2.0`

