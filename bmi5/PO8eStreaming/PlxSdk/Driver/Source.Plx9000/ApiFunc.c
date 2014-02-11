/*******************************************************************************
 * Copyright (c) PLX Technology, Inc.
 *
 * PLX Technology Inc. licenses this source file under the GNU Lesser General Public
 * License (LGPL) version 2.  This source file may be modified or redistributed
 * under the terms of the LGPL and without express permission from PLX Technology.
 *
 * PLX Technology, Inc. provides this software AS IS, WITHOUT ANY WARRANTY,
 * EXPRESS OR IMPLIED, INCLUDING, WITHOUT LIMITATION, ANY WARRANTY OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  PLX makes no guarantee
 * or representations regarding the use of, or the results of the use of,
 * the software and documentation in terms of correctness, accuracy,
 * reliability, currentness, or otherwise; and you rely on the software,
 * documentation and results solely at your own risk.
 *
 * IN NO EVENT SHALL PLX BE LIABLE FOR ANY LOSS OF USE, LOSS OF BUSINESS,
 * LOSS OF PROFITS, INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES
 * OF ANY KIND.
 *
 ******************************************************************************/

/*******************************************************************************
 *
 * File Name:
 *
 *      ApiFunc.c
 *
 * Description:
 *
 *      Implements the PLX API functions
 *
 * Revision History:
 *
 *      02-01-13 : PLX SDK v7.00
 *
 ******************************************************************************/


#include <asm/uaccess.h>
#include <linux/sched.h>    // For MAX_SCHED_TIMEOUT & TASK_UNINTERRUPTIBLE
#include "ApiFunc.h"
#include "Eep_9000.h"
#include "PciFunc.h"
#include "PlxChipApi.h"
#include "PlxChipFn.h"
#include "PlxInterrupt.h"
#include "SuppFunc.h"




/*******************************************************************************
 *
 * Function   :  PlxDeviceFind
 *
 * Description:  Search for a specific device using device key parameters
 *
 ******************************************************************************/
PLX_STATUS
PlxDeviceFind(
    DEVICE_EXTENSION *pdx,
    PLX_DEVICE_KEY   *pKey,
    U16              *pDeviceNumber
    )
{
    U16            DeviceCount;
    BOOLEAN        bMatchId;
    BOOLEAN        bMatchLoc;
    DEVICE_OBJECT *fdo;


    DeviceCount = 0;

    // Get first device instance in list
    fdo = pdx->pDeviceObject->DriverObject->DeviceObject;

    // Compare with items in device list
    while (fdo != NULL)
    {
        // Get the device extension
        pdx = fdo->DeviceExtension;

        // Assume successful match
        bMatchLoc = TRUE;
        bMatchId  = TRUE;

        //
        // Compare device key information
        //

        // Compare Bus number
        if (pKey->bus != (U8)PCI_FIELD_IGNORE)
        {
            if (pKey->bus != pdx->Key.bus)
            {
                bMatchLoc = FALSE;
            }
        }

        // Compare Slot number
        if (pKey->slot != (U8)PCI_FIELD_IGNORE)
        {
            if (pKey->slot != pdx->Key.slot)
            {
                bMatchLoc = FALSE;
            }
        }

        // Compare Function number
        if (pKey->function != (U8)PCI_FIELD_IGNORE)
        {
            if (pKey->function != pdx->Key.function)
            {
                bMatchLoc = FALSE;
            }
        }

        //
        // Compare device ID information
        //

        // Compare Vendor ID
        if (pKey->VendorId != (U16)PCI_FIELD_IGNORE)
        {
            if (pKey->VendorId != pdx->Key.VendorId)
            {
                bMatchId = FALSE;
            }
        }

        // Compare Device ID
        if (pKey->DeviceId != (U16)PCI_FIELD_IGNORE)
        {
            if (pKey->DeviceId != pdx->Key.DeviceId)
            {
                bMatchId = FALSE;
            }
        }

        // Compare Subsystem Vendor ID
        if (pKey->SubVendorId != (U16)PCI_FIELD_IGNORE)
        {
            if (pKey->SubVendorId != pdx->Key.SubVendorId)
            {
                bMatchId = FALSE;
            }
        }

        // Compare Subsystem Device ID
        if (pKey->SubDeviceId != (U16)PCI_FIELD_IGNORE)
        {
            if (pKey->SubDeviceId != pdx->Key.SubDeviceId)
            {
                bMatchId = FALSE;
            }
        }

        // Compare Revision
        if (pKey->Revision != (U8)PCI_FIELD_IGNORE)
        {
            if (pKey->Revision != pdx->Key.Revision)
            {
                bMatchId = FALSE;
            }
        }

        // Check if match on location and ID
        if (bMatchLoc && bMatchId)
        {
            // Match found, check if it is the desired device
            if (DeviceCount == *pDeviceNumber)
            {
                // Copy the device information
                *pKey = pdx->Key;

                DebugPrintf((
                    "Criteria matched device %04X_%04X [b:%02x s:%02x f:%x]\n",
                    pdx->Key.DeviceId, pdx->Key.VendorId,
                    pdx->Key.bus, pdx->Key.slot, pdx->Key.function
                    ));

                return ApiSuccess;
            }

            // Increment device count
            DeviceCount++;
        }

        // Jump to next entry
        fdo = fdo->NextDevice;
    }

    // Return number of matched devices
    *pDeviceNumber = DeviceCount;

    DebugPrintf(("Criteria did not match any devices\n"));

    return ApiInvalidDeviceInfo;
}




/*******************************************************************************
 *
 * Function   :  PlxChipTypeGet
 *
 * Description:  Returns PLX chip type and revision
 *
 ******************************************************************************/
PLX_STATUS
PlxChipTypeGet(
    DEVICE_EXTENSION *pdx,
    U16              *pChipType,
    U8               *pRevision
    )
{
    *pChipType = pdx->Key.PlxChip;
    *pRevision = pdx->Key.PlxRevision;

    DebugPrintf((
        "PLX chip = %04X rev %02X\n",
        *pChipType, *pRevision
        ));

    return ApiSuccess;
}




/*******************************************************************************
 *
 * Function   :  PlxChipTypeSet
 *
 * Description:  Sets the PLX chip type dynamically
 *
 ******************************************************************************/
PLX_STATUS
PlxChipTypeSet(
    DEVICE_EXTENSION *pdx,
    U16               ChipType,
    U8                Revision
    )
{
    // Setting the PLX chip type is not supported in this PnP driver
    return ApiUnsupportedFunction;
}




