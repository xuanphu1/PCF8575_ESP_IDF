#include "../../component/PCF8575_Sparc_lab/PCF.h"

pcf8575_t pcf8575;
void app_main()
{
    pcf8575_initialize(&pcf8575,I2C_NUM_0, GPIO_NUM_22,GPIO_NUM_21);
}
