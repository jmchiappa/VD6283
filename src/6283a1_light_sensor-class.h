/**
  ******************************************************************************
  * @file    6283a1_light_sensor.h
  * @author  IMG SW Application Team
  * @brief   This file contains the common defines and functions prototypes for
  *          the vd6283tx_light_sensor.c driver.
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
#ifndef VD6283A1_XNUCLEO_LIGHT_SENSOR_H
#define VD6283A1_XNUCLEO_LIGHT_SENSOR_H

/* Includes ------------------------------------------------------------------*/
#include "vd6283tx/light_sensor.h"
#include "vd6283tx/vd6283tx.h"
#include "Arduino.h"
#include "Wire.h"

typedef struct
{
  uint8_t NumberOfChannels;  /*!< Max: LIGHT_SENSOR_MAX_CHANNELS */
  uint8_t FlickerDetection;  /*!< Not available: 0, Available: 1 */
  uint8_t Autogain;          /*!< Not available: 0, Available: 1 */
  uint8_t Flicker;           /*!< Not available: 0, Available: 1 */
} LIGHT_SENSOR_Capabilities_t;

/** @defgroup XNUCLEO_6283A1_LIGHT_SENSOR_Exported_Constants Exported Constants
  * @{
  */
#define LIGHT_SENSOR_VD6283TX_ADDRESS   (0x40U)
#define LIGHT_SENSOR_MAX_CHANNELS       VD6283TX_MAX_CHANNELS
#define LIGHT_SENSOR_ALL_CHANNELS       VD6283TX_ALL_CHANNELS

#define LIGHT_SENSOR_MODE_SINGLESHOT    VD6283TX_MODE_SINGLESHOT
#define LIGHT_SENSOR_MODE_CONTINUOUS    VD6283TX_MODE_CONTINUOUS
#define LIGHT_SENSOR_FLICKER_ANALOG     VD6283TX_FLICKER_ANALOG
#define LIGHT_SENSOR_CTRL_DARK          VD6283TX_CTRL_DARK

#define LIGHT_SENSOR_RED_CHANNEL        VD6283TX_RED_CHANNEL
#define LIGHT_SENSOR_VISIBLE_CHANNEL    VD6283TX_VISIBLE_CHANNEL
#define LIGHT_SENSOR_BLUE_CHANNEL       VD6283TX_BLUE_CHANNEL
#define LIGHT_SENSOR_GREEN_CHANNEL      VD6283TX_GREEN_CHANNEL
#define LIGHT_SENSOR_IR_CHANNEL         VD6283TX_IR_CHANNEL
#define LIGHT_SENSOR_CLEAR_CHANNEL      VD6283TX_CLEAR_CHANNEL

/** @defgroup XNUCLEO_6283A1_LIGHT_SENSOR_Exported_Functions Exported Functions
  * @{
  */
class VD6283TX {
  public:
    VD6283TX(TwoWire &port);
    int32_t Begin();
    int32_t ReadID(uint32_t *pId);
    int32_t GetCapabilities(LIGHT_SENSOR_Capabilities_t *pCapabilities);
    int32_t SetExposureTime(uint32_t ExposureTime);
    int32_t GetExposureTime(uint32_t *pExposureTime);
    int32_t SetGain(uint8_t Channel, uint32_t Gain);
    int32_t GetGain(uint8_t Channel, uint32_t *pGain);
    int32_t SetInterMeasurementTime(uint32_t InterMeasurementTime);
    int32_t GetInterMeasurementTime(uint32_t *pInterMeasurementTime);
    int32_t Start(uint8_t Mode);
    int32_t Stop();
    int32_t StartFlicker(uint8_t Channel, uint8_t OutputMode);
    int32_t StopFlicker();
    int32_t GetValues(uint32_t *pResult);
    int32_t SetControlMode(uint32_t ControlMode, uint32_t Value);
    int32_t GetSaturation(uint32_t *pValue);
    int32_t VD6283A1_I2C_Init();
    int32_t VD6283A1_I2C_DeInit();
    int32_t VD6283A1_I2C_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
    int32_t VD6283A1_I2C_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length);
    int32_t VD6283A1_GetTick() { return millis(); }
  private:
    int32_t DeInit();
    LIGHT_SENSOR_Drv_t *VD6283A1_LIGHT_SENSOR_Drv = (LIGHT_SENSOR_Drv_t *) &VD6283TX_LIGHT_SENSOR_Driver;
    LIGHT_SENSOR_Capabilities_t VD6283A1_LIGHT_SENSOR_Cap;
    VD6283TX_Object_t VD6283TXObj;
    TwoWire &port_ = Wire;
};

#endif /* VD6283A1_XNUCLEO_LIGHT_SENSOR_H */
