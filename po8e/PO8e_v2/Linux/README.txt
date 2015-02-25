Included files:
 - drivers/KERNEL_VERSION/Plx9054.ko
 - patches/*.patch
 - mkDevs
 - PO8e.h
 - libPO8eStreaming.so
 - PO8eTest
 - PO8eTest.cpp


 -- The .ko Driver Files --
The .ko file provides the PlxApi verison 7.11 kernel driver for the
PLX chip that the PO8e uses to communicate with the PCI-Express bus.
The included .ko file(s) were built on a linux machines running the
kernel versions specified in the directory names.

A user running as root on a machine with the same kernel version
should be able to insert the .ko file into the currently running
kernel using the insmod (or modprobe) command:

insmod path/to/Plx9054.ko

On success the command will print nothing, but if there are any errors
then you will most likely need to recompile the PLX driver.  The
source code for this driver can be found at:
http://www.plxtech.com/products/sdk/pde

Details for compiling the Plx9054 driver can be found within the sdk
package from PLX, but the short version can be seen in the buildPLX
script.


 -- buildPLX and patches/ folder -- 
Script demonstrating the basic build process in case the provided
kernel modules do not include the module for your kernel.  Simply
running ./buildPLX on a machine with the kernel development package
installed should be enough to generate a .ko module for the running
kernel.

The patches included in the patches/ folder are automatically applied
by the buildPLX script.  This should allow the driver to build against
most recent kernels.  In the case of build errors please check for
newer versions of the PLX API and/or contact TDT.


 -- mkDevs --
After loading the Plx9054 kernel module this script can be used to
create the necessary device files in /dev/plx.


 -- The .h and .so Files --
These two files are required to compile an application that can
interface with the data stream coming over the PO8e card.  Details of
the API are beyond the scope of this document.  Note that the libary
is built for the x86_64 architecture.


 -- PO8eExample executable --
The PO8eExample executable uses the libPO8eStreaming.so library to
collect data from the installed PO8e card.  When the application
starts it attempts to connect to the PO8e card, waits for a data
stream to start, and prints status messages as data flows.  This
executable is built for the x86_64 architecture.


 -- PO8eExample.cpp --
Source code for the previous executable.
