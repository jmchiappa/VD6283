/**
  ******************************************************************************
  * @file    vd6283tx.h
  * @author  IMG SW Application Team
  * @brief   This file contains all the functions prototypes for the vd6283tx.c
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef VD6283TX_H
#define VD6283TX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "modules/STALS.h"
#include <stddef.h>

#define VD6283TX_DEVICE_ID_REG        (0x00U)
#define VD6283TX_DEVICE_ID            (0x70U)
#define VD6283TX_IRQ_CTRL_ST					(0x02U)
#define VD6283TX_MAX_CHANNELS         ((uint8_t)STALS_ALS_MAX_CHANNELS)     /*!< Number of channels of the device */
#define VD6283TX_ALL_CHANNELS         ((1U << STALS_ALS_MAX_CHANNELS) - 1U) /*!< Bitmask to select all ALS channels */

#define VD6283TX_CTRL_DARK            (STALS_OUTPUT_DARK_ENABLE)

#define VD6283TX_RED_CHANNEL          (0U)   /*!< Channel 1 */
#define VD6283TX_VISIBLE_CHANNEL      (1U)   /*!< Channel 2 */
#define VD6283TX_BLUE_CHANNEL         (2U)   /*!< Channel 3 */
#define VD6283TX_GREEN_CHANNEL        (3U)   /*!< Channel 4 */
#define VD6283TX_IR_CHANNEL           (4U)   /*!< Channel 5 */
#define VD6283TX_CLEAR_CHANNEL        (5U)   /*!< Channel 6 */

/* flicker capture modes */
#define VD6283TX_FLICKER_ANALOG       (0U)
#define VD6283TX_FLICKER_DIGITAL      (1U)

/* als capture modes */
#define VD6283TX_MODE_SINGLESHOT      (0U)
#define VD6283TX_MODE_CONTINUOUS      (1U)

/* vd6283tx error codes */
#define VD6283TX_OK                   (0)
#define VD6283TX_ERROR                (-1)
#define VD6283TX_INVALID_PARAM        (-2)
/**
  * @}
  */

/** @defgroup VD6283TX_Exported_Types Exported Types
  * @{
  */

typedef struct VD6283TX_Capabilities_s
{
  uint8_t NumberOfChannels;  /*!< Max: LIGHT_SENSOR_MAX_CHANNELS */
  uint8_t FlickerDetection;  /*!< Not available: 0, Available: 1 */
  uint8_t Autogain;          /*!< Not available: 0, Available: 1 */
} VD6283TX_Capabilities_t;

typedef struct VD6283TX_Object_s
{

  void *IO;
  void *handle;  /*!< bare-driver handle */
  uint32_t FlickerOutputType;
  uint8_t IsInitialized;
  uint8_t IsContinuous;
  uint8_t IsStarted;
  uint8_t IsFlickerActive;
} VD6283TX_Object_t;

int32_t VD6283TX_Init(VD6283TX_Object_t *pObj);
int32_t VD6283TX_DeInit(VD6283TX_Object_t *pObj);
int32_t VD6283TX_ReadID(VD6283TX_Object_t *pObj, uint32_t *pId);
int32_t VD6283TX_isDataReady(VD6283TX_Object_t *pObj, uint8_t *pIsReady);
int32_t VD6283TX_GetCapabilities(VD6283TX_Object_t *pObj, VD6283TX_Capabilities_t *pCapabilities);
int32_t VD6283TX_SetExposureTime(VD6283TX_Object_t *pObj, uint32_t ExposureTime);
int32_t VD6283TX_GetExposureTime(VD6283TX_Object_t *pObj, uint32_t *pExposureTime);
int32_t VD6283TX_SetGain(VD6283TX_Object_t *pObj, uint8_t Channel, uint32_t Gain);
int32_t VD6283TX_GetGain(VD6283TX_Object_t *pObj, uint8_t Channel, uint32_t *pGain);
int32_t VD6283TX_SetInterMeasurementTime(VD6283TX_Object_t *pObj, uint32_t InterMeasurementTime);
int32_t VD6283TX_GetInterMeasurementTime(VD6283TX_Object_t *pObj, uint32_t *pInterMeasurementTime);
int32_t VD6283TX_Start(VD6283TX_Object_t *pObj, uint8_t Mode);
int32_t VD6283TX_Stop(VD6283TX_Object_t *pObj);
int32_t VD6283TX_StartFlicker(VD6283TX_Object_t *pObj, uint8_t Channel, uint8_t OutputMode);
int32_t VD6283TX_StopFlicker(VD6283TX_Object_t *pObj);
int32_t VD6283TX_GetValues(VD6283TX_Object_t *pObj, uint32_t *pResult);
int32_t VD6283TX_SetControlMode(VD6283TX_Object_t *pObj, uint32_t ControlMode, uint32_t Value);

int32_t VD6283TX_GetSaturation(VD6283TX_Object_t *pObj, uint32_t *pValue);

#ifdef __cplusplus
}
#endif

#endif /* VD6283TX_H */