/*******************************************************************************
 *
 * Function   :  PlxGetPortProperties
 *
 * Description:  Returns the current port information and status
 *
 ******************************************************************************/
PLX_STATUS
PlxGetPortProperties(
    DEVICE_EXTENSION *pdx,
    PLX_PORT_PROP    *pPortProp
    )
{
    DebugPrintf(("Device does not support PCI Express Capability\n"));

    // Set default value for properties
    RtlZeroMemory(pPortProp, sizeof(PLX_PORT_PROP));

    // Mark device as non-PCIe
    pPortProp->bNonPcieDevice = TRUE;

    // Default to a legacy endpoint
    pPortProp->PortType = PLX_PORT_LEGACY_ENDPOINT;

    return ApiSuccess;
}




/*******************************************************************************
 *
 * Function   :  PlxPciDeviceReset
 *
 * Description:  Resets a device using software reset feature of PLX chip
 *
 ******************************************************************************/
PLX_STATUS
PlxPciDeviceReset(
    DEVICE_EXTENSION *pdx
    )
{
    // Call chip-specific function
    return PlxChip_BoardReset(
        pdx
        );
}




/*******************************************************************************
 *
 * Function   :  PlxRegisterRead
 *
 * Description:  Reads a PLX-specific register
 *
 ******************************************************************************/
U32
PlxRegisterRead(
    DEVICE_EXTENSION *pdx,
    U32               offset,
    PLX_STATUS       *pStatus,
    BOOLEAN           bAdjustForPort
    )
{
    // Verify register offset
    if ((offset & 0x3) || (offset >= MAX_PLX_REG_OFFSET))
    {
        DebugPrintf(("ERROR - Invalid register offset (%X)\n", offset));

        if (pStatus != NULL)
            *pStatus = ApiInvalidOffset;

        return 0;
    }

    if (pStatus != NULL)
        *pStatus = ApiSuccess;

    return PLX_9000_REG_READ(
               pdx,
               offset
               );
}




/*******************************************************************************
 *
 * Function   :  PlxRegisterWrite
 *
 * Description:  Writes to a PLX-specific register
 *
 ******************************************************************************/
PLX_STATUS
PlxRegisterWrite(
    DEVICE_EXTENSION *pdx,
    U32               offset,
    U32               value,
    BOOLEAN           bAdjustForPort
    )
{
    // Verify register offset
    if ((offset & 0x3) || (offset >= MAX_PLX_REG_OFFSET))
    {
        DebugPrintf(("ERROR - Invalid register offset (%X)\n", offset));
        return ApiInvalidOffset;
    }

    PLX_9000_REG_WRITE(
        pdx,
        offset,
        value
        );

    return ApiSuccess;
}




/*******************************************************************************
 *
 * Function   :  PlxPciBarProperties
 *
 * Description:  Returns the properties of a PCI BAR space
 *
 ******************************************************************************/
PLX_STATUS
PlxPciBarProperties(
    DEVICE_EXTENSION *pdx,
    U8                BarIndex,
    PLX_PCI_BAR_PROP *pBarProperties
    )
{
    // Verify BAR number
    switch (BarIndex)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            break;

        default:
            return ApiInvalidIndex;
    }

    // Return BAR properties
    *pBarProperties = pdx->PciBar[BarIndex].Properties;

    // Display BAR properties if enabled
    if (pdx->PciBar[BarIndex].Properties.Size == 0)
    {
        DebugPrintf(("BAR %d is disabled\n", BarIndex));
        return ApiSuccess;
    }

    DebugPrintf((
        "    PCI BAR %d: %08llX\n",
        BarIndex, pdx->PciBar[BarIndex].Properties.BarValue
        ));

    DebugPrintf((
        "    Phys Addr: %08llX\n",
        pdx->PciBar[BarIndex].Properties.Physical
        ));

    DebugPrintf((
        "    Size     : %08llX (%lld %s)\n",
        pdx->PciBar[BarIndex].Properties.Size,
        pdx->PciBar[BarIndex].Properties.Size < ((U64)1 << 10) ?
            pdx->PciBar[BarIndex].Properties.Size :
            pdx->PciBar[BarIndex].Properties.Size >> 10,
        pdx->PciBar[BarIndex].Properties.Size < ((U64)1 << 10) ? "Bytes" : "KB"
        ));

    DebugPrintf((
        "    Property : %sPrefetchable %d-bit\n",
        (pdx->PciBar[BarIndex].Properties.Flags & PLX_BAR_FLAG_PREFETCHABLE) ? "" : "Non-",
        (pdx->PciBar[BarIndex].Properties.Flags & PLX_BAR_FLAG_64_BIT) ? 64 : 32
        ));

    return ApiSuccess;
}




/*******************************************************************************
 *
 * Function   :  PlxPciBarMap
 *
 * Description:  Map a PCI BAR Space into User virtual space
 *
 ******************************************************************************/
PLX_STATUS
PlxPciBarMap(
    DEVICE_EXTENSION *pdx,
    U8                BarIndex,
    VOID             *pUserVa,
    VOID             *pOwner
    )
{
    // Handled in Dispatch_mmap() in Linux
    return ApiUnsupportedFunction;
}




/*******************************************************************************
 *
 * Function   :  PlxPciBarUnmap
 *
 * Description:  Unmap a previously mapped PCI BAR Space from User virtual space
 *
 ******************************************************************************/
PLX_STATUS
PlxPciBarUnmap(
    DEVICE_EXTENSION *pdx,
    VOID             *UserVa,
    VOID             *pOwner
    )
{
    // Handled at user API level in Linux
    return ApiUnsupportedFunction;
}




/*******************************************************************************
 *
 * Function   :  PlxEepromPresent
 *
 * Description:  Returns the state of the EEPROM as reported by the PLX device
 *
 ******************************************************************************/
PLX_STATUS
PlxEepromPresent(
    DEVICE_EXTENSION *pdx,
    U8               *pStatus
    )
{
    return Plx9000_EepromPresent(
               pdx,
               pStatus
               );
}




/*******************************************************************************
 *
 * Function   :  PlxEepromProbe
 *
 * Description:  Probes for the presence of an EEPROM
 *
 ******************************************************************************/
