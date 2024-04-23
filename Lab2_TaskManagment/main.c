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

/*Task1 Function*/
void vPeriodicGreenLedTask(void *pvParameters);

/*Task2 Function*/
void vPeriodicRedLedTask(void *pvParameters);


int main(void)
{
    /* Setup Hardware */
    prvSetupHardware();

    /* Creation of Tasks */
    xTaskCreate(vPeriodicGreenLedTask, "GreenTask",256, NULL, 1, NULL);
    xTaskCreate(vPeriodicRedLedTask, "RedTask",256, NULL, 1, NULL);

    /* Start Scheduler */
    vTaskStartScheduler();
}

/* The HW setup function */
static void prvSetupHardware( void ){
    GPIO_BuiltinButtonsLedsInit();
}

/*Task1 Function*/
void vPeriodicGreenLedTask(void *pvParameters){

    for(;;){
        GPIO_GreenLedToggle();
        Delay_MS(1000);
    }
}

/*Task2 Function*/
void vPeriodicRedLedTask(void *pvParameters){

    for(;;){
        Delay_MS(1000);
        GPIO_RedLedToggle();
    }

}


/*-----------------------------------------------------------*/
