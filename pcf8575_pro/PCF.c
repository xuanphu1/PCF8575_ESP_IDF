#include "PCF.h"

//----------------------****----------------------------------------------------------
// Initialize PCF8575
esp_err_t pcf8575_initialize(pcf8575_t *pcf8575, uint8_t addr, i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio){
    
    esp_err_t error_code = pcf8575_init_decs(pcf8575->dev, addr, port , sda_gpio, scl_gpio);
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
        ESP_LOGI(__func__,"pcf8575 deinitialize failed !")
        return error_code;
    }
    else {
        ESP_LOGI(__func__,"pcf8575 deinitialize successfully !")
        return error_code;
    }
}

esp_err_t pcf8575_readAllPin(pcf8575_t *pcf8575, uint16_t *val) 
{
    esp_err_t error_code = pcf8575_port_read(pcf8575->dev,pcf8575->io_state);
    if(error_code != ESP_OK){
        ESP_LOGI(__func__,"pcf8575 read all pin failed !");
        return error_code;
    }
    else{
        ESP_LOGI(__func__,"pcf8575 read all pin successfully !");
        return error_code;
    }
}


esp_err_t pcf8575_writeAllPin(pcf8575_t *pcf8575 ,uint16_t val){

    esp_err_t error_code = pcf8575_port_write(pcf8575->dev,val);
    if(error_code != ESP_OK){
        ESP_LOGI(__func__,"pcf8575 write all pin failed !");
        return error_code;
    }
    else{
        ESP_LOGI(__func__,"pcf8575 write all pin successfully !");
        return error_code;
    }
}

esp_err_t pcf8575_writeOnePin(pcf8575_t *pcf8575, uint8_t pin, bool state){

    
    if(pin > 15) return ESP_ERR_INVALID_ARG;

    uint16_t data = pcf8575->io_state ;
    if (state) data |= BV(pin);
    else data &= ~ BV(pin);

    return pcf8575_writeAllPin(pcf8575,data);
}

esp_err_t pcf8575_readOnePin(pcf8575_t *pcf8575, uint16_t pin, bool &state){
    if(pin > 15) return ESP_ERR_INVALID_ARG;

    uint16_t data = pcf8575->io_state ;
    *state = data & BV(pin);
    return ESP_OK;
}


void IRAM_ATTR interrupe_handler(void *arg){
    printf("Interrupt occupied!\n");
}

esp_err_t pcf8575_interrupt(pcf8575_t *pcf8575,bool enable){
    if (enable){
        // Cấu hình GPIO làm đầu vào với chế độ pull-pu là HIGH
        gpio_config_t io_conf;
        io_conf.intr_type = GPIO_INTR_NEGEDGE ; // Kích hoạt interrupt khi GPIO thay đổi
        io_conf.pin_bit_mask = (1ULL << PCF8575_INTERRUPT_PIN);
        io_conf.mode = GPIO_MODE_INPUT;
        io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
        gpio_config(&io_conf);
        
        // Hàm xử lý khi interrupt xảy ra
        gpio_isr_handler_add(PCF8575_INTERRUPT_PIN,interrupe_handler,NULL);
    }
    else {
        gpio_intr_disable(PCF8575_INTERRUPT_PIN);
    }
return ESP_OK;
}

esp_err_t pcf8575_interruptCheck(pcf8575_t *pcf8575, bool *occurred){
    if(!occurred){
        return ESP_ERR_INVALID_ARG;
    }

    int level = gpio_get_level(PCF8575_INTERRUPT_PIN);

    *occurred = (level == 0) ;
    return ESP_OK;
}

esp_err_t pcf8575_interruptClear(pcf8575_t *pcf8575) {
    uint16_t data;

    // Đọc trạng thái hiện tại của các chân I/O để xóa cờ interrupt
    esp_err_t ret = pcf8575_read(pcf8575->dev, &pcf8575->io_state);
    if (ret != ESP_OK) {
        return ret;
    }

    return ESP_OK;
}