#ifndef DELAY_H_
#define DELAY_H_

#ifdef __FREERTOS_H
  /* include RTOS header files */
  #include "FreeRTOS.h" /* for vTaskDelay() */
  #include "task.h"
#endif

/* TODO: insert other definitions and declarations here. */
#include "fsl_clock.h" /*!< To call specific Kinetis SDK clock API to use in DELAY_CLOCK_FREQUENCY macro!*/

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup delay
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define DELAY_CPU_IS_ARM_CORTEX_M      /*!< Comment this macro, if an ARM Cortex CPU is being used.*/
#define DELAY_ARM_CORTEX_M 0           /*!< The ARM Cortex CPU number.*/
#define DELAY_CPU_IS_RISC_V            /*!< Macro for RISC-V CPU.*/
/*!< If ARM Cortex CPU is equal or higher than M3, you can use register cycle counter.
 *   Comment if do not want to use it. */
#define DELAY_USE_ARM_CYCLE_COUNTER
#define DELAY_CLOCK_FREQUENCY CLOCK_GetCoreSysClkFreq() /*!< Specific microcontroller CPU clock frequency. */

#ifdef DELAY_CPU_IS_ARM_CORTEX_M
  #undef DELAY_CPU_IS_RISC_V
  #if (DELAY_ARM_CORTEX_M < 3)
     #undef DELAY_USE_ARM_CYCLE_COUNTER
  #endif
#endif /* DELAY_CPU_IS_ARM_CORTEX_M */

/*!< Variables set in initialization function, to be used by the entire library. Do not modify!*/
extern uint32_t g_mcuCoreFrequency, g_mcuCyclesForUs, g_mcuCyclesForMs;


/*******************************************************************************
 * API
 ******************************************************************************/

/**
 * @brief Calculates the needed cycles based on core clock frequency
 *        to get a delay of a predetermined time in microseconds.
 *
 * @param ms - the time interval in us.
 *
 * @return The cycles number.
 *
 */
#define Delay_GetNofCyclesUs(us)  ((us)*g_mcuCyclesForUs)

/**
 * @brief Calculates the needed cycles based on core clock frequency
 *        to get a delay of a predetermined time in nanoseconds.
 *
 * @param ms - the time interval in ns.
 *
 * @return The cycles number.
 *
 */
#define Delay_GetNofCyclesNs(ns)  (((ns)*g_mcuCyclesForUs)/1000)

/**
 * @brief Initialize the delayer module.
 *
 * @note Always call this function before using any other API function.
 *
 */
void Delay_Init(void);

/**
 * @brief Block the current firmware execution until the
 *        number of core cycles is reached.
 *
 * @param cycles - the number of core cycles.
 *
 */
void Delay_WaitCycles(uint32_t cycles);

/**
 * @brief  Wait for a specified time in milliseconds.
 *
 *        The firmware execution is blocked inside the
 *        function.
 *
 * @param ms - How many milliseconds the function has to wait.
 *
 * @note The mean error obtained in ARM Cortex >= M3 CPUs
 *       was about +6.8e-4%
 *
 */
void Delay_Waitms(uint16_t ms);

/**
 * @brief  Wait for a specified time in microseconds.
 *
 *        The firmware execution is blocked inside the
 *        function.
 *
 * @param ms - How many microseconds the function has
 *             to wait.
 *
 * @note The mean error obtained in ARM Cortex >= M3 CPUs
 *       was very variable (ex.: +0.04%, 0%, -0.007,...)
 *
 */
#define Delay_Waitus(us) Delay_WaitCycles(Delay_GetNofCyclesUs(us))

/**
 * @brief  Wait for a specified time in nanoseconds.
 *
 *        The firmware execution is blocked inside the
 *        function.
 *
 * @param ms - How many nanoseconds the function has to wait.
 *
 * @note This function is basically a wrapper for the "Delay_Waitus", to express
 *       values in ns. It is not accurate for small intervals expressed in ns.
 *
 */
#define Delay_Waitns(ns) Delay_WaitCycles(Delay_GetNofCyclesNs(ns))

/**
 * @brief  If an RTOS is enabled, this routine will use a non-blocking
 *         wait method. Otherwise it will do a busy/blocking wait.
 *
 * @param ms - How many milliseconds the function has to wait.
 *
 */
#ifdef __FREERTOS_H
#define Delay_WaitOSms(ms) vTaskDelay(pdMS_TO_TICKS(ms)) /* use FreeRTOS API */
#else
#define Delay_WaitOSms(ms) Delay_Waitms(ms) /* no RTOS used, so use normal wait */
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

/*! @}*/

#endif
