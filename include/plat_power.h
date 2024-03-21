/*
 * If not stated otherwise in this file or this component's LICENSE file the
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
 * @addtogroup HPK Hardware Porting Kit
 * @{
 * @par The Hardware Porting Kit
 * HPK is the next evolution of the well-defined Hardware Abstraction Layer
 * (HAL), but augmented with more comprehensive documentation and test suites
 * that OEM or SOC vendors can use to self-certify their ports before taking
 * them to RDKM for validation or to an operator for final integration and
 * deployment. The Hardware Porting Kit effectively enables an OEM and/or SOC
 * vendor to self-certify their own Video Accelerator devices, with minimal RDKM
 * assistance.
 *
 */

 /**
 * @defgroup POWER_MANAGER Power Manager Module
 * @{
 */

/**
 * @defgroup POWER_MANAGER_HAL Power Manager HAL
 * @{
 * Described herein are the PWRMGR_HAL HAL types and functions that are part of the Power
 * Manager HAL. All listeners should releases resources when
 * entering POWER OFF/STANDBY state and re-acquire them when entering POWER ON state.
 */

/**
 * @defgroup IARM_PLAT_POWER_API Power Manager (HAL Types and Public API)
 * Described herein are the IARM-Bus HAL types and functions that are part of the Power
 * Manager application. This manager monitors Power IR key events and reacts to power
 * state changes based on  RDK Power Management Specification. It dispatches
 * Power Mode Change events to IARM-Bus. All listeners should releases resources when
 * entering POWER OFF/STANDBY state and re-acquire them when entering POWER ON state.
 */

/**
 * @defgroup PLAT_POWER_H Plat Power
 * @{
 */

/**
 * @file plat_power.h
 *
 * @par Abbreviations
 * - HAL:     Hardware Abstraction Layer
 * - CPE:     Customer Premises Equipment
 * - CPU:     Central Processing Unit
 * 
 *
 * @par Implementation Notes
 * -# None
 *
 */


#ifndef _POWERMGR_PLAT_H
#define _POWERMGR_PLAT_H
#include "pwrMgr.h"
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Initializes the underlying Power Management module
 *
 * This function must initialize all aspects of the CPE's Power Management module.
 *
 * @return    Returns the status of the operation
 * @retval    0 if successful, appropiate error code otherwise.
 *
 */
int PLAT_INIT(void);

/**
 * @brief Sets the CPE Power State
 *
 * This fumction is just required to hold the value of the current power state status.
 *
 * @param[in]  newState - The new power state value
 *
 * @return    Returns the status of the operation.
 * @retval    0 if successful, appropiate error code otherwise.
 * 
 * @pre PLAT_INIT() must be called before calling this API
 * 
 * @warning This API is Not thread safe
 * 
 * @see PLAT_API_GetPowerState(), IARM_Bus_PWRMgr_PowerState_t (@see section)
 * 
 */
int PLAT_API_SetPowerState(IARM_Bus_PWRMgr_PowerState_t newState);

/**
 * @brief Gets the CPE Power State
 *
 * @param[out] curState  - The current power state of the CPE
 *
 * @return Returns the status of the operation.
 * @retval 0 if successful, appropiate error code otherwise.
 * 
 * @pre PLAT_INIT() must be called before calling this API
 *  
 * @warning This API is Not thread safe
 * 
 * @see PLAT_API_SetPowerState(), IARM_Bus_PWRMgr_PowerState_t()
 *
 */
int PLAT_API_GetPowerState(IARM_Bus_PWRMgr_PowerState_t *curState);

#ifdef ENABLE_THERMAL_PROTECTION

/**
 * @brief Get the  current temperature of the core.
 *
 * @param[out] curState         - The current state of the core temperature
 * @param[out] curTemperature   - Raw temperature value of the core
 *                                in degrees Celsius
 * @param[out] wifiTemperature  - Raw temperature value of the wifi chip
 *                                in degrees Celsius
 * @pre PLAT_INIT() must be called before calling this API
 *
 * @see for IARM_Bus_PWRMgr_ThermalState_t()
 *
 * @return Returns the status of the operation.
 * @retval 0 if successful, appropiate error code otherwise.
 *
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
 * @pre PLAT_INIT() must be called before calling this API
 *
 * @return  Returns the status of the operation.
 * @retval  0 if successful, appropiate error code otherwise.
 *
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
 * @pre PLAT_INIT() must be called before calling this API
 * @return Returns the status of the operation.
 * @retval 0 if successful, appropiate error code otherwise.
 *
 */