PLX_STATUS
PlxEepromProbe(
    DEVICE_EXTENSION *pdx,
    U8               *pFlag
    )
{
    U16        OffsetProbe;
    U32        ValueRead;
    U32        ValueWrite;
    U32        ValueOriginal;
    PLX_STATUS status;


    // Default to no EEPROM present
    *pFlag = FALSE;

    // Set EEPROM offset to use for probe
    OffsetProbe = 0x70;

    DebugPrintf(("Probe EEPROM at offset %02xh\n", OffsetProbe));

    // Get the current value
    status =
        PlxEepromReadByOffset(
            pdx,
            OffsetProbe,
            &ValueOriginal
            );

    if (status != ApiSuccess)
        return status;

    // Prepare inverse value to write
    ValueWrite = ~(ValueOriginal);

    // Write inverse of original value
    status =
        PlxEepromWriteByOffset(
            pdx,
            OffsetProbe,
            ValueWrite
            );

    if (status != ApiSuccess)
        return status;

    // Read updated value
    status =
        PlxEepromReadByOffset(
            pdx,
            OffsetProbe,
            &ValueRead
            );

    if (status != ApiSuccess)
        return status;

    // Check if value was written properly
    if (ValueRead == ValueWrite)
    {
        DebugPrintf(("Probe detected an EEPROM present\n"));

        *pFlag = TRUE;

        // Restore the original value
        PlxEepromWriteByOffset(
            pdx,
            OffsetProbe,
            ValueOriginal
            );
    }
    else
    {
        DebugPrintf(("Probe did not detect an EEPROM\n"));
    }

    return ApiSuccess;
}




/*******************************************************************************
 *
 * Function   :  PlxEepromCrcGet
 *
 * Description:  Returns the EEPROM CRC and its status
 *
 ******************************************************************************/
PLX_STATUS
PlxEepromCrcGet(
    DEVICE_EXTENSION *pdx,
    U32              *pCrc,
    U8               *pCrcStatus
    )
{
    // Clear return value
    *pCrc       = 0;
    *pCrcStatus = PLX_CRC_UNSUPPORTED;

    // CRC not supported
    return ApiUnsupportedFunction;
}




/*******************************************************************************
 *
 * Function   :  PlxEepromCrcUpdate
 *
 * Description:  Updates the EEPROM CRC
 *
 ******************************************************************************/
PLX_STATUS
PlxEepromCrcUpdate(
    DEVICE_EXTENSION *pdx,
    U32              *pCrc,
    BOOLEAN           bUpdateEeprom
    )
{
    // Clear return value
    *pCrc = 0;

    // CRC not supported
    return ApiUnsupportedFunction;
}




/*******************************************************************************
 *
 * Function   :  PlxEepromReadByOffset
 *
 * Description:  Read a 32-bit value from the EEPROM at a specified offset
 *
 ******************************************************************************/
PLX_STATUS
PlxEepromReadByOffset(
    DEVICE_EXTENSION *pdx,
    U16               offset,
    U32              *pValue
    )
{
    // Make sure offset is aligned on 32-bit boundary
    if (offset & (3 << 0))
    {
        *pValue = 0;
        return ApiInvalidOffset;
    }

    // Call chip-specific function
    return PlxChip_EepromReadByOffset(
        pdx,
        offset,
        pValue
        );
}




/*******************************************************************************
 *
 * Function   :  PlxEepromWriteByOffset
 *
 * Description:  Write a 32-bit value to the EEPROM at a specified offset
 *
 ******************************************************************************/
PLX_STATUS
PlxEepromWriteByOffset(
    DEVICE_EXTENSION *pdx,
    U16               offset,
    U32               value
    )
{
    // Make sure offset is aligned on 32-bit boundary
    if (offset & (3 << 0))
        return ApiInvalidOffset;

    // Call chip-specific function
    return PlxChip_EepromWriteByOffset(
        pdx,
        offset,
        value
        );
}




/*******************************************************************************
 *
 * Function   :  PlxEepromReadByOffset_16
 *
 * Description:  Read a 16-bit value from the EEPROM at a specified offset
 *
 ******************************************************************************/
PLX_STATUS
PlxEepromReadByOffset_16(
    DEVICE_EXTENSION *pdx,
    U16               offset,
    U16              *pValue
    )
{
    U32        Value_32;
    PLX_STATUS status;


    // Set default return value
    *pValue = 0;

    // Make sure offset is aligned on 16-bit boundary
    if (offset & (1 << 0))
        return ApiInvalidOffset;

    /******************************************
     * For devices that do not support 16-bit
     * EEPROM accesses, use 32-bit access
     *****************************************/

    // Get 32-bit value
    status =
        PlxEepromReadByOffset(
            pdx,
            (offset & ~0x3),
            &Value_32
            );

    if (status != ApiSuccess)
        return status;

    // Return desired 16-bit portion
    if (offset & 0x3)
    {
        *pValue = (U16)(Value_32 >> 16);
    }
    else
    {
        *pValue = (U16)Value_32;
    }

    return ApiSuccess;
}




/*******************************************************************************
 *
 * Function   :  PlxEepromWriteByOffset_16
 *
 * Description:  Write a 16-bit value to the EEPROM at a specified offset
 *
 ******************************************************************************/
PLX_STATUS
PlxEepromWriteByOffset_16(
    DEVICE_EXTENSION *pdx,
    U16               offset,
    U16               value
    )
{
    U32        Value_32;
    PLX_STATUS status;


    // Make sure offset is aligned on 16-bit boundary
    if (offset & (1 << 0))
        return ApiInvalidOffset;

    /******************************************
     * For devices that do not support 16-bit
     * EEPROM accesses, use 32-bit access
     *****************************************/

    // Get current 32-bit value
    status =
        PlxEepromReadByOffset(
            pdx,
            (offset & ~0x3),
            &Value_32
            );

    if (status != ApiSuccess)
        return status;

    // Insert new 16-bit value in correct location
    if (offset & 0x3)
    {
        Value_32 = ((U32)value << 16) | (Value_32 & 0xFFFF);
    }
    else
    {
        Value_32 = ((U32)value) | (Value_32 & 0xFFFF0000);
    }

    // Update EEPROM
    return PlxEepromWriteByOffset(
        pdx,
        (offset & ~0x3),
        Value_32
        );
}




/*******************************************************************************
 *
 * Function   :  PlxPciIoPortTransfer
 *
 * Description:  Read or Write from/to an I/O port
 *
 ******************************************************************************/
