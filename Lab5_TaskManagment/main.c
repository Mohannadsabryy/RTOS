/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* MCAL includes. */
#include "gpio.h"
#include "uart0.h"

#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 369

void Delay_MS(unsigned long long n)
{
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}

/* The HW setup function */
static void prvSetupHardware( void );

/*Tasks Function*/
void vPeriodicTask(void *pvParameters);

#define GREEN_LED 0
#define RED_LED   1

/* New type to hold task information */
typedef struct
{
    const uint8 * pcTextForTask;
    uint8_t ucLed;
} TaskInformation;

TaskInformation task1 = { /* pcTextForTask */  "Green LED Task is running\r\n",
                          /* ucLed */          GREEN_LED
                        };

TaskInformation task2 = { /* pcTextForTask */  "Red LED Task is running\r\n",
                          /* ucLed */          RED_LED
                        };

int main(void)
{
    /* Setup Hardware */
    prvSetupHardware();

    /* Creation of Tasks */
    xTaskCreate(vPeriodicTask, "Task1",256,(void*)&task1, 1, NULL);
    xTaskCreate(vPeriodicTask, "Task2",256,(void*)&task2, 1, NULL);

    /* Start Scheduler */
    vTaskStartScheduler();
}

/* The HW setup function */
static void prvSetupHardware( void ){
    GPIO_BuiltinButtonsLedsInit();
    UART0_Init();
}

/*Tasks Function*/
void vPeriodicTask(void *pvParameters){

    for(;;){
        //here we send the address of the first character in the string.
        UART0_SendString(((TaskInformation *)pvParameters)->pcTextForTask);
        if(((TaskInformation *)pvParameters)->ucLed==GREEN_LED){
            GPIO_GreenLedToggle();
        }
        else{
            GPIO_RedLedToggle();
        }
        Delay_MS(1000);
    }
}
/*-----------------------------------------------------------*/
