set(app_src PCF.c pcf8575/pcf8575.c i2cdev/i2cdev.c)
set(pre_req log driver)
idf_component_register(SRCS ${app_src}
                    INCLUDE_DIRS "."
                    REQUIRES ${pre_req})
                    