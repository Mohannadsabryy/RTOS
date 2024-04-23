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


const uint8 *pcNameTask1="Task1 is running\r\n";
const uint8 *pcNameTask2="Task2 is running\r\n";


int main(void)
{
    /* Setup Hardware */
    prvSetupHardware();

    /* Creation of Tasks */
    xTaskCreate(vPeriodicTask, "Task1",256,(void *)pcNameTask1, 1, NULL);
    xTaskCreate(vPeriodicTask, "Task2",256,(void *)pcNameTask2, 1, NULL);

    /* Start Scheduler */
    vTaskStartScheduler();
}

/* The HW setup function */
static void prvSetupHardware( void ){
    UART0_Init();
}

/*Tasks Function*/
void vPeriodicTask(void *pvParameters){

    for(;;){
        UART0_SendString((uint8 *)pvParameters);
        Delay_MS(1000);
    }
}
/*-----------------------------------------------------------*/
