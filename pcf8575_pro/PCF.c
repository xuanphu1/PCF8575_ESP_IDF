#include "PCF.h"
//----------------------****----------------------------------------------------------

// Hàm khởi tạo pcf8575
esp_err_t pcf8575_initialize(pcf8575_t *pcf8575, uint8_t addr, i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio){
    
    esp_err_t error_code = pcf8575_init_desc(pcf8575->dev, addr, port , sda_gpio, scl_gpio);
        if (error_code != ESP_OK) {
            ESP_LOGE(__func__,"pcf8575 initialize failed !");
            return error_code ;
        }
        else {
            ESP_LOGI(__func__,"pcf8575 initialize successfully !");
            pcf8575_port_write(pcf8575->dev,0xFFFF);
            return error_code;
        }
}
// Hàm khởi xóa khởi tạo 
esp_err_t pcf8575_deinitialize(pcf8575_t *pcf8575){
    esp_err_t error_code = pcf8575_free_desc(pcf8575->dev);
    if(error_code != ESP_OK){
        ESP_LOGE(__func__,"pcf8575 deinitialize failed !");
        return error_code ;
    }
    else {
        ESP_LOGI(__func__,"pcf8575 deinitialize successfully !");
        return ESP_OK ;
    }
}
// Hàm đọc trạng thái của tất cả các chân GPIO
esp_err_t pcf8575_readAllPin(pcf8575_t *pcf8575, uint16_t *val) 
{
    esp_err_t error_code = pcf8575_port_read(pcf8575->dev,&pcf8575->io_state);
    if(error_code != ESP_OK){
        ESP_LOGE(__func__,"pcf8575 read all pin failed !");
        return error_code;
    }
    else{
        ESP_LOGI(__func__,"pcf8575 read all pin successfully !");
        return error_code;
    }
}

// Hàm viết trạng thái của tất cả các chân GPIO
esp_err_t pcf8575_writeAllPin(pcf8575_t *pcf8575 ,uint16_t val){

    esp_err_t error_code = pcf8575_port_write(pcf8575->dev,val);
    if(error_code != ESP_OK){
        ESP_LOGE(__func__,"pcf8575 write all pin failed !");
        return error_code;
    }
    else{
        ESP_LOGI(__func__,"pcf8575 write all pin successfully !");
        return error_code;
    }
}
// Hàm viết trạng thái vào 1 chân GPIO
esp_err_t pcf8575_writeOnePin(pcf8575_t *pcf8575, uint16_t pin, bool state){

    
    if(pin > 15) return ESP_ERR_INVALID_ARG;

    uint16_t data = pcf8575->io_state ;
    if (state) data |= BV(pin);
    else data &= ~ BV(pin);

    return pcf8575_writeAllPin(pcf8575,data);
}
// Hàm đọc trạng thái của 1 chân GPIO
esp_err_t pcf8575_readOnePin(pcf8575_t *pcf8575, uint16_t pin, bool *state){
    if(pin > 15) return ESP_ERR_INVALID_ARG;

    uint16_t data = pcf8575->io_state ;
    *state = data & BV(pin);
    return ESP_OK;
}

// Hàm xử lý ngắt
void IRAM_ATTR interrupe_handler(void *arg){
    // Writing function you want
}
#ifdef CONFIG_INTERRUPT_ENABLE
// Hàm cấu hình interrupt
esp_err_t pcf8575_interruptInitialize(pcf8575_t *pcf8575){
    // Cấu hình GPIO làm đầu vào với chế độ pull-pu là HIGH
#ifdef CONFIG_PCF8575_INTERRUPT_PIN
    pcf8575->gpio_interrupt = CONFIG_PCF8575_INTERRUPT_PIN;
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_NEGEDGE ; // Kích hoạt interrupt khi GPIO thay đổi
    io_conf.pin_bit_mask = (1ULL << pcf8575->gpio_interrupt);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
    
    // Hàm xử lý khi interrupt xảy ra
    gpio_isr_handler_add(pcf8575->gpio_interrupt,interrupe_handler,NULL);
#endif
    return ESP_OK;
}
#else
// Hàm vô hiệu hóa interrupt
esp_err_t pcf8575_interruptDeinitialize(pcf8575_t *pcf8575){    
#ifdef CONFIG_PCF8575_INTERRUPT_PIN
    int pcf8575->gpio_interrupt = CONFIG_PCF8575_INTERRUPT_PIN;
    gpio_intr_disable(pcf8575->gpio_interrupt);
#endif
}
#endif