PLX_STATUS
PlxPciIoPortTransfer(
    U64              IoPort,
    VOID            *pBuffer,
    U32              SizeInBytes,
    PLX_ACCESS_TYPE  AccessType,
    BOOLEAN          bReadOperation
    )
{
    U8 AccessSize;


    if (pBuffer == NULL)
        return ApiNullParam;

    // Verify size & type
    switch (AccessType)
    {
        case BitSize8:
            AccessSize = sizeof(U8);
            break;

        case BitSize16:
            if (IoPort & (1 << 0))
            {
                DebugPrintf(("ERROR - I/O port not aligned on 16-bit boundary\n"));
                return ApiInvalidAddress;
            }

            if (SizeInBytes & (1 << 0))
            {
                DebugPrintf(("ERROR - Byte count not aligned on 16-bit boundary\n"));
                return ApiInvalidSize;
            }
            AccessSize = sizeof(U16);
            break;

        case BitSize32:
            if (IoPort & 0x3)
            {
                DebugPrintf(("ERROR - I/O port not aligned on 32-bit boundary\n"));
                return ApiInvalidAddress;
            }

            if (SizeInBytes & 0x3)
            {
                DebugPrintf(("ERROR - Byte count not aligned on 32-bit boundary\n"));
                return ApiInvalidSize;
            }
            AccessSize = sizeof(U32);
            break;

        default:
            return ApiInvalidAccessType;
    }

    while (SizeInBytes)
    {
        if (bReadOperation)
        {
            switch (AccessType)
            {
                case BitSize8:
                    *(U8*)pBuffer = IO_PORT_READ_8( IoPort );
                    break;

                case BitSize16:
                    *(U16*)pBuffer = IO_PORT_READ_16( IoPort );
                    break;

                case BitSize32:
                    *(U32*)pBuffer = IO_PORT_READ_32( IoPort );
                    break;

                default:
                    // Added to avoid compiler warnings
                    break;
            }
        }
        else
        {
            switch (AccessType)
            {
                case BitSize8:
                    IO_PORT_WRITE_8(
                        IoPort,
                        *(U8*)pBuffer
                        );
                    break;

                case BitSize16:
                    IO_PORT_WRITE_16(
                        IoPort,
                        *(U16*)pBuffer
                        );
                    break;

                case BitSize32:
                    IO_PORT_WRITE_32(
                        IoPort,
                        *(U32*)pBuffer
                        );
                    break;

                default:
                    // Added to avoid compiler warnings
                    break;
            }
        }

        // Adjust pointer & byte count
        pBuffer      = (VOID*)((PLX_UINT_PTR)pBuffer + AccessSize);
        SizeInBytes -= AccessSize;
    }

    return ApiSuccess;
}




/*******************************************************************************
 *
 * Function   :  PlxPciPhysicalMemoryAllocate
 *
 * Description:  Allocate physically contiguous page-locked memory
 *
 ******************************************************************************/
PLX_STATUS
PlxPciPhysicalMemoryAllocate(
    DEVICE_EXTENSION *pdx,
    PLX_PHYSICAL_MEM *pPciMem,
    BOOLEAN           bSmallerOk,
    VOID             *pOwner
    )
{
    U32                  DecrementAmount;
    PLX_PHYS_MEM_OBJECT *pMemObject;


    // Initialize buffer information
    pPciMem->UserAddr     = 0;
    pPciMem->PhysicalAddr = 0;
    pPciMem->CpuPhysical  = 0;

    /*******************************************************
     * Verify size
     *
     * A size of 0 is valid because this function may
     * be called to allocate a common buffer of size 0;
     * therefore, the information is reset & return sucess.
     ******************************************************/
    if (pPciMem->Size == 0)
    {
        return ApiSuccess;
    }

    // Allocate memory for new list object
    pMemObject =
        kmalloc(
            sizeof(PLX_PHYS_MEM_OBJECT),
            GFP_KERNEL
            );

    if (pMemObject == NULL)
    {
        DebugPrintf(("ERROR - Memory allocation for list object failed\n"));
        return ApiInsufficientResources;
    }

    // Clear object
    RtlZeroMemory( pMemObject, sizeof(PLX_PHYS_MEM_OBJECT) );

    // Set buffer request size
    pMemObject->Size = pPciMem->Size;

    // Setup amount to reduce on failure
    DecrementAmount = (pPciMem->Size / 10);

    DebugPrintf((
        "Attempt to allocate physical memory (%d Kb)...\n",
        (pPciMem->Size >> 10)
        ));

    do
    {
        // Attempt to allocate the buffer
        pMemObject->pKernelVa =
            Plx_dma_buffer_alloc(
                pdx,
                pMemObject
                );

        if (pMemObject->pKernelVa == NULL)
        {
            // Reduce memory request size if requested
            if (bSmallerOk && (pMemObject->Size > PAGE_SIZE))
            {
                pMemObject->Size -= DecrementAmount;
            }
            else
            {
                // Release the list object
                kfree(
                    pMemObject
                    );

                DebugPrintf(("ERROR - Physical memory allocation failed\n"));

                pPciMem->Size = 0;

                return ApiInsufficientResources;
            }
        }
    }
    while (pMemObject->pKernelVa == NULL);

    // Record buffer owner
    pMemObject->pOwner = pOwner;

    // Assign buffer to device if provided
    if (pOwner != pGbl_DriverObject)
    {
        // Return buffer information
        pPciMem->Size         = pMemObject->Size;
        pPciMem->PhysicalAddr = pMemObject->BusPhysical;
        pPciMem->CpuPhysical  = pMemObject->CpuPhysical;

        // Add buffer object to list
        spin_lock(
            &(pdx->Lock_PhysicalMemList)
            );

        list_add_tail(
            &(pMemObject->ListEntry),
            &(pdx->List_PhysicalMem)
            );

        spin_unlock(
            &(pdx->Lock_PhysicalMemList)
            );
    }
    else
    {
        // Store common buffer information
        pGbl_DriverObject->CommonBuffer = *pMemObject;

        // Release the list object
        kfree(
            pMemObject
            );
    }

    return ApiSuccess;
}




/*******************************************************************************
 *
 * Function   :  PlxPciPhysicalMemoryFree
 *
 * Description:  Free previously allocated physically contiguous page-locked memory
 *
 ******************************************************************************/
PLX_STATUS
PlxPciPhysicalMemoryFree(
    DEVICE_EXTENSION *pdx,
    PLX_PHYSICAL_MEM *pPciMem
    )
{
    struct list_head    *pEntry;
    PLX_PHYS_MEM_OBJECT *pMemObject;


    spin_lock(
        &(pdx->Lock_PhysicalMemList)
        );

    pEntry = pdx->List_PhysicalMem.next;

    // Traverse list to find the desired list object
    while (pEntry != &(pdx->List_PhysicalMem))
    {
        // Get the object
        pMemObject =
            list_entry(
                pEntry,
                PLX_PHYS_MEM_OBJECT,
                ListEntry
                );

        // Check if the physical addresses matches
        if (pMemObject->BusPhysical == pPciMem->PhysicalAddr)
        {
            // Remove the object from the list
            list_del(
                pEntry
                );

            spin_unlock(
                &(pdx->Lock_PhysicalMemList)
                );

            // Release the buffer
            Plx_dma_buffer_free(
                pdx,
                pMemObject
                );

            // Release the list object
            kfree(
                pMemObject
                );

            return ApiSuccess;
        }

        // Jump to next item in the list
        pEntry = pEntry->next;
    }

    spin_unlock(
        &(pdx->Lock_PhysicalMemList)
        );

    DebugPrintf(("ERROR - buffer object not found in list\n"));

    return ApiInvalidData;
}