int PLAT_API_GetTempThresholds(float *tempHigh, float *tempCritical);

/**
 * @brief Get clock speeds for this device for the given states
 *
 * @param [out] cpu_rate_Normal  The clock rate to be used when in the 'normal' state
 * @param [out] cpu_rate_Scaled  The clock rate to be used when in the 'scaled' state
 * @param [out] cpu_rate_Minimal The clock rate to be used when in the 'minimal' state
 *
 * @pre PLAT_INIT() must be called before calling this API
 * @return 1 if operation is attempted 0 otherwise
 *
 */
int PLAT_API_DetemineClockSpeeds(uint32_t *cpu_rate_Normal, uint32_t *cpu_rate_Scaled, uint32_t *cpu_rate_Minimal);

/**
 * @brief This API sets the clock speed of the CPU.
 *
 * @param [in] speed  One of the predefined parameters to set the clock speed.
 *
 * @pre PLAT_INIT() must be called before calling this API
 * @return Returns the status of the operation
 * @retval returns 1, if operation is attempted and 0 
 *
 */
int PLAT_API_SetClockSpeed(uint32_t speed);

/**
 * @brief This API returns the clock speed of the CPU
 *
 * @param [out] speed One of the predefined parameters
 *
 * @pre PLAT_INIT() must be called before calling this API
 * @return Returns the current clock speed.
 *
 */
int PLAT_API_GetClockSpeed(uint32_t *speed);

#endif //ENABLE_THERMAL_PROTECTION


/**
 * @brief Enables or disables the Wakeup source type
 *
 * @param [in] srcType  - Wake up source type
 * @param [in] enable   - Enable or disable Wake up source
 *                        True for enabled, false for disabled
 * 
 * @return Returns the status of the API execution
 * @retval 0 for success, 1 for unsupported source type, negative value for error cases.
 * @pre PLAT_INIT() must be called before calling this API
 * 
 * @warning This API is Not thread safe
 * 
 * @see PLAT_API_GetWakeupSrc(), WakeupSrcType_t
 */
int32_t PLAT_API_SetWakeupSrc(WakeupSrcType_t srcType, bool  enable);

/**
 * @brief Checks if the wake up source is enabled or disabled for the device
 *
 * @param [in] srcType  - Wake up source type
 * @param [out] enable  - Variable to store if wake up source type is enabled or disabled
 *                        True for enabled, false for disabled
 *
 * @return Returns the status of the API execution
 * @retval 0 for success, 1 for unsupported source type, negative value for error cases.
 *
 * @pre PLAT_INIT() must be called before calling this API
 * 
 * @warning This API is Not thread safe
 * 
 * @see WakeupSrcType_t, PLAT_API_SetWakeupSrc()
 */
int32_t PLAT_API_GetWakeupSrc(WakeupSrcType_t srcType, bool  *enable);

/**
 * @brief Resets the power state of the device
 * 
 * @note PLAT_Reset() will be deprecated.
 *
 * @param[in] newState  - The state to be set
 * 
 * @pre PLAT_INIT() must be called before calling this API
 * 
 * @warning This API is Not thread safe
 *
 * @see IARM_Bus_PWRMgr_PowerState_t
 * 
 */
void PLAT_Reset(IARM_Bus_PWRMgr_PowerState_t newState);

/**
 * @brief Terminates the CPE Power Management module
 *
 * All data structures used within Power Management module must be reset and release any
 * Power Management specific handles and resources.
 * 
 * @pre PLAT_INIT() must be called before calling this API
 *
 */
void PLAT_TERM(void);


#ifdef __cplusplus
}
#endif
#endif //End of _POWERMGR_PLAT_H

/** @} */ // End of PLAT_POWER_H
/** @} */ // End of POWER_MANAGER_HAL
/** @} */ // End of POWER_MANAGER
/** @} */ // End of HPK
