/*
 * uart.c
 *
 *  Created on: Jun 23, 2023
 *      Author: KIMMINJI
 */

#include "uart.h"
#include "qbuffer.h"



typedef struct
{
  uint32_t baudrate;

  uint32_t databit;              /*!< Specifies the number of data bits transmitted or received in a frame.
                                         This parameter can be a value of @ref UARTEx_Word_Length. */

  uint32_t stopbit;                /*!< Specifies the number of stop bits transmitted.
                                         This parameter can be a value of @ref UART_Stop_Bits. */

  uint32_t parity;

  uint32_t flowCtl;               /*!< Specifies whether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref UART_Hardware_Flow_Control. */
} uart_tbl_t;


uart_tbl_t uart_tbl[UART_MAX_CH] =
      {
          {19200, UART_WORDLENGTH_8B, UART_STOPBITS_1, UART_PARITY_NONE, UART_HWCONTROL_NONE},
      };


static bool is_open[UART_MAX_CH];

static qbuffer_t qbuffer[UART_MAX_CH];
static uint8_t rx_buf[256];
static uint8_t rx_dma_buf[256];

extern uint8_t RxData[256];

bool available_flag = false;

uint8_t rx_buffer[256];
uint16_t rx_buffer_index = 0;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;





bool uartInit(void)
{
  for (int i=0; i<UART_MAX_CH; i++)
    {
      is_open[i] = false;
    }
  return true;
}

bool uartOpen(uint8_t ch)
{
  bool ret = false;


  switch(ch)
  {
    case _DEF_UART1:


      huart1.Instance                    = USART1;
      huart1.Init.Mode                   = UART_MODE_TX_RX;
      huart1.Init.OverSampling           = UART_OVERSAMPLING_16;
      huart1.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
      huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

      for (int i = 0; i<UART_MAX_CH; i++)
        {
          huart1.Init.BaudRate               = uart_tbl[i].baudrate;
          huart1.Init.WordLength             = uart_tbl[i].databit;
          huart1.Init.StopBits               = uart_tbl[i].stopbit;
          huart1.Init.Parity                 = uart_tbl[i].parity;
          huart1.Init.HwFlowCtl              = uart_tbl[i].flowCtl;
        }

      qbufferCreate(&qbuffer[ch], &rx_buf[0], 256);

      HAL_UART_DeInit(&huart1);

      __HAL_RCC_DMA1_CLK_ENABLE();
      HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
      HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

      if (HAL_UART_Init(&huart1) != HAL_OK)
      {
        ret = false;
      }
      else
      {
        ret = true;
        is_open[ch] = true;

         /*DMA*/
        if(HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t *)&rx_dma_buf[0], 256) != HAL_OK)
          {
            ret = false;
          }
        __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);

        qbuffer[ch].in = 0;
        qbuffer[ch].out = 0;
      }
      break;
  }

  return ret;
}

uint32_t uartAvailable(uint8_t ch)
{
  uint32_t ret = 0;
  if(available_flag)
  {
    switch(ch)
    {
      case _DEF_UART1:
          ret= qbufferAvailable(&qbuffer[_DEF_UART1]);
          if(ret == 0)
          {
            available_flag = false;
          }
        break;
    }
  }
  return ret;
}

uint8_t uartRead(uint8_t ch)
{
  uint8_t ret = 0;

  switch(ch)
  {
    case _DEF_UART1:
      //sizeof(rx_buf)+1
      qbufferRead(&qbuffer[_DEF_UART1], RxData, 256);
      break;
  }

  return ret;
}

uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length)
{
  uint32_t ret = 0;
  HAL_StatusTypeDef status;

  switch(ch)
  {
    case _DEF_UART1:
      status = HAL_UART_Transmit(&huart1, p_data, length, 100);
      if (status == HAL_OK)
      {
        ret = length;
      }
      break;
  }
  return ret;
}

uint32_t uartPrintf(uint8_t ch, char *fmt, ...)
{
  char buf[256];
  va_list args;
  int len;
  uint32_t ret;

  va_start(args, fmt);

  len = vsnprintf(buf, 256, fmt, args);

  ret = uartWrite(ch, (uint8_t *)buf, len);

  va_end(args);

  return ret;
}


/*
 * uart_tbl_mem_tag
 * 0 : baudrate
 * 1 : databit
 * 2 : stopbit
 * 3 : parity
 * 4 : flowCtl
 */
bool set_uart_tbl(uint16_t* Holding_Registers_Database)
{
  bool ret = true;

    for (int i=0; i<UART_MAX_CH; i++)
    {
      is_open[i] = false;

      for (int j=0; j<5; j++)
      {
        int uart_tbl_mem_tag = j;

        switch (uart_tbl_mem_tag)
        {
          case 0:
            uart_tbl[i].baudrate = (uint32_t)Holding_Registers_Database[uart_tbl_mem_tag+1]<<8 | (uint32_t)Holding_Registers_Database[uart_tbl_mem_tag+2]<<0;
            break;

          case 1:
            if(Holding_Registers_Database[uart_tbl_mem_tag+2] == 0x08)
            {
              uart_tbl[i].databit = (uint32_t)UART_WORDLENGTH_8B;
            }
            break;

          case 2:
            if(Holding_Registers_Database[uart_tbl_mem_tag+2] == 0x01)
            {
              uart_tbl[i].stopbit = (uint32_t)UART_STOPBITS_1;
            }
            break;

          case 3:
            if(Holding_Registers_Database[uart_tbl_mem_tag+2] == 0x00)
            {
              uart_tbl[i].parity = (uint32_t)UART_PARITY_NONE;
            }
            break;

          case 4:
            if((uint32_t)Holding_Registers_Database[uart_tbl_mem_tag+2] == 0x00)
            {
              uart_tbl[i].flowCtl = (uint32_t)UART_HWCONTROL_NONE;
            }
            break;

          default:
            ret = false;
            break;
        }
      }
    }
    return ret;
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
    {

    }
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  uint16_t availableSpace = 256 - qbuffer[_DEF_UART1].in;

  bool ret = true;

  if (huart->Instance == USART1) //case _DEF_UART1
  {

    qbuffer[_DEF_UART1].in = 0;
    qbuffer[_DEF_UART1].out = 0;

    if (Size > availableSpace)
    {
           // 처리할 수 없는 크기의 데이터가 수신됨
           // 예외 처리 또는 에러 처리를 수행
      return;
    }
    qbuffer[_DEF_UART1].in = qbuffer[_DEF_UART1].len - hdma_usart1_rx.Instance->CNDTR;

    for(int i=0; i<Size; i++)
    {
      rx_buf[i] = rx_dma_buf[i];
    }
    available_flag = true;

    HAL_UART_DeInit(&huart1);
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
      ret = false;
    }
    else
    {
      ret = true;
      is_open[_DEF_UART1] = true;

      /*DMA*/
      if(HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t *)&rx_dma_buf[0], 256) != HAL_OK)
      {
        ret = false;
      }
      __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);


      }

  }

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#if 0
  if (huart->Instance == USART1)
  {
    qbufferWrite(&qbuffer[_DEF_UART1], &rx_data[_DEF_UART1], 1);

    HAL_UART_Receive_IT(&huart1, (uint8_t *)&rx_data[_DEF_UART1], 1);
  }
#endif
}




void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA1_Channel3;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;

    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}
