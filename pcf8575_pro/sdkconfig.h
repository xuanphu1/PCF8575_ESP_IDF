#define LLL_ADDRESS 0x40    // A[2]A[1]A[0] = 000  
#define LLH_ADDRESS 0X42    // A[2]A[1]A[0] = 001   
#define LHL_ADDRESS 0X44    // A[2]A[1]A[0] = 010 
#define LHH_ADDRESS 0X46    // A[2]A[1]A[0] = 011 
#define HLL_ADDRESS 0X48    // A[2]A[1]A[0] = 100 
#define HLH_ADDRESS 0X4A    // A[2]A[1]A[0] = 101 
#define HHL_ADDRESS 0x4C    // A[2]A[1]A[0] = 110 
#define HHH_ADDRESS 0x4E    // A[2]A[1]A[0] = 111 

#define CONFIG_PCF8575_INTERRUPT_PIN GPIO_NUM_5
#define CONFIG_INTERRUPT_ENABLE 0