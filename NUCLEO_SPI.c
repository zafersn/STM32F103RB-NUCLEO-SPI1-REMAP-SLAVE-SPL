

/*****************************************************************************/
/*                           INCLUDES	                                     */
/*****************************************************************************/



#include "NUCLEO_SPI.h"
/*****************************************************************************/
/*                           GLOBALS                                         */
/*****************************************************************************/


SPI_InitTypeDef SPI_InitStructure;

/*****************************************************************************/
/*                           FUNCTIONS                                       */
/*****************************************************************************/

/**
 * @brief  Initializes the SPI
 * @param  None
 * @retval None
 */
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);

void InitSPI1(void)
{

    RCC_Configuration();
    GPIO_Configuration();
    NVIC_Configuration();

   /* SPI_SLAVE configuration -------------------------------------------------*/

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;

    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                                                                         /* NOTE: Clock polarity low */

    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                                                                       /* NOTE: Clock phase 2 edges */

    SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;                                                                          /* NOTE: Chip select is controlled by software */

    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;

    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                                                                 /* NOTE: MSB First */

    SPI_InitStructure.SPI_CRCPolynomial = 7;                                                                           /* NOTE: Default CRC calculation polynomial value */

    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);

/* Enable SPI_SLAVE */

    SPI_Cmd(SPI1, ENABLE);


}
void RCC_Configuration(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
}

void GPIO_Configuration(void)
{

  /* Configure SPI_SLAVE pins: SCK and MOSI ---------------------------------*/
  /* Configure SCK and MOSI pins as Input Floating */

      GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
      GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);

      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5; //sck  /mosi
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
      GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void NVIC_Configuration(void)
{
        NVIC_InitTypeDef NVIC_InitStructure;

        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	    NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        NVIC_Init(&NVIC_InitStructure);

}
/*****************************************************************************/
/*                           END OF FILE	       		                     */
/*****************************************************************************/