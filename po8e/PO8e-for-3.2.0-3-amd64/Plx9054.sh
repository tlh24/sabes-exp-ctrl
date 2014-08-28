#!/bin/sh

MAJOR=`grep Plx9054 /proc/devices | sed 's/ Plx9054//'`

if [ -n "$MAJOR" ]; then
	mkdir /dev/plx
	mknod /dev/plx/Plx9054 c $MAJOR 255
	mknod /dev/plx/Plx9054-0 c $MAJOR 0
	mknod /dev/plx/Plx9054-1 c $MAJOR 1
	mknod /dev/plx/Plx9054-2 c $MAJOR 2
	mknod /dev/plx/Plx9054-3 c $MAJOR 3
	chmod -R 777 /dev/plx
fi
