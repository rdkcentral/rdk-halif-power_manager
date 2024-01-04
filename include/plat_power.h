/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
/**
 * @defgroup IARM_PLAT_POWER_API Power Manager (HAL Types and Public API)
 * Described herein are the IARM-Bus HAL types and functions that are part of the Power
 * Manager application. This manager monitors Power IR key events and reacts to power
 * state changes based on  RDK Power Management Specification. It dispatches
 * Power Mode Change events to IARM-Bus. All listeners should releases resources when
 * entering POWER OFF/STANDBY state and re-acquire them when entering POWER ON state.
 * @ingroup IARMMGR_HAL
 */
/**
* @defgroup iarmmgrs
* @{
* @defgroup hal
* @{
**/
#ifndef _POWERMGR_PLAT_H
#define _POWERMGR_PLAT_H
#include "pwrMgr.h"
#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @addtogroup IARM_PLAT_POWER_API
 * @{
 */
/**
 * @todo Should a callback function mode and registration API be added here?
 */
 /** @addtogroup IARM_BUS_PWRMGR_HAL_API IARM-Bus HAL Power Manager API.
 *  @ingroup IARM_BUS
 *
 *  Described herein are the IARM-Bus HAL types and functions that are part of the Power
 *  Manager application. This manager monitors Power IR key events and reacts to power
 *  state changes based on Comcast RDK Power Management Specification. It dispatches
 *  Power Mode Change events to IARM-Bus. All listeners should releases resources when
 *  entering POWER OFF/STANDBY state and re-acquire them when entering POWER ON state.
 *
 *  @{
 */
/**
 * @todo Should a callback function mode and registration API be added here?
 */
/**
 * @brief Initialize the underlying Power Management module.
 *
 * This function must initialize all aspects of the CPE's Power Management module.
 *
 * @return    Returns the status of the operation
 * @retval    0 if successful, appropiate error code otherwise.
 */
int PLAT_INIT(void);
/**
 * @brief This API sets the CPE Power State.
 *
 * This function sets the CPE's current power state to the specified state.
 *
 * @param[in]  newState   The power state to which to set the CPE.
 *
 * @return    Returns the status of the operation.
 * @retval    0 if successful, appropiate error code otherwise.
 */
int PLAT_API_SetPowerState(IARM_Bus_PWRMgr_PowerState_t newState);
/**
 * @brief This function is used to get the CPE Power State.
 *
 * This function returns the current power state of the CPE.
 *
 * @param[in] curState The address of a location to hold the current power state of the CPE on return.
 *
 * @return Returns the status of the operation.
 * @retval 0 if successful, appropiate error code otherwise.
 */
int PLAT_API_GetPowerState(IARM_Bus_PWRMgr_PowerState_t *curState);
#ifdef ENABLE_THERMAL_PROTECTION
/**
 * @brief Get the  current temperature of the core.
 *
 * @param[out] state            The current state of the core temperature
 * @param[out] curTemperature   Raw temperature value of the core
 *                              in degrees Celsius
 * @param[out] wifiTemperature  Raw temperature value of the wifi chip
 *                              in degrees Celsius
 *
 * @return Returns the status of the operation.
 * @retval 0 if successful, appropiate error code otherwise.
*/
int PLAT_API_GetTemperature(IARM_Bus_PWRMgr_ThermalState_t *curState, float *curTemperature, float *wifiTemperature);
/**
 * @brief Set temperature thresholds which will determine the state returned from a call to mfrGetTemperature.
 *
 * @param[in] tempHigh       Temperature threshold at which mfrTEMPERATURE_HIGH
 *                           state will be reported.
 * @param[in] tempCritical   Temperature threshold at which mfrTEMPERATURE_CRITICAL
 *                           state will be reported.
 *
 * @return  Returns the status of the operation.
 * @retval  0 if successful, appropiate error code otherwise.
 */
int PLAT_API_SetTempThresholds(float tempHigh, float tempCritical);
/**
 * @brief Get temperature thresholds which will determine the state returned from a call to mfrGetTemperature.
 *
 * @param[out] tempHigh      Temperature threshold at which mfrTEMPERATURE_HIGH
 *                           state will be reported.
 * @param[out] tempCritical  Temperature threshold at which mfrTEMPERATURE_CRITICAL
 *                           state will be reported.
 *
 * @return Returns the status of the operation.
 * @retval 0 if successful, appropiate error code otherwise.
 */
int PLAT_API_GetTempThresholds(float *tempHigh, float *tempCritical);
/**
 * @brief Get clock speeds for this device for the given states
 *
 * @param [out] cpu_rate_Normal  The clock rate to be used when in the 'normal' state
 * @param [out] cpu_rate_Scaled  The clock rate to be used when in the 'scaled' state
 * @param [out] cpu_rate_Minimal The clock rate to be used when in the 'minimal' state
 *
 * @return 1 if operation is attempted 0 otherwise
 */
int PLAT_API_DetemineClockSpeeds(uint32_t *cpu_rate_Normal, uint32_t *cpu_rate_Scaled, uint32_t *cpu_rate_Minimal);
/**
 * @brief This API sets the clock speed of the CPU.
 * @param [in] speed  One of the predefined parameters to set the clock speed.
 *
 * @return Returns the status of the operation
 * @retval returns 1, if operation is attempted and 0 otherwise
 */
int PLAT_API_SetClockSpeed(uint32_t speed);
/**
 * @brief This API returns the clock speed of the CPU
 *
 * @param [out] speed One of the predefined parameters
 * @return Returns the current clock speed.
 */
int PLAT_API_GetClockSpeed(uint32_t *speed);
#endif //ENABLE_THERMAL_PROTECTION
/**
 * @brief This API used to enable or disable the Wakeup source type.
 *
 * @param [in] srcType Source type to be enabled or disabled
 * @param [in] enable Bool value indicating to enable or disable the source type.
 * @return Returns the status of the API execution
 * @retval 0 for success, 1 for unsupported source type, negative value for error cases.
 */
int32_t PLAT_API_SetWakeupSrc(WakeupSrcType_t srcType, bool  enable);
/**
 * @brief This API used get if the wake up source is enabled or disabled for the device.
 *
 * @param [in] srcType Source type to be enabled or disabled
 * @param [out] enable Bool value indicating to enable or disable the source type.
 * @return Returns the status of the API execution
 * @retval 0 for success, 1 for unsupported source type, negative value for error cases.
 */
int32_t PLAT_API_GetWakeupSrc(WakeupSrcType_t srcType, bool  *enable);
/**
 * @brief This API resets the power state of the device.
 *
 * @param[in] newState The state to be set.
 * The input paramter is not in use.
 */
void PLAT_Reset(IARM_Bus_PWRMgr_PowerState_t newState);
/**
 * @brief This API terminates the power management  module.
 *
 * This function must terminate the CPE Power Management module. It must reset any data
 * structures used within Power Management module and release any Power Management
 * specific handles and resources.
 */
void PLAT_TERM(void);
/** @} */ //End of Doxygen Tag
#ifdef __cplusplus
}
#endif
#endif
/** @} */
/** @} */
