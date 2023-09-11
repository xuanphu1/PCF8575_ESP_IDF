set(srcs PCF.c)
set(pre_req log )
set(include_dirs ".")
idf_component_register(SRCS ${app_src}
                    INCLUDE_DIRS ${include_dirs}
                    REQUIRES ${pre_req})
