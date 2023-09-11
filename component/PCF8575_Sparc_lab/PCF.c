#include "PCF.h"


//----------------------****----------------------------------------------------------
// Initialize PCF8575
esp_err_t pcf8575_initialize(pcf8575_t *pcf8575){
    pcf8575->address = CONFIG_PCF8575_ADDRESS;
    pcf8575->sda_gpio = CONFIG_PCF8575_SDA_GPIO;
    pcf8575->scl_gpio = CONFIG_PCF8575_SCL_GPIO;
    pcf8575->port = CONFIG_PCF8575_PORT_I2C;
    esp_err_t error_code = pcf8575_init_desc(pcf8575->dev, pcf8575->address, pcf8575->port , pcf8575->sda_gpio, pcf8575->scl_gpio);
        if (error_code != ESP_OK) {
            ESP_LOGI(__func__,"pcf8575 initialize failed !");
            return error_code ;
        }
        else {
            ESP_LOGI(__func__,"pcf8575 initialize successfully !");
            pcf8575_port_write(pcf8575->dev,0xFFFF);
            return error_code;
        }
}
// 
esp_err_t pcf8575_deinitialize(pcf8575_t *pcf8575){
    esp_err_t error_code = pcf8575_free_desc(pcf8575->dev);
    if(error_code != ESP_OK){
        ESP_LOGI(__func__,"pcf8575 deinitialize failed !");
        return error_code ;
    }
    else {
        ESP_LOGI(__func__,"pcf8575 deinitialize successfully !");
        return ESP_OK ;
    }
}

esp_err_t pcf8575_readAllPin(pcf8575_t *pcf8575, uint16_t *value) 
{
    esp_err_t error_code = pcf8575_port_read(pcf8575->dev,&pcf8575->io_state);
    if(error_code != ESP_OK){
        ESP_LOGI(__func__,"pcf8575 read all pin failed !");
        return error_code;
    }
    else{
        ESP_LOGI(__func__,"pcf8575 read all pin successfully !");
        return error_code;
    }
}


esp_err_t pcf8575_writeAllPin(pcf8575_t *pcf8575 ,uint16_t value){

    esp_err_t error_code = pcf8575_port_write(pcf8575->dev,value);
    if(error_code != ESP_OK){
        ESP_LOGI(__func__,"pcf8575 write all pin failed !");
        return error_code;
    }
    else{
        ESP_LOGI(__func__,"pcf8575 write all pin successfully !");
        return error_code;
    }
}

esp_err_t pcf8575_writeOnePin(pcf8575_t *pcf8575, uint16_t pin, bool state){

    
    if(pin > 15) return ESP_ERR_INVALID_ARG;

    uint16_t data = pcf8575->io_state ;
    if (state) data |= BV(pin);
    else data &= ~ BV(pin);

    return pcf8575_writeAllPin(pcf8575,data);
}

esp_err_t pcf8575_readOnePin(pcf8575_t *pcf8575, uint16_t pin, bool *state){
    if(pin > 15) return ESP_ERR_INVALID_ARG;

    uint16_t data = pcf8575->io_state ;
    *state = data & BV(pin);
    return ESP_OK;
}


// Hàm xử lý ngắt
void IRAM_ATTR interrupe_handler(void *arg){
    // Function
}

// Hàm cấu hình interrupt
esp_err_t pcf8575_interruptInitialize(pcf8575_t *pcf8575){
    // Cấu hình GPIO làm đầu vào với chế độ pull-pu là HIGH

    pcf8575->gpio_interrupt = CONFIG_PCF8575_INTERRUPT_GPIO;
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_NEGEDGE ; // Kích hoạt interrupt khi GPIO thay đổi
    io_conf.pin_bit_mask = (1ULL << pcf8575->gpio_interrupt);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
    
    // Hàm xử lý khi interrupt xảy ra
    gpio_isr_handler_add(pcf8575->gpio_interrupt,interrupe_handler,NULL);

    return ESP_OK;
}

// Hàm vô hiệu hóa interrupt
esp_err_t pcf8575_interruptDeinitialize(pcf8575_t *pcf8575){    

    //int pinInterrupt = CONFIG_PCF8575_INTERRUPT_GPIO;
    gpio_intr_disable(pcf8575->gpio_interrupt);
    return ESP_OK;

}
