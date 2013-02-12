Included files:
 - Plx9054.ko
 - PLX-kernelVer.patch
 - mkDevs
 - PO8e.h
 - libPO8eStreaming.so
 - PO8eTest
 - PO8eTest.cpp


 -- The .ko Driver File --
The .ko file provides the PlxApi verison 6.50 kernel driver for the
PLX chip that the PO8e uses to communicate with the PCI-Express bus.
The included .ko was built on a 64-bit Debian stable system running
the linux-image-3.2.0-0.bpo.3-amd64 kernel backported from Debian
unstable.

A user running as root on a machine with the same kernel version
should be able to insert the .ko file into the currently running
kernel using the insmod (or modprobe) command:

insmod Plx9054.ko

On success the command will print nothing, but if there are any errors
then you will most likely need to recompile the PLX driver.  The
source code for this driver can be found at:
http://www.plxtech.com/products/sdk/pde

Registration is required, but is free.  Details for compiling the
Plx9054 driver can be found within the sdk package from PLX.


 -- PLX-kernelVer.patch --
If you are using a kernel later than 2.6 and are compiling the Plx9054
kernel obejct you will need to remove a version check from the PPLX
source code.  This patch contains the changes necessary to bump the
version check from 2.6 to 3.2


 -- mkDevs --
After loading the Plx9054 kernel module this script can be used to
create the necessary device files in /dev/plx.


 -- The .h and .so Files --
These two files are required to compile an application that can
interface with the data stream coming over the PO8e card.  Details of
the API are beyond the scope of this document


 -- PO8eTest executable --
The PO8eTest executable uses the libPO8eStreaming.so library to
collect data from the installed PO8e card.  When the application
starts it attempts to connect to the PO8e card, waits for a data
stream to start, and prints status messages as data flows.


 -- PO8eTest.cpp --
Source code for the previous executable.
