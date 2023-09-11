/**
 * @author Ho Xuan Phu (@Phu20214041) && Pham Van Sang (https://github.com/sang8022002)
 * @brief Library PCF8575
 * @date 2023-08-15
 * 
 * @copyright Copyright (C) 2023
*/



#ifndef __PCF8575_PRO_H__
#define __PCF8575_PRO_H__

#include <stddef.h>
#include "../../component/i2cdev/i2cdev.h"
#include <esp_err.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "../../component/esp_idf_lib_helpers/esp_idf_lib_helpers.h"
#include "../../component/pcf8575/pcf8575.h"
#include "sdkconfig.h"


#ifdef __cplusplus
extern "C" {
#endif



#define P00 0
#define P01 1
#define P02 2
#define P03 3
#define P04 4
#define P05 5
#define P06 6
#define P07 7
#define P10 8
#define P11 9
#define P12 10
#define P13 11
#define P14 12
#define P15 13
#define P16 14
#define P17 15

typedef struct {
    uint16_t io_state;
    i2c_dev_t *dev ;
    uint8_t address ;
    int gpio_interrupt;
} pcf8575_t ;
#define BV(x) (1 << (x))

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
esp_err_t pcf8575_initialize(pcf8575_t *pcf8575, i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio);

/**
 * @brief Free device descriptor
 * @param pcf8575 Struct of pcf8575
 * @return ESP_OK
 */
esp_err_t pcf8575_deinitialize(pcf8575_t *pcf8575);

/**
 * @brief Read All GPIO port value
 * @param pcf8575 Struct of pcf8575
 * @param value 16-bit GPIO port value
 * @return ESP_OK
 */
esp_err_t pcf8575_readAllPin(pcf8575_t *pcf8575, uint16_t *value);

/**
 * @brief Write All GPIO port value
 * @param pcf8575 Struct of pcf8575
 * @param value 16-bit GPIO port value
 * @return ESP_OK
*/
esp_err_t pcf8575_writeAllPin(pcf8575_t *pcf8575, uint16_t value);

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
 * @brief Funciton interrupt initialize
 * @param pcf8575 Struct of pcf8575
*/
esp_err_t pcf8575_interruptInitialize(pcf8575_t *pcf8575);

/**
 * @brief Function interrupt deinitialize
 * @param pcf8575 Struct of pcf8575
*/
esp_err_t pcf8575_interruptDeinitialize(pcf8575_t *pcf8575);

#ifdef __cplusplus
}
#endif
/**@}*/

#endif /* __PCF8575_PRO_H__ */



