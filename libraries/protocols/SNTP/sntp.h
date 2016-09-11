/*
 * Broadcom Proprietary and Confidential. Copyright 2016 Broadcom
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#pragma once

#include "wiced.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

typedef struct
{
    uint32_t seconds;
    uint32_t microseconds;
} ntp_timestamp_t;

/******************************************************
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

extern wiced_result_t sntp_start_auto_time_sync( uint32_t interval_ms );
extern wiced_result_t sntp_stop_auto_time_sync( void );
extern wiced_result_t sntp_get_time( const wiced_ip_address_t* address, ntp_timestamp_t* timestamp );
extern wiced_result_t sntp_set_server_ip_address(uint32_t index, wiced_ip_address_t ip_address);
extern wiced_result_t sntp_clr_server_ip_address(uint32_t index);

#ifdef __cplusplus
} /* extern "C" */
#endif
