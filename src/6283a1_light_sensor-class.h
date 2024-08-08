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
#include "vd6283tx/vd6283tx.h"
#include "Arduino.h"
#include "Wire.h"
#include "vd6283tx/modules/busIO/IO.h"

namespace VD6283 {
  namespace CONSTANT {
    byte const I2C_DEFAULT_ADDRESS = (0x40U);
    byte const MAX_CHANNELS        = VD6283TX_MAX_CHANNELS;
    byte const ALL_CHANNELS        = VD6283TX_ALL_CHANNELS;
  }
  namespace MODE {
    byte const SINGLESHOT          = VD6283TX_MODE_SINGLESHOT;
    byte const CONTINUOUS          = VD6283TX_MODE_CONTINUOUS;
    byte const FLICKER_ANALOG      = VD6283TX_FLICKER_ANALOG;
    byte const CTRL_DARK           = VD6283TX_CTRL_DARK;
  }
  namespace CHANNEL {

    byte const RED                = VD6283TX_RED_CHANNEL;
    byte const VISIBLE            = VD6283TX_VISIBLE_CHANNEL;
    byte const BLUE               = VD6283TX_BLUE_CHANNEL;
    byte const GREEN              = VD6283TX_GREEN_CHANNEL;
    byte const IR                 = VD6283TX_IR_CHANNEL;
    byte const CLEAR              = VD6283TX_CLEAR_CHANNEL;
    byte const LENGTH             = VD6283TX_CLEAR_CHANNEL+1;
  }
  class VD6283TX {
    public:
      VD6283TX() {};
      int32_t begin(TwoWire &port);
      int32_t ReadID(uint32_t *pId);
      int32_t isDataReady(uint8_t *pIsDataReady);
      int32_t GetCapabilities(VD6283TX_Capabilities_t *pCapabilities);
      int32_t SetExposureTime(uint32_t ExposureTime);
      int32_t GetExposureTime(uint32_t *pExposureTime);
      int32_t SetGain(uint8_t Channel, uint32_t Gain);
      int32_t SetGain(uint32_t Gain);
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
      int32_t DeInit();
    private:
      VD6283TX_Capabilities_t VD6283A1_LIGHT_SENSOR_Cap;
      VD6283TX_Object_t VD6283TXObj;
      BusIO i2cBus;
  };
}

#endif /* VD6283A1_XNUCLEO_LIGHT_SENSOR_H */