/*******************************************************************************
 *
 * Function   :  PlxPciPhysicalMemoryMap
 *
 * Description:  Maps physical memory to User virtual address space
 *
 ******************************************************************************/
PLX_STATUS
PlxPciPhysicalMemoryMap(
    DEVICE_EXTENSION *pdx,
    PLX_PHYSICAL_MEM *pPciMem,
    VOID             *pOwner
    )
{
    // Handled in Dispatch_mmap() in Linux
    return ApiUnsupportedFunction;
}




/*******************************************************************************
 *
 * Function   :  PlxPciPhysicalMemoryUnmap
 *
 * Description:  Unmap physical memory from User virtual address space
 *
 ******************************************************************************/
PLX_STATUS
PlxPciPhysicalMemoryUnmap(
    DEVICE_EXTENSION *pdx,
    PLX_PHYSICAL_MEM *pPciMem,
    VOID             *pOwner
    )
{
    // Handled by user-level API in Linux
    return ApiUnsupportedFunction;
}




/*******************************************************************************
 *
 * Function   :  PlxInterruptEnable
 *
 * Description:  Enables specific interupts of the PLX Chip
 *
 ******************************************************************************/
PLX_STATUS
PlxInterruptEnable(
    DEVICE_EXTENSION *pdx,
    PLX_INTERRUPT    *pPlxIntr
    )
{
    // Call chip-specific function
    return PlxChip_InterruptEnable(
        pdx,
        pPlxIntr
        );
}




/*******************************************************************************
 *
 * Function   :  PlxInterruptDisable
 *
 * Description:  Disables specific interrupts of the PLX Chip
 *
 ******************************************************************************/
PLX_STATUS
PlxInterruptDisable(
    DEVICE_EXTENSION *pdx,
    PLX_INTERRUPT    *pPlxIntr
    )
{
    // Call chip-specific function
    return PlxChip_InterruptDisable(
        pdx,
        pPlxIntr
        );
}




/*******************************************************************************
 *
 * Function   :  PlxNotificationRegisterFor
 *
 * Description:  Registers a wait object for notification on interrupt(s)
 *
 ******************************************************************************/
PLX_STATUS
PlxNotificationRegisterFor(
    DEVICE_EXTENSION  *pdx,
    PLX_INTERRUPT     *pPlxIntr,
    VOID             **pUserWaitObject,
    VOID              *pOwner
    )
{
    unsigned long    flags;
    PLX_WAIT_OBJECT *pWaitObject;


    // Allocate a new wait object
    pWaitObject =
        kmalloc(
            sizeof(PLX_WAIT_OBJECT),
            GFP_KERNEL
            );

    if (pWaitObject == NULL)
    {
        DebugPrintf((
            "ERROR - memory allocation for interrupt wait object failed\n"
            ));

        return ApiInsufficientResources;
    }

    // Provide the wait object to the user app
    *pUserWaitObject = pWaitObject;

    // Record the owner
    pWaitObject->pOwner = pOwner;

    // Mark the object as waiting
    pWaitObject->state = PLX_STATE_WAITING;

    // Clear number of sleeping threads
    atomic_set( &pWaitObject->SleepCount, 0 );

    // Initialize wait queue
    init_waitqueue_head(
        &(pWaitObject->WaitQueue)
        );

    // Clear interrupt source
    pWaitObject->Source_Ints     = INTR_TYPE_NONE;
    pWaitObject->Source_Doorbell = 0;

    // Set interrupt notification flags
    PlxChipSetInterruptNotifyFlags(
        pPlxIntr,
        pWaitObject
        );

    // Add to list of waiting objects
    spin_lock_irqsave(
        &(pdx->Lock_WaitObjectsList),
        flags
        );

    list_add_tail(
        &(pWaitObject->ListEntry),
        &(pdx->List_WaitObjects)
        );

    spin_unlock_irqrestore(
        &(pdx->Lock_WaitObjectsList),
        flags
        );

    DebugPrintf((
        "Registered interrupt wait object (%p)\n",
        pWaitObject
        ));

    return ApiSuccess;
}




/*******************************************************************************
 *
 * Function   :  PlxNotificationWait
 *
 * Description:  Put the process to sleep until wake-up event occurs or timeout
 *
 ******************************************************************************/
