/**
  ******************************************************************************
  * @file    6283a1_light_sensor.c
  * @author  IMG SW Application Team
  * @brief   This file includes the driver for the light sensor mounted on the
  *          X-NUCLEO VD6283A1 expansion board.
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

#include "vd6283tx/modules/busIO/IO.h"
#include "6283a1_light_sensor-class.h"
#include "stm32l4xx_nucleo_errno.h"

int32_t VD6283::VD6283TX::begin(TwoWire &port)
{
  int32_t ret;
  uint32_t id;
  VD6283TXObj.IO = (void *) &i2cBus;
  i2cBus.begin(VD6283::CONSTANT::I2C_DEFAULT_ADDRESS>>1,port);
  if (VD6283TX_ReadID(&VD6283TXObj, &id) != VD6283TX_OK)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    if (id != VD6283TX_DEVICE_ID)
    {
      ret = BSP_ERROR_UNKNOWN_COMPONENT;
    }
    else
    {
      if (VD6283TX_Init(&VD6283TXObj) != VD6283TX_OK)
      {
        ret = BSP_ERROR_INIT_FAILURE;
      }
      else if (VD6283TX_GetCapabilities(&VD6283TXObj, &VD6283A1_LIGHT_SENSOR_Cap) != VD6283TX_OK)
      {
        ret = BSP_ERROR_GET_CAPABILITIES__FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
  }
  return ret;
}

int32_t VD6283::VD6283TX::DeInit()
{
  int32_t ret;

  if (VD6283TX_DeInit(&VD6283TXObj) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Read the light sensor device ID.
  * @retval device ID
  */
uint32_t VD6283::VD6283TX::ReadID()
{
  uint32_t pId;
  if (VD6283TX_ReadID(&VD6283TXObj, &pId) < 0)
  {
    return BSP_ERROR_COMPONENT_FAILURE;
  }

  return pId;
}

/**
  * @brief Get the light sensor capabilities.
  * @retval boolean true : data available otherwise false
  */
uint32_t VD6283::VD6283TX::isDataReady()
{
  uint8_t pIsReady;
  if (VD6283TX_isDataReady(&VD6283TXObj, &pIsReady) < 0)
  {
    return BSP_ERROR_COMPONENT_FAILURE;
  }
  return (uint32_t)pIsReady;
}

/**
  * @brief Get the light sensor capabilities.
  * @retval BSP status
  */
