/*
 * Broadcom Proprietary and Confidential. Copyright 2016 Broadcom
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

MEMORY
{
    /* No Bootloader or DCT */
    APP_FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM      (rwx) : ORIGIN = 0x20000000, LENGTH = 96K
}