PLX_STATUS
PlxNotificationWait(
    DEVICE_EXTENSION *pdx,
    VOID             *pUserWaitObject,
    PLX_UINT_PTR      Timeout_ms
    )
{
    long              Wait_rc;
    PLX_STATUS        rc;
    PLX_UINT_PTR      Timeout_sec;
    unsigned long     flags;
    struct list_head *pEntry;
    PLX_WAIT_OBJECT  *pWaitObject;


    // Find the wait object in the list
    spin_lock_irqsave(
        &(pdx->Lock_WaitObjectsList),
        flags
        );

    pEntry = pdx->List_WaitObjects.next;

    // Find the wait object and wait for wake-up event
    while (pEntry != &(pdx->List_WaitObjects))
    {
        // Get the wait object
        pWaitObject =
            list_entry(
                pEntry,
                PLX_WAIT_OBJECT,
                ListEntry
                );

        // Check if the object address matches the Tag
        if (pWaitObject == pUserWaitObject)
        {
            spin_unlock_irqrestore(
                &(pdx->Lock_WaitObjectsList),
                flags
                );

            DebugPrintf((
                "Waiting for Interrupt wait object (%p) to wake-up\n",
                pWaitObject
                ));

            /*********************************************************
             * Convert milliseconds to jiffies.  The following
             * formula is used:
             *
             *                      ms * HZ
             *           jiffies = ---------
             *                       1,000
             *
             *
             *  where:  HZ      = System-defined clock ticks per second
             *          ms      = Timeout in milliseconds
             *          jiffies = Number of HZ's per second
             *
             *  Note: Since the timeout is stored as a "long" integer,
             *        the conversion to jiffies is split into two operations.
             *        The first is on number of seconds and the second on
             *        the remaining millisecond precision.  This mimimizes
             *        overflow when the specified timeout is large and also
             *        keeps millisecond precision.
             ********************************************************/

            // Perform conversion if not infinite wait
            if (Timeout_ms != PLX_TIMEOUT_INFINITE)
            {
                // Get number of seconds
                Timeout_sec = Timeout_ms / 1000;

                // Store milliseconds precision
                Timeout_ms = Timeout_ms - (Timeout_sec * 1000);

                // Convert to jiffies
                Timeout_sec = Timeout_sec * HZ;
                Timeout_ms  = (Timeout_ms * HZ) / 1000;

                // Compute total jiffies
                Timeout_ms = Timeout_sec + Timeout_ms;
            }

            // Timeout parameter is signed and can't be negative
            if ((signed long)Timeout_ms < 0)
            {
                // Shift out negative bit
                Timeout_ms = Timeout_ms >> 1;
            }

            // Increment number of sleeping threads
            atomic_inc( &pWaitObject->SleepCount );

            do
            {
                // Wait for interrupt event
                Wait_rc =
                    wait_event_interruptible_timeout(
                        pWaitObject->WaitQueue,
                        (pWaitObject->state != PLX_STATE_WAITING),
                        Timeout_ms
                        );
            }
            while ((Wait_rc == 0) && (Timeout_ms == PLX_TIMEOUT_INFINITE));

            if (Wait_rc > 0)
            {
                // Condition met or interrupt occurred
                DebugPrintf(("Interrupt wait object awakened\n"));
                rc = ApiSuccess;
            }
            else if (Wait_rc == 0)
            {
                // Timeout reached
                DebugPrintf(("Timeout waiting for interrupt\n"));
                rc = ApiWaitTimeout;
            }
            else
            {
                // Interrupted by a signal
                DebugPrintf(("Interrupt wait object interrupted by signal or error\n"));
                rc = ApiWaitCanceled;
            }

            // If object is in triggered state, rest to waiting state
            if (pWaitObject->state == PLX_STATE_TRIGGERED)
                pWaitObject->state = PLX_STATE_WAITING;

            // Decrement number of sleeping threads
            atomic_dec( &pWaitObject->SleepCount );

            return rc;
        }

        // Jump to next item in the list
        pEntry = pEntry->next;
    }

    spin_unlock_irqrestore(
        &(pdx->Lock_WaitObjectsList),
        flags
        );

    DebugPrintf((
        "Interrupt wait object (%p) not found or previously canceled\n",
        pUserWaitObject
        ));

    // Object not found at this point
    return ApiFailed;
}




/*******************************************************************************
 *
 * Function   :  PlxNotificationStatus
 *
 * Description:  Returns the interrupt(s) that have caused notification events
 *
 ******************************************************************************/
PLX_STATUS
PlxNotificationStatus(
    DEVICE_EXTENSION *pdx,
    VOID             *pUserWaitObject,
    PLX_INTERRUPT    *pPlxIntr
    )
{
    unsigned long       flags;
    struct list_head   *pEntry;
    PLX_WAIT_OBJECT    *pWaitObject;
    PLX_INTERRUPT_DATA  IntData;


    spin_lock_irqsave(
        &(pdx->Lock_WaitObjectsList),
        flags
        );

    pEntry = pdx->List_WaitObjects.next;

    // Traverse list to find the desired list object
    while (pEntry != &(pdx->List_WaitObjects))
    {
        // Get the object
        pWaitObject =
            list_entry(
                pEntry,
                PLX_WAIT_OBJECT,
                ListEntry
                );

        // Check if desired object
        if (pWaitObject == pUserWaitObject)
        {
            // Copy the interrupt sources
            IntData.Source_Ints     = pWaitObject->Source_Ints;
            IntData.Source_Doorbell = pWaitObject->Source_Doorbell;

            // Reset interrupt sources
            pWaitObject->Source_Ints     = INTR_TYPE_NONE;
            pWaitObject->Source_Doorbell = 0;

            spin_unlock_irqrestore(
                &(pdx->Lock_WaitObjectsList),
                flags
                );

            DebugPrintf((
                "Returning status for interrupt wait object (%p)...\n",
                pWaitObject
                ));

            // Set triggered interrupts
            PlxChipSetInterruptStatusFlags(
                &IntData,
                pPlxIntr
                );

            return ApiSuccess;
        }

        // Jump to next item in the list
        pEntry = pEntry->next;
    }

    spin_unlock_irqrestore(
        &(pdx->Lock_WaitObjectsList),
        flags
        );

    return ApiFailed;
}




/*******************************************************************************
 *
 * Function   :  PlxNotificationCancel
 *
 * Description:  Cancels a registered notification event
 *
 ******************************************************************************/
PLX_STATUS
PlxNotificationCancel(
    DEVICE_EXTENSION *pdx,
    VOID             *pUserWaitObject,
    VOID             *pOwner
    )
{
    U32               LoopCount;
    BOOLEAN           bRemove;
    unsigned long     flags;
    struct list_head *pEntry;
    PLX_WAIT_OBJECT  *pWaitObject;


    spin_lock_irqsave(
        &(pdx->Lock_WaitObjectsList),
        flags
        );

    pEntry = pdx->List_WaitObjects.next;

    // Find the object and remove it
    while (pEntry != &(pdx->List_WaitObjects))
    {
        // Get the object
        pWaitObject =
            list_entry(
                pEntry,
                PLX_WAIT_OBJECT,
                ListEntry
                );

        // Default to not remove
        bRemove = FALSE;

        // Determine if object should be removed
        if (pOwner == pWaitObject->pOwner)
        {
            if (pUserWaitObject == NULL)
            {
                bRemove = TRUE;
            }
            else if (pWaitObject == pUserWaitObject)
            {
                bRemove = TRUE;
            }
        }

        // Remove object
        if (bRemove)
        {
            DebugPrintf((
                "Removing interrupt wait object (%p)...\n",
                pWaitObject
                ));

            // Remove the object from the list
            list_del(
                pEntry
                );

            spin_unlock_irqrestore(
                &(pdx->Lock_WaitObjectsList),
                flags
                );

            // Set loop count
            LoopCount = 20;

            // Wake-up processes if wait object is pending
            if (atomic_read(&pWaitObject->SleepCount) != 0)
            {
                DebugPrintf(("Wait object is pending in another thread, forcing wake up\n"));

                // Mark object for deletion
                pWaitObject->state = PLX_STATE_MARKED_FOR_DELETE;

                // Wake-up any process waiting on the object
                wake_up_interruptible(
                    &(pWaitObject->WaitQueue)
                    );

                do
                {
                    // Set current task as uninterruptible
                    set_current_state(TASK_UNINTERRUPTIBLE);

                    // Relieve timeslice to allow pending thread to wake up
                    schedule_timeout( Plx_ms_to_jiffies( 10 ) );

                    // Decrement counter
                    LoopCount--;
                }
                while (LoopCount && (atomic_read(&pWaitObject->SleepCount) != 0));
            }


            if (LoopCount == 0)
            {
                DebugPrintf(("ERROR: Timeout waiting for pending thread, unable to free wait object\n"));
            }
            else
            {
                // Release the list object
                kfree(
                    pWaitObject
                    );
            }

            // Return if removing only a specific object
            if (pUserWaitObject != NULL)
                return ApiSuccess;

            // Reset to beginning of list
            spin_lock_irqsave(
                &(pdx->Lock_WaitObjectsList),
                flags
                );

            pEntry = pdx->List_WaitObjects.next;
        }
        else
        {
            // Jump to next item in the list
            pEntry = pEntry->next;
        }
    }

    spin_unlock_irqrestore(
        &(pdx->Lock_WaitObjectsList),
        flags
        );

    return ApiFailed;
}




