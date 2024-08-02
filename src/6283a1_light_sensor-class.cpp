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

/* File Info: ------------------------------------------------------------------
*                                   User NOTES

* Includes ------------------------------------------------------------------
* */

#include "6283a1_light_sensor-class.h"
#include "stm32l4xx_nucleo_errno.h"

/**
  * @}
  */

// static int32_t VD6283TX_Probe(uint32_t Instance);
// static int32_t vd6283tx_i2c_recover(void);

/**
  * @brief Initializes the light sensor.
  * @param Instance    Light sensor instance.
  * @retval BSP status
  */
VD6283TX::VD6283TX(TwoWire &port) {
  this->port_ = port;
}

int32_t VD6283TX::Begin()
{
  int32_t ret;
  uint32_t id;
  VD6283TXObj.IO.begin(LIGHT_SENSOR_VD6283TX_ADDRESS,port_);
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
      //VD6283A1_LIGHT_SENSOR_Drv = (LIGHT_SENSOR_Drv_t *) &VD6283TX_LIGHT_SENSOR_Driver;
      //VD6283A1_LIGHT_SENSOR_CompObj[Instance] = &(VD6283TXObj[Instance]);

      if (VD6283A1_LIGHT_SENSOR_Drv->Init(&VD6283TXObj) != VD6283TX_OK)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else if (VD6283A1_LIGHT_SENSOR_Drv->GetCapabilities(&VD6283TXObj, &VD6283A1_LIGHT_SENSOR_Cap)
               != VD6283TX_OK)
      {
        ret = BSP_ERROR_COMPONENT_FAILURE;
      }
      else
      {
        ret = BSP_ERROR_NONE;
      }
    }
  }
  return ret;
}

int32_t VD6283TX::DeInit()
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->DeInit(&VD6283TXObj) < 0)
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
  * @param Instance    Light sensor instance.
  * @param pId    Pointer to the device ID.
  * @retval BSP status
  */
int32_t VD6283TX::ReadID(uint32_t *pId)
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->ReadID(&VD6283TXObj, pId) < 0)
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
  * @brief Get the light sensor capabilities.
  * @param Instance    Light sensor instance.
  * @param pCapabilities    Pointer to the light sensor capabilities.
  * @retval BSP status
  */
int32_t VD6283TX::GetCapabilities(LIGHT_SENSOR_Capabilities_t *pCapabilities)
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->GetCapabilities(&VD6283TXObj, pCapabilities) < 0)
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
  * @param Instance    Light sensor instance.
  * @param ExposureTime    New exposure time to be applied.
  * @warning This function must not be called when a capture is ongoing.
  * @retval BSP status
  */
int32_t VD6283TX::SetExposureTime(uint32_t ExposureTime)
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->SetExposureTime(&VD6283TXObj, ExposureTime) < 0)
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
  * @param Instance    Light sensor instance.
  * @param pExposureTime    Pointer to the current exposure time value.
  * @retval BSP status
  */
int32_t VD6283TX::GetExposureTime(uint32_t *pExposureTime)
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->GetExposureTime(&VD6283TXObj, pExposureTime) < 0)
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
  * @brief Set the gain of a channel.
  * @param Instance    Light sensor instance.
  * @param Channel    Device channel.
  * @param Gain    New gain to be applied on the provided channel.
  * @warning This function must not be called when a capture is ongoing.
  * @retval BSP status
  */
int32_t VD6283TX::SetGain(uint8_t Channel, uint32_t Gain)
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->SetGain(&VD6283TXObj, Channel, Gain) < 0)
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
  * @param Instance    Light sensor instance.
  * @param Channel    Device channel.
  * @param pGain    Pointer to the current gain value.
  * @retval BSP status
  */
int32_t VD6283TX::GetGain(uint8_t Channel, uint32_t *pGain)
{
  int32_t ret;
  if (VD6283A1_LIGHT_SENSOR_Drv->GetGain(&VD6283TXObj, Channel, pGain) < 0)
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
  * @brief Set the inter-measurement time.
  * @param Instance    Light sensor instance.
  * @param InterMeasurementTime    Inter-measurement to be applied.
  * @note This should be configured only when using the device in continuous mode.
  * @warning This function must not be called when a capture is ongoing.
  * @retval BSP status
  */
int32_t VD6283TX::SetInterMeasurementTime(uint32_t InterMeasurementTime)
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->SetInterMeasurementTime(&VD6283TXObj, InterMeasurementTime) < 0)
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
  * @param Instance    Light sensor instance.
  * @param pInterMeasurementTime    Pointer to the current inter-measurement time.
  * @retval BSP status
  */
int32_t VD6283TX::GetInterMeasurementTime(uint32_t *pInterMeasurementTime)
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->GetInterMeasurementTime(&VD6283TXObj, pInterMeasurementTime) < 0)
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
  * @brief Start the light measurement on all channels.
  * @param Instance    Light sensor instance.
  * @param Mode    Measurement mode (continuous or single-shot)
  * @retval BSP status
  */
int32_t VD6283TX::Start(uint8_t Mode)
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->Start(&VD6283TXObj, Mode) < 0)
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
  * @param Instance    Light sensor instance.
  * @retval BSP status
  */
int32_t VD6283TX::Stop()
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->Stop(&VD6283TXObj) < 0)
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
  * @param Instance    Light sensor instance.
  * @param Channel    The channel that will be used for flicker detection.
  * @param OutputMode    Analog or Digital depending on the hardware configuration.
  * @note The application must call VD6283A1_LIGHT_SENSOR_Start before calling this function.
  * @warning The flicker can be started only on one channel at a time.
  * @note Calling this function will enable ALS capture on all the other channels.
  * @retval BSP status
  */
int32_t VD6283TX::StartFlicker(uint8_t Channel, uint8_t OutputMode)
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->StartFlicker(&VD6283TXObj, Channel, OutputMode) < 0)
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
  * @param Instance     Light sensor instance.
  * @retval BSP status
  */
int32_t VD6283TX::StopFlicker()
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->StopFlicker(&VD6283TXObj) < 0)
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
int32_t VD6283TX::GetValues(uint32_t *pResult)
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->GetValues(&VD6283TXObj, pResult) < 0)
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
  * @param Instance    Light sensor instance.
  * @param ControlMode    Feature to be be enabled or disabled.
  * @param Value    Value to be applied.
  * @warning This function must not be called when a capture is ongoing.
  * @retval BSP status
  */
int32_t VD6283TX::SetControlMode(uint32_t ControlMode, uint32_t Value)
{
  int32_t ret;

  if (VD6283A1_LIGHT_SENSOR_Drv->SetControlMode(&VD6283TXObj, ControlMode, Value) < 0)
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
  * @param Instance    Light sensor instance.
  * @param pValue    Pointer to the variable where the saturation value is stored.
  * @warning The saturation value is reset when the device is stopped.
  * @retval BSP status
  */
int32_t VD6283TX::GetSaturation(uint32_t *pValue)
{
  int32_t ret;

  if (VD6283TX_GetSaturation(&VD6283TXObj, pValue) < 0)
  {
    ret = BSP_ERROR_COMPONENT_FAILURE;
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/** @defgroup XNUCLEO_6283A1_LIGHT_SENSOR_Private_Functions Private Functions
  * @{
  */

/**
  * @brief Register Bus IOs if component ID is OK.
  * @param Instance    Light sensor instance.
  * @retval BSP status
  */
