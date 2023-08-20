#ifndef __PCF8575_PRO_H__
#define __PCF8575_PRO_H__

#include <stddef.h>
#include <i2cdev.h>
#include <esp_err.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "esp_idf_lib_helpers.h"
#include "pcf8575.h"


#ifdef __cplusplus
extern "C" {
#endif

#define LLL_ADDRESS 0x40    // A[2]A[1]A[0] = 000  
#define LLH_ADDRESS 0X42    // A[2]A[1]A[0] = 001   
#define LHL_ADDRESS 0X44    // A[2]A[1]A[0] = 010 
#define LHH_ADDRESS 0X46    // A[2]A[1]A[0] = 011 
#define HLL_ADDRESS 0X48    // A[2]A[1]A[0] = 100 
#define HLH_ADDRESS 0X4A    // A[2]A[1]A[0] = 101 
#define HHL_ADDRESS 0x4C    // A[2]A[1]A[0] = 110 
#define HHH_ADDRESS 0x4E    // A[2]A[1]A[0] = 111 

#define PCF8575_INTERRUPT_PIN GPIO_NUM_5

#define GPIO_pcf8575_NUM_0 0
#define GPIO_pcf8575_NUM_1 1
#define GPIO_pcf8575_NUM_2 2
#define GPIO_pcf8575_NUM_3 3
#define GPIO_pcf8575_NUM_4 4
#define GPIO_pcf8575_NUM_5 5
#define GPIO_pcf8575_NUM_6 6
#define GPIO_pcf8575_NUM_7 7
#define GPIO_pcf8575_NUM_10 8
#define GPIO_pcf8575_NUM_11 9
#define GPIO_pcf8575_NUM_12 10
#define GPIO_pcf8575_NUM_13 11
#define GPIO_pcf8575_NUM_14 12
#define GPIO_pcf8575_NUM_15 13
#define GPIO_pcf8575_NUM_16 14
#define GPIO_pcf8575_NUM_17 15

typedef struct {
    uint16_t io_state;
    int gpio_interrupt;
    i2c_dev_t *dev ;
    uint8_t address ;
} pcf8575_t ;

/**
 * @brief Initalize device descriptor
 * @param pcf8575 Struct of pcf8575
 * @param addr Address of I2C (0x0100[A2][A1][A0][R/W] for pcf8575])
 * @param port Port I2C
 * @param scl GPIO set up scl
 * @param sda GPIO set up sda 
 * @return ESP_OK 
 * 
*/
esp_err_t pcf8575_initialize(pcf8575_t *pcf8575, uint8_t addr, i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio);

/**
 * @brief Free device descriptor
 * @param pcf8575 Struct of pcf8575
 * @return ESP_OK
 */
esp_err_t pcf8575_deinitialize(pcf8575_t *pcf8575);

/**
 * @brief Read All GPIO port value
 * @param pcf8575 Struct of pcf8575
 * @param val 16-bit GPIO port value
 * @return ESP_OK
 */
esp_err_t pcf8575_readAllPin(pcf8575_t *pcf8575, uint16_t *val);

/**
 * @brief Write All GPIO port value
 * @param pcf8575 Struct of pcf8575
 * @param val 16-bit GPIO port value
 * @return ESP_OK
*/
esp_err_t pcf8575_writeAllPin(pcf8575_t *pcf8575, uint16_t val);

/**
 * @brief Read GPIO value
 * @param pcf8575 Struct of pcf8575
 * @param pin Number of GPIO
 * @param state logic 0 or logic 1
 * @return ESP_OK
*/
esp_err_t pcf8575_readOnePin(pcf8575_t *pcf8575, uint16_t pin, bool *state);

/**
 * @brief Write GPIO value
 * @param pcf8575 Struct of pcf8575
 * @param pin Number of GPIO
 * @param state logic 0 or logic 1
 * @return ESP_OK
*/
esp_err_t pcf8575_writeOnePin(pcf8575_t *pcf8575, uint16_t pin, bool state);

/**
 * @brief Funciton Interrupt
 * @param pcf8575 Struct of pcf8575
 * @param enable enable interrupt or prevent interrupt
*/
esp_err_t pcf8575_interrupt(pcf8575_t *pcf8575, bool enable);

/**
 * @brief Check interrupt occurred
 * @param pcf8575 Struct of pcf8575
 * @param occurred False(interrupt didn't occur) , True(interrup occurred)
*/
esp_err_t pcf8575_interruptCheck(pcf8575_t *pcf8575, bool *occurred);

/**
 * @brief Clear flag interrupt
 * @param pcf8575 Struct of pcf8575
*/
esp_err_t pcf8575_interruptClear(pcf8575_t *pcf8575);

#ifdef __cplusplus
}
#endif
/**@}*/

#endif /* __PCF8575_PRO_H__ */