/*******************************************************************************
 *
 * Function   :  PlxPciBarSpaceTransfer
 *
 * Description:  Accesses a PCI BAR space
 *
 ******************************************************************************/
PLX_STATUS
PlxPciBarSpaceTransfer(
    DEVICE_EXTENSION *pdx,
    U8                BarIndex,
    U32               offset,
    U8               *pBuffer,
    U32               ByteCount,
    PLX_ACCESS_TYPE   AccessType,
    BOOLEAN           bRemap,
    BOOLEAN           bReadOperation
    )
{
    U8  *pVaSpace;
    U16  Offset_RegRemap;
    U32  RegValue;
    U32  SpaceRange;
    U32  SpaceOffset;
    U32  RemapOriginal;
    U32  BytesToTransfer;


    DebugPrintf((
        "%s PCI BAR %d (%s=%08X  %d bytes)\n",
        (bReadOperation) ? "Read from" : "Write to",
        BarIndex,
        (bRemap) ? "Local Addr" : "Offset",
        offset,
        ByteCount
        ));

    // Added to prevent compiler warnings
    RemapOriginal = 0;

    // Verify data alignment
    switch (AccessType)
    {
        case BitSize8:
            break;

        case BitSize16:
            if (offset & 0x1)
            {
                DebugPrintf(("ERROR - Local address not aligned\n"));
                return ApiInvalidAddress;
            }

            if (ByteCount & 0x1)
            {
                DebugPrintf(("ERROR - Byte count not aligned\n"));
                return ApiInvalidSize;
            }
            break;

        case BitSize32:
            if (offset & 0x3)
            {
                DebugPrintf(("ERROR - Local address not aligned\n"));
                return ApiInvalidAddress;
            }

            if (ByteCount & 0x3)
            {
                DebugPrintf(("ERROR - Byte count not aligned\n"));
                return ApiInvalidSize;
            }
            break;

        default:
            DebugPrintf(("ERROR - Invalid access type\n"));
            return ApiInvalidAccessType;
    }

    // Get offset of remap register
    PlxChipGetRemapOffset(
        pdx,
        BarIndex,
        &Offset_RegRemap
        );

    if (Offset_RegRemap == (U16)-1)
    {
        return ApiInvalidIopSpace;
    }

    // Only memory spaces are supported by this function
    if (pdx->PciBar[BarIndex].Properties.Flags & PLX_BAR_FLAG_IO)
    {
        DebugPrintf(("ERROR - I/O spaces not supported by this function\n"));
        return ApiInvalidIopSpace;
    }

    // Get kernel virtual address for the space
    pVaSpace = pdx->PciBar[BarIndex].pVa;

    if (pVaSpace == NULL)
    {
        DebugPrintf(("ERROR - Invalid kernel VA (%p) for PCI BAR\n", pVaSpace));
        return ApiInvalidAddress;
    }

    // Save the remap register
    if (bRemap)
    {
        RemapOriginal =
            PLX_9000_REG_READ(
                pdx,
                Offset_RegRemap
                );
    }
    else
    {
        // Make sure requested area doesn't exceed our local space window boundary
        if ((offset + ByteCount) > (U32)pdx->PciBar[BarIndex].Properties.Size)
        {
            DebugPrintf(("ERROR - requested area exceeds space range\n"));
            return ApiInvalidSize;
        }
    }

    // Get the range of the space
    SpaceRange = ~((U32)pdx->PciBar[BarIndex].Properties.Size - 1);

    // Transfer data in blocks
    while (ByteCount != 0)
    {
        // Adjust remap if necessary
        if (bRemap)
        {
            // Clear upper bits of remap
            RegValue = RemapOriginal & ~SpaceRange;

            // Adjust window to local address
            RegValue |= offset & SpaceRange;

            PLX_9000_REG_WRITE(
                pdx,
                Offset_RegRemap,
                RegValue
                );
        }

        // Get current offset into space
        SpaceOffset = offset & (~SpaceRange);

        // Calculate bytes to transfer for next block
        if (ByteCount <= (((~SpaceRange) + 1) - SpaceOffset))
        {
            BytesToTransfer = ByteCount;
        }
        else
        {
            BytesToTransfer = ((~SpaceRange) + 1) - SpaceOffset;
        }

        // Make sure user buffer is accessible for next block
        if (bReadOperation)
        {
            // Read from device = Write to user buffer
            if (access_ok(
                    VERIFY_WRITE,
                    pBuffer,
                    BytesToTransfer
                    ) == FALSE)
            {
                DebugPrintf(("ERROR - User buffer not accessible\n"));
                return ApiInsufficientResources;
            }
        }
        else
        {
            // Write to device = Read from user buffer
            if (access_ok(
                    VERIFY_READ,
                    pBuffer,
                    BytesToTransfer
                    ) == FALSE)
            {
                DebugPrintf(("ERROR - User buffer not accessible\n"));
                return ApiInsufficientResources;
            }
        }

        if (bReadOperation)
        {
            // Copy block to user buffer
            switch (AccessType)
            {
                case BitSize8:
                    DEV_MEM_TO_USER_8(
                        pBuffer,
                        (pVaSpace + SpaceOffset),
                        BytesToTransfer
                        );
                    break;

                case BitSize16:
                    DEV_MEM_TO_USER_16(
                        pBuffer,
                        (pVaSpace + SpaceOffset),
                        BytesToTransfer
                        );
                    break;

                case BitSize32:
                    DEV_MEM_TO_USER_32(
                        pBuffer,
                        (pVaSpace + SpaceOffset),
                        BytesToTransfer
                        );
                    break;

                case BitSize64:
                    // 64-bit not implemented yet
                    break;
            }
        }
        else
        {
            // Copy user buffer to device memory
            switch (AccessType)
            {
                case BitSize8:
                    USER_TO_DEV_MEM_8(
                        (pVaSpace + SpaceOffset),
                        pBuffer,
                        BytesToTransfer
                        );
                    break;

                case BitSize16:
                    USER_TO_DEV_MEM_16(
                        (pVaSpace + SpaceOffset),
                        pBuffer,
                        BytesToTransfer
                        );
                    break;

                case BitSize32:
                    USER_TO_DEV_MEM_32(
                        (pVaSpace + SpaceOffset),
                        pBuffer,
                        BytesToTransfer
                        );
                    break;

                case BitSize64:
                    // 64-bit not implemented yet
                    break;
            }
        }

        // Adjust for next block access
        pBuffer   += BytesToTransfer;
        offset    += BytesToTransfer;
        ByteCount -= BytesToTransfer;
    }

    // Restore the remap register
    if (bRemap)
    {
        PLX_9000_REG_WRITE(
            pdx,
            Offset_RegRemap,
            RemapOriginal
            );
    }

    return ApiSuccess;
}




