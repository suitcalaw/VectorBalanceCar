/* FreeRTOS Header file */
#include "FreeRTOS.h"
#include "task.h"
#include "misc.h"

static TaskHandle_t AppTaskCreate_Handle = NULL;        /* the handle of  AppTaskCreate*/

static void AppTaskCreate(void);                        /* Create task's task */

int main(void)
{
    BaseType_t xReturn = pdPASS;                        /* the return value of create task */

    SystemInit();                                       /* System Initialzation */

    NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
    /* Create AppTaskCreate task */
    xReturn = xTaskCreate(
              (TaskFunction_t) AppTaskCreate,           /* task fun */
              (const char*) "AppTaskCreate",            /* task name */
              (uint16_t) 512,                           /* task stack depth */
              (void*) NULL,                             /* task para */
              (UBaseType_t) 1,                          /* task  priorty */
              (TaskHandle_t*) &AppTaskCreate_Handle);   /* task handle */

    if (pdPASS == xReturn)
        vTaskStartScheduler();                          /* run os */
    else
        return -1;

    while (1);
}


static void AppTaskCreate(void)
{
    BaseType_t xReturn = pdPASS; /* the return of new create task */

    taskENTER_CRITICAL(); //enter critical area



    vTaskDelete(AppTaskCreate_Handle); //dele AppTaskCreate task

    taskEXIT_CRITICAL(); //sign out critical area
}
/********************************END OF FILE****************************/
