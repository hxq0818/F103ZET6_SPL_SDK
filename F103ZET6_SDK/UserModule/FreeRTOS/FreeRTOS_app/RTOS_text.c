
#include "RTOS_text.h"

#include "led.h"
#include "usart.h"

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define LED1_TASK_PRIO		2
//任务堆栈大小	
#define LED1_STK_SIZE 		50  
//任务句柄
TaskHandle_t LED1Task_Handler;  
//任务函数
void led1_task(void *pvParameters);

//任务优先级
#define LED2_TASK_PRIO		3
//任务堆栈大小	
#define LED2_STK_SIZE 		50  
//任务句柄
TaskHandle_t LED2Task_Handler;
//任务函数
void led2_task(void *pvParameters);


void FreeRTOS_start_task(void)
{
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
      
    //创建LED1任务
    xTaskCreate((TaskFunction_t )led1_task,     
                (const char*    )"led1_task",   
                (uint16_t       )LED1_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED1_TASK_PRIO,
                (TaskHandle_t*  )&LED1Task_Handler); 
				
	//创建LED2任务
    xTaskCreate((TaskFunction_t )led2_task,     
                (const char*    )"led2_task",   
                (uint16_t       )LED2_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED2_TASK_PRIO,
                (TaskHandle_t*  )&LED2Task_Handler); 
				
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
} 

//LED1任务函数
void led1_task(void *pvParameters)
{
    while(1)
    {
				LED1 = 1;
				GPIO_ResetBits(LED2_PORT,LED2_PIN);
				printf("LED2-->0\r\n");
        vTaskDelay(800);
				LED1 = 0;
				GPIO_SetBits(LED2_PORT,LED2_PIN);
				printf("LED2-->1\r\n");
        vTaskDelay(200);
    }
}

//LED2任务函数
/*! 由于PB5管脚被使用，所以LED2用不了!*/
void led2_task(void *pvParameters)
{
    while(1)
    {
//				LED2 = 1;
//				GPIO_ResetBits(LED1_PORT,LED1_PIN);
				printf("LED1-->0\r\n");
        vTaskDelay(200);
//				LED1 = 1;
//				GPIO_SetBits(LED1_PORT,LED1_PIN);
				printf("LED1-->1\r\n");
        vTaskDelay(800);
    }
}


