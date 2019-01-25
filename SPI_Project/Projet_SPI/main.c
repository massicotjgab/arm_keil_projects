/*-------------------------------------------------------*/
/*----------------------Projet SPI-----------------------*/
/*-------------------------------------------------------*/

/*
***********************************************************
*
*
*	@FILE					:	Project_SPI : main.c
*	@AUTHOR				:	MASSICOT Jean-Gabriel
*	@BOARD				:	STM32F407
*	@BRIEF				: SPI manipulation and configuration to use the embedded accelerometer
*	@EVOLUTION		:	In Progress 10%
*	@FIRST COMMIT	:	13/12/2018
*	@LAST COMMIT	:	25/01/2019 13h41
*	@COMMIT INFO	:	
*	@LICENCE			:	BSD-3Clause
*
***********************************************************
*/

/*-------------------------------------------------------*/
/*------------------BSD-3Clause license------------------*/
/*-------------------------------------------------------*/
/*
***********************************************************
Copyright (c) 2018-2019, MASSICOT Jean-Gabriel, All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
	this list of conditions and the following disclaimer.
	
* Redistributions in binary form must reproduce the above copyright notice,
	this list of conditions and the following disclaimer in the documentation
	and/or other materials provided with the distribution.
	
* Neither the name of the copyright holder nor the names of its contributors
	may be used to endorse or promote products derived from this software without
	specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************
*/

/*-------- INCLUDES --------*/
#include "stm32f4xx_hal.h"


void init_config(void);
SPI_HandleTypeDef hspi;
unsigned char spiSendData[2];
unsigned char spiReceiveData [6];


/*===== MAIN =====*/
int main (void){
	
	init_config();
	
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET);
	spiSendData[0]=0x20;
	spiSendData[1]=0x17;
	HAL_SPI_Transmit(&hspi,spiSendData,2,50);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET);
	spiSendData[0]=0x20|0x80;
	HAL_SPI_Transmit(&hspi,spiSendData,1,50);
	HAL_SPI_Receive(&hspi,spiReceiveData,1,50);
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET);

	while (1){
	}

}/*===== FIN MAIN =====*/


/*===== CONFIGURATION =====*/
void init_config (void){

	
	
	/*----- Config MISO/MOSI -----*/
	
	GPIO_InitTypeDef SPI_pins;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	SPI_pins.Pin								=		GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	SPI_pins.Mode								=		GPIO_MODE_AF_PP;
	SPI_pins.Alternate					=		GPIO_AF5_SPI1;
	SPI_pins.Speed							=		GPIO_SPEED_FREQ_VERY_HIGH;
	
	HAL_GPIO_Init(GPIOA, &SPI_pins);
	
	/*----- FIN Config MISO/MOSI -----*/


	
	/*----- Config CS -----*/
	
	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitTypeDef SPI_CS_pin;
		
	SPI_CS_pin.Pin							=		GPIO_PIN_3;
	SPI_CS_pin.Mode							=		GPIO_MODE_OUTPUT_PP;
		
	HAL_GPIO_Init(GPIOE, &SPI_CS_pin);
	
	/*----- FIN Config CS -----*/



	/*----- Config LED -----*/
	
	__HAL_RCC_GPIOD_CLK_ENABLE();
	GPIO_InitTypeDef LED_pin;

	LED_pin.Pin									=		GPIO_PIN_12 | GPIO_PIN_13;
	LED_pin.Mode								=		GPIO_MODE_OUTPUT_PP;

	HAL_GPIO_Init(GPIOE, &LED_pin);
	
	/*----- FIN Config LED -----*/


	
	/*----- Config SPI -----*/
	
	__HAL_RCC_SPI1_CLK_ENABLE();
	hspi.Instance								=		SPI1;
	hspi.Init.Mode							=		SPI_MODE_MASTER;
	hspi.Init.Direction					=		SPI_DIRECTION_2LINES;
	hspi.Init.CLKPolarity				=		SPI_POLARITY_HIGH; //SPI_POLARITY_LOW  ?
	hspi.Init.CLKPhase					=		SPI_PHASE_1EDGE;
	hspi.Init.NSS								=		SPI_NSS_SOFT;
	hspi.Init.BaudRatePrescaler	=		SPI_BAUDRATEPRESCALER_16;
	hspi.Init.CRCCalculation		=		SPI_CRCCALCULATION_DISABLE;
	hspi.Init.DataSize					=		SPI_DATASIZE_8BIT;
	hspi.Init.FirstBit					=		SPI_FIRSTBIT_MSB;
	hspi.Init.TIMode						=		SPI_TIMODE_DISABLE;
	
	HAL_SPI_Init(&hspi);
	
	/*----- FIN Config SPI -----*/
	

}/*===== FIN CONFIGURATION =====*/





/*-------------------------------------------------------*/
/*------------------- FIN DU PROGRAMME ------------------*/
/*-------------------------------------------------------*/