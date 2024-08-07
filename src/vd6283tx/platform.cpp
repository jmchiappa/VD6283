/**
  ******************************************************************************
  * @file    platform.c
  * @author  IMG SW Application Team
  * @brief   This file provides the implementation of read/write operations for
  * 		 VD6283TX component driver
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "vd6283tx.h"
#include "modules/STALS_platform.h"
#include "modules/busIO/IO.h"

STALS_ErrCode_t STALS_WrByte(void *pClient, uint8_t index, uint8_t data)
{
	int32_t res;
	VD6283TX_Object_t *pObj = (VD6283TX_Object_t *) pClient;
	BusIO *port = (BusIO *)pObj->IO;
	// port.
	res = port->writeSingleByte( index, data );

	if (res)
			return STALS_ERROR_WRITE;

	return STALS_NO_ERROR;
}

STALS_ErrCode_t STALS_RdByte(void *pClient, uint8_t index, uint8_t *data)
{
	int32_t res;
	VD6283TX_Object_t *pObj = (VD6283TX_Object_t *) pClient;
	BusIO *port = (BusIO *)pObj->IO;
	*data = port->readSingleByte( index );
	return STALS_NO_ERROR;
}

STALS_ErrCode_t STALS_RdMultipleBytes(void *pClient, uint8_t index, uint8_t *data, int nb)
{
	int32_t res;
	VD6283TX_Object_t *pObj = (VD6283TX_Object_t *) pClient;
	BusIO *port = (BusIO *)pObj->IO;
	res = port->readMultipleBytes(index,data,nb);
	if (res)
			return STALS_ERROR_READ;

	return STALS_NO_ERROR;
}
