
#include "RTOS_text.h"

#include "led.h"
#include "usart.h"

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define LED1_TASK_PRIO		2
//�����ջ��С	
#define LED1_STK_SIZE 		50  
//������
TaskHandle_t LED1Task_Handler;  
//������
void led1_task(void *pvParameters);

//�������ȼ�
#define LED2_TASK_PRIO		3
//�����ջ��С	
#define LED2_STK_SIZE 		50  
//������
TaskHandle_t LED2Task_Handler;
//������
void led2_task(void *pvParameters);


void FreeRTOS_start_task(void)
{
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
      
    //����LED1����
    xTaskCreate((TaskFunction_t )led1_task,     
                (const char*    )"led1_task",   
                (uint16_t       )LED1_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED1_TASK_PRIO,
                (TaskHandle_t*  )&LED1Task_Handler); 
				
	//����LED2����
    xTaskCreate((TaskFunction_t )led2_task,     
                (const char*    )"led2_task",   
                (uint16_t       )LED2_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED2_TASK_PRIO,
                (TaskHandle_t*  )&LED2Task_Handler); 
				
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
} 

//LED1������
/*! ����PB5�ܽű�ʹ�ã�����LED2�ò���!*/
void led1_task(void *pvParameters)
{
    while(1)
    {
//				GPIO_ResetBits(LED1_PORT,LED1_PIN);
				printf("LED1-->0\r\n");
        vTaskDelay(200);
//				GPIO_SetBits(LED1_PORT,LED1_PIN);
				printf("LED1-->1\r\n");
        vTaskDelay(800);
    }
}

//LED2������
void led2_task(void *pvParameters)
{
    while(1)
    {
				GPIO_ResetBits(LED2_PORT,LED2_PIN);
				printf("LED2-->0\r\n");
        vTaskDelay(800);
				GPIO_SetBits(LED2_PORT,LED2_PIN);
				printf("LED2-->1\r\n");
        vTaskDelay(200);
    }
}