int32_t VD6283::VD6283TX::GetCapabilities(VD6283TX_Capabilities_t *pCapabilities)
{
  int32_t ret;

  if (VD6283TX_GetCapabilities(&VD6283TXObj, pCapabilities) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Set the exposure time.
  * @param ExposureTime    New exposure time to be applied.
  * @warning This function must not be called when a capture is ongoing.
  * @retval BSP status
  */
int32_t VD6283::VD6283TX::SetExposureTime(uint32_t ExposureTime)
{
  int32_t ret;

  if (VD6283TX_SetExposureTime(&VD6283TXObj, ExposureTime) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Get the exposure time.
  * @retval the current exposure time value.
  */
uint32_t VD6283::VD6283TX::GetExposureTime()
{
  uint32_t pExposureTime;
  if (VD6283TX_GetExposureTime(&VD6283TXObj, &pExposureTime) < 0)
  {
    return BSP_ERROR_COMPONENT_FAILURE;
  }
  return pExposureTime;
}

int32_t VD6283::VD6283TX::SetGain(float Gain)
{
  int32_t ret = BSP_ERROR_NONE;
  uint16_t gain = (uint16_t)(Gain*256); //encoded to 8.8
  for(uint8_t channel=0 ; channel< VD6283::CHANNEL::LENGTH ;channel++) {
    if (VD6283TX_SetGain(&VD6283TXObj, channel, gain) < 0)
    {
      ret = BSP_ERROR_COMPONENT_FAILURE;
      break;
    }
  }
  return ret;
}

/**
  * @brief Set the gain of a channel.
  * @param Channel    Device channel.
  * @param Gain    New gain to be applied on the provided channel.
  * @warning This function must not be called when a capture is ongoing.
  * @retval BSP status
  */
int32_t VD6283::VD6283TX::SetGain(uint8_t Channel, float Gain)
{
  int32_t ret;

  uint16_t gain = (uint16_t)(Gain*256); //encoded to 8.8
  if (VD6283TX_SetGain(&VD6283TXObj, Channel, gain) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Get the current gain of a channel.
  * @param Channel    Device channel.
  * @retval BSP status
  */
uint32_t VD6283::VD6283TX::GetGain(uint8_t Channel)
{
  int32_t ret;
  uint32_t pGain;
  if (VD6283TX_GetGain(&VD6283TXObj, Channel, &pGain) < 0)
  {
    return BSP_ERROR_COMPONENT_FAILURE;
  }

  return pGain;
}

/**
  * @brief Set the inter-measurement time.
  * @param InterMeasurementTime    Inter-measurement to be applied.
  * @note This should be configured only when using the device in continuous mode.
  * @warning This function must not be called when a capture is ongoing.
  * @retval BSP status
  */
int32_t VD6283::VD6283TX::SetInterMeasurementTime(uint32_t InterMeasurementTime)
{
  int32_t ret;

  if (VD6283TX_SetInterMeasurementTime(&VD6283TXObj, InterMeasurementTime) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Get the inter-measurement time.
  * @retval the current inter-measurement time.
  */
uint32_t VD6283::VD6283TX::GetInterMeasurementTime()
{
  int32_t ret;
  uint32_t pInterMeasurementTime;

  if (VD6283TX_GetInterMeasurementTime(&VD6283TXObj, &pInterMeasurementTime) < 0)
  {
    return BSP_ERROR_COMPONENT_FAILURE;
  }
  return pInterMeasurementTime;
}

/**
  * @brief Start the light measurement on all channels.
  * @param Mode    Measurement mode (continuous or single-shot)
  * @retval BSP status
  */
int32_t VD6283::VD6283TX::Start(uint8_t Mode)
{
  int32_t ret;

  if (VD6283TX_Start(&VD6283TXObj, Mode) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Stop the measurement on all channels.
  * @retval BSP status
  */
int32_t VD6283::VD6283TX::Stop()
{
  int32_t ret;

  if (VD6283TX_Stop(&VD6283TXObj) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Start flicker capture.
  * @param Channel    The channel that will be used for flicker detection.
  * @param OutputMode    Analog or Digital depending on the hardware configuration.
  * @note The application must call VD6283A1_LIGHT_SENSOR_Start before calling this function.
  * @warning The flicker can be started only on one channel at a time.
  * @note Calling this function will enable ALS capture on all the other channels.
  * @retval BSP status
  */
int32_t VD6283::VD6283TX::StartFlicker(uint8_t Channel, uint8_t OutputMode)
{
  int32_t ret;

  if (VD6283TX_StartFlicker(&VD6283TXObj, Channel, OutputMode) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Stop flicker capture.
  * @retval BSP status
  */
int32_t VD6283::VD6283TX::StopFlicker()
{
  int32_t ret;

  if (VD6283TX_StopFlicker(&VD6283TXObj) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Returns the measurement values for all the channels.
  * @param Instance    Light sensor instance.
  * @param pResult    Pointer to an array which will be filled with the values of each channel.
  * @note The array size must match the number of channels of the device.
  * @retval BSP status
  */
int32_t VD6283::VD6283TX::GetValues(uint32_t *pResult)
{
  int32_t ret;

  if (VD6283TX_GetValues(&VD6283TXObj, pResult) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief Enable and disable control features.
  * @param ControlMode    Feature to be be enabled or disabled.
  * @param Value    Value to be applied.
  * @warning This function must not be called when a capture is ongoing.
  * @retval BSP status
  */
int32_t VD6283::VD6283TX::SetControlMode(uint32_t ControlMode, uint32_t Value)
{
  int32_t ret;

  if (VD6283TX_SetControlMode(&VD6283TXObj, ControlMode, Value) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

 /**
  * @brief Get saturation value from the device.
  * @param pValue    Pointer to the variable where the saturation value is stored.
  * @warning The saturation value is reset when the device is stopped.
  * @retval BSP status
  */
uint32_t VD6283::VD6283TX::GetSaturation()
{
  int32_t ret;
  uint32_t pValue;
  if (VD6283TX_GetSaturation(&VD6283TXObj, &pValue) < 0)
  {
    return BSP_ERROR_COMPONENT_FAILURE;
  }

  return pValue;
}
