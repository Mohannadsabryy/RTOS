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
void vPeriodicTask1(void *pvParameters);

/*Task2 Function*/
void vPeriodicTask2(void *pvParameters);


int main(void)
{
    /* Setup Hardware */
    prvSetupHardware();

    /* Creation of Tasks */
    xTaskCreate(vPeriodicTask1, "Task1",256, NULL, 1, NULL);
    xTaskCreate(vPeriodicTask2, "Task2",256, NULL, 1, NULL);

    /* Start Scheduler */
    vTaskStartScheduler();
}

/* The HW setup function */
static void prvSetupHardware( void ){
    UART0_Init();
}

/*Task1 Function*/
void vPeriodicTask1(void *pvParameters){

    for(;;){
        UART0_SendString("Task 1 is running\r\n");
        Delay_MS(1000);
    }
}

/*Task2 Function*/
void vPeriodicTask2(void *pvParameters){

    for(;;){
        Delay_MS(1000);
        UART0_SendString("Task 2 is running\r\n");
    }

}


/*-----------------------------------------------------------*/