/*******************************************************************************
 *
 * Function   :  PlxPciVpdRead
 *
 * Description:  Read the Vital Product Data
 *
 ******************************************************************************/
PLX_STATUS
PlxPciVpdRead(
    DEVICE_EXTENSION *pdx,
    U16               offset,
    U32              *pValue
    )
{
    S16 VpdRetries;
    S16 VpdPollCount;
    U16 Offset_VPD;
    U32 RegValue;


    // Check for unaligned offset
    if (offset & 0x3)
    {
        *pValue = (U32)-1;
        return ApiInvalidOffset;
    }

    // Get the VPD offset
    Offset_VPD =
        PlxGetExtendedCapabilityOffset(
            pdx,
            CAP_ID_VPD
            );

    if (Offset_VPD == 0)
    {
        return ApiUnsupportedFunction;
    }

     /**********************************************
      * The EEDO Input (bit 31) must be disabled
      * for some chips when VPD access is used.
      * Since it is a reserved bit in older chips,
      * there is no harm in clearing it for all.
      *********************************************/
    RegValue =
        PLX_9000_REG_READ(
            pdx,
            REG_EEPROM_CTRL
            );

    PLX_9000_REG_WRITE(
        pdx,
        REG_EEPROM_CTRL,
        RegValue & ~(1 << 31)
        );

    // Prepare VPD command
    RegValue = ((U32)offset << 16) | 0x3;

    VpdRetries = VPD_COMMAND_MAX_RETRIES;
    do
    {
        /**************************************
        *  This loop will continue until the
        *  VPD reports success or until we reach
        *  the maximum number of retries
        **************************************/

        // Send VPD Command
        PLX_PCI_REG_WRITE(
            pdx,
            Offset_VPD,
            RegValue
            );

        // Poll until VPD operation has completed
        VpdPollCount = VPD_STATUS_MAX_POLL;
        do
        {
            // Delay for a bit for VPD operation
            Plx_sleep(VPD_STATUS_POLL_DELAY);

            // Get VPD Status
            PLX_PCI_REG_READ(
                pdx,
                Offset_VPD,
                &RegValue
                );

            // Check for command completion
            if (RegValue & (1 << 31))
            {
                // VPD read completed successfully

                // Get the VPD Data result
                PLX_PCI_REG_READ(
                    pdx,
                    Offset_VPD + sizeof(U32),
                    pValue
                    );

                return ApiSuccess;
            }
        }
        while (VpdPollCount--);
    }
    while (VpdRetries--);

    // At this point, VPD access failed
    DebugPrintf(("ERROR - Timeout waiting for VPD read to complete\n"));

    *pValue = (U32)-1;

    return ApiWaitTimeout;
}




/*******************************************************************************
 *
 * Function   :  PlxPciVpdWrite
 *
 * Description:  Write to the Vital Product Data
 *
 ******************************************************************************/
PLX_STATUS
PlxPciVpdWrite(
    DEVICE_EXTENSION *pdx,
    U16               offset,
    U32               VpdData
    )
{
    S16 VpdRetries;
    S16 VpdPollCount;
    U16 Offset_VPD;
    U32 RegValue;


    // Check for unaligned offset
    if (offset & 0x3)
        return ApiInvalidOffset;

    // Get the VPD offset
    Offset_VPD =
        PlxGetExtendedCapabilityOffset(
            pdx,
            CAP_ID_VPD
            );

    if (Offset_VPD == 0)
    {
        return ApiUnsupportedFunction;
    }

     /**********************************************
      * The EEDO Input (bit 31) must be disabled
      * for some chips when VPD access is used.
      * Since it is a reserved bit in older chips,
      * there is no harm in clearing it for all.
      *********************************************/
    RegValue =
        PLX_9000_REG_READ(
            pdx,
            REG_EEPROM_CTRL
            );

    PLX_9000_REG_WRITE(
        pdx,
        REG_EEPROM_CTRL,
        RegValue & ~(1 << 31)
        );

    // Put write value into VPD Data register
    PLX_PCI_REG_WRITE(
        pdx,
        Offset_VPD + sizeof(U32),
        VpdData
        );

    // Prepare VPD command
    RegValue = (1 << 31) | ((U32)offset << 16) | 0x3;

    VpdRetries = VPD_COMMAND_MAX_RETRIES;
    do
    {
        /**************************************
        *  This loop will continue until the
        *  VPD reports success or until we reach
        *  the maximum number of retries
        **************************************/

        // Send VPD command
        PLX_PCI_REG_WRITE(
            pdx,
            Offset_VPD,
            RegValue
            );

        // Poll until VPD operation has completed
        VpdPollCount = VPD_STATUS_MAX_POLL;
        do
        {
            // Delay for a bit for VPD operation
            Plx_sleep(VPD_STATUS_POLL_DELAY);

            // Get VPD Status
            PLX_PCI_REG_READ(
                pdx,
                Offset_VPD,
                &RegValue
                );

            // Check for command completion
            if ((RegValue & (1 << 31)) == 0)
            {
                // VPD write completed successfully
                return ApiSuccess;
            }
        }
        while (VpdPollCount--);
    }
    while (VpdRetries--);

    // At this point, VPD access failed
    DebugPrintf(("ERROR - Timeout waiting for VPD write to complete\n"));

    return ApiWaitTimeout;
}
