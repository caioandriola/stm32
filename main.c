/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Utility.h"
#include "LCD_Blio.h"
#include "stdio.h"
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void atraso(int tempo);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void aula_20_08(){
	Utility_Init();



	GPIO_Clock_Enable(GPIOA); //liga clock
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);//PA6 como saída


	GPIO_Clock_Enable(GPIOE);
	GPIO_Pin_Mode(GPIOA, PIN_3, INPUT);
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);

	while(1){
		if(!GPIO_Read_Pin(GPIOE, PIN_3)){
			GPIO_Toggle_Pin(GPIOA,PIN_6); //liga led
			Delay_ms(100); //delay de 1 segundo
		}
		else{
			GPIO_Write_Pin(GPIOA,PIN_6,HIGH);
		}
		/*GPIO_Write_Pin(GPIOA,PIN_6,HIGH); //desliga led
		Delay_ms(1000); //delay	de 1 segundo*/

	}
}
void aula_27_08(){
	Utility_Init();

	GPIO_Clock_Enable(GPIOA); //liga clock
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);//PA6 como saída


	GPIO_Clock_Enable(GPIOE);
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT);
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);

	int t=5000;

	while(1){

		if(!GPIO_Read_Pin(GPIOE,PIN_4)){
			if(t>10000){
				t=10000;
			}
			else if(t+100<=10000){
				t+=100;
			}
		}
		else if(!GPIO_Read_Pin(GPIOE,PIN_3)){
			if(t<0){
				t=0;
			}
			else if(t-100>=0){
				t-=100;
			}
		}

		GPIO_Write_Pin(GPIOA,PIN_6,HIGH);
		Delay_us(t);

		GPIO_Write_Pin(GPIOA,PIN_6,LOW);
		Delay_us(10000-t);

	}
}

void aula_01_09(){
	Utility_Init();

	GPIO_Clock_Enable(GPIOA); //liga clock
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);//PA6 como saída

	GPIO_Clock_Enable(GPIOE);
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);

	int delay=1000;
	int bin =1;
	while(1){

		if(bin==1){
			delay=100;

			GPIO_Toggle_Pin(GPIOA,PIN_6);
			Delay_ms(delay);

			if(!GPIO_Read_Pin(GPIOE,PIN_3)) bin--;
		}
		else if(bin==0){
			delay=1000;

			GPIO_Toggle_Pin(GPIOA,PIN_6);
			Delay_ms(delay);

			if(!GPIO_Read_Pin(GPIOE,PIN_3)) bin++;

		}

	}
}

void Q14_lista(){
	/*Utility_Init();

	GPIO_Clock_Enable(GPIOC);

	GPIO_Pin_Mode(GPIOC, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOC, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOC, PIN_2, OUTPUT);

	GPIO_Write_Pin(GPIOC,PIN_0,LOW);
	GPIO_Write_Pin(GPIOC,PIN_1,HIGH);

	int sentido=0,tempo=0,incremento=5;

	while(1){

		if (tempo==50 && sentido==0){
			incremento=-5;
			tempo+=incremento;
		}
		else if (tempo==0 && sentido==0){
			incremento=5;
			sentido=1;
			GPIO_Write_Pin(GPIOC,PIN_0,LOW);
			GPIO_Write_Pin(GPIOC,PIN_1,HIGH);
			tempo+=incremento;
		}
		else if (tempo==50 && sentido==1){
			incremento=-5;
			tempo+=incremento;
		}
		else if (tempo==0 && sentido==1){
			incremento=5;
			sentido=0;
			GPIO_Write_Pin(GPIOC,PIN_0,HIGH);
			GPIO_Write_Pin(GPIOC,PIN_1,LOW);
			tempo+=incremento;
		}

		GPIO_Write_Pin(GPIOC,PIN_2,HIGH);
		Delay_us(20);
		GPIO_Write_Pin(GPIOC,PIN_2,LOW);
		Delay_us(30);

		tempo+=incremento;

	}*/

		int duty;
		Utility_Init();
		GPIO_Clock_Enable(GPIOD);

		//PDO -> TIM4_CH1 -> PWM
		GPIO_Pin_Mode(GPIOD, PIN_12, ALTERNATE);
		GPIO_Alternate_Function(GPIOD,PIN_12,2);

		//PD1 -> INA1
		GPIO_Pin_Mode(GPIOD,PIN_1,OUTPUT);
		GPIO_Output_Type(GPIOD, PIN_1, PUSH_PULL);

		//PD2 -> INB1

		GPIO_Pin_Mode(GPIOD,PIN_2,OUTPUT);
		GPIO_Output_Type(GPIOD,PIN_2,PUSH_PULL);

		 /* Configura o TIM4 */
		RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

		TIM4->PSC = 83;
		TIM4->ARR = 499;
		    /* TIM4_CH1 em PWM Mode 1 */
		TIM4->CCMR1 &= ~(0b111 << 4);
		TIM4->CCMR1 |= (0b110 << 4);
		    /* Habilita preload do CCR1 */
		TIM4->CCMR1 |= TIM_CCMR1_OC1PE;
		    /* Habilita saída do canal 1 */
		TIM4->CCER |= TIM_CCER_CC1E;
		    /* Duty inicial = 0% */
		TIM4->CCR1 = 0;
		/* Atualiza os registradores */
		TIM4->EGR = TIM_EGR_UG;
		/* Habilita o timer */
		TIM4->CR1 |= TIM_CR1_CEN;

		while(1){

			GPIO_Write_Pin(GPIOD, PIN_1, LOW);
			GPIO_Write_Pin(GPIOD, PIN_2, HIGH);

			for(duty = 0; duty <= 499; duty++){

				TIM4->CCR1 = duty;
				Delay_ms(10);
			}

			for(duty = 499; duty >= 0; duty--){
				TIM4->CCR1 = duty;
				Delay_ms(10);
			}

			GPIO_Write_Pin(GPIOD,PIN_1,HIGH);
			GPIO_Write_Pin(GPIOD,PIN_2,LOW);

			for(duty = 0; duty <= 499; duty++){
				TIM4->CCR1 = duty;
				Delay_ms(10);
			}

			for(duty = 499; duty >= 0; duty--){
				TIM4->CCR1 = duty;
				Delay_ms(10);
			}
		}



}


void Q15_lista(){
	Utility_Init();

	GPIO_Clock_Enable(GPIOA);
	GPIO_Clock_Enable(GPIOE);



	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);

	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);


	while(1){
		if (!GPIO_Read_Pin(GPIOE,PIN_3)){
			if(GPIO_Read_Pin(GPIOA,PIN_6)){
				GPIO_Write_Pin(GPIOA,PIN_6,LOW);
					Delay_ms(500);

			}

			else if(!GPIO_Read_Pin(GPIOA,PIN_6)){
				GPIO_Write_Pin(GPIOA,PIN_6,HIGH);
					Delay_ms(500);
			}

		}
	}
}


void Q16_lista(){
	Utility_Init();

	GPIO_Clock_Enable(GPIOA);
	GPIO_Clock_Enable(GPIOE);



	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);

	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT);
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);


	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

	int ligado = 0,bloqueado=0;
	GPIO_Write_Pin(GPIOA, PIN_6,HIGH);

	while(1){
		if (GPIO_Read_Pin(GPIOE,PIN_4)){
			bloqueado=0;
		}
		if(!GPIO_Read_Pin(GPIOE,PIN_4) && GPIO_Read_Pin(GPIOE,PIN_3) && !bloqueado){
			Delay_ms(20);
			if (!GPIO_Read_Pin(GPIOE,PIN_4) && GPIO_Read_Pin(GPIOE,PIN_3) && !bloqueado){
				int contador = 0;
				while(contador<100 && !GPIO_Read_Pin(GPIOE,PIN_4) ) {
					if(!GPIO_Read_Pin(GPIOE,PIN_3)){
						Delay_ms(20);
						if (!GPIO_Read_Pin(GPIOE,PIN_3)){
							Delay_ms(10);
							ligado=1;
							GPIO_Write_Pin(GPIOA, PIN_6,LOW);
							break;
						}
					}
					Delay_ms(10);
					contador ++;
				}
				bloqueado=1;
			}
		}
		if (ligado && GPIO_Read_Pin(GPIOE,PIN_4) && GPIO_Read_Pin(GPIOE,PIN_3)){
			GPIO_Write_Pin(GPIOA, PIN_6,HIGH);
			ligado=0;
		}
	}
}


void aula_8_10(){
	Utility_Init();
	DAC_Init(DAC_CHANNEL1);
	const uint16_t array[200] = {
	    /* 000-009 */  2048, 2112, 2176, 2240, 2304, 2368, 2431, 2494, 2557, 2619,
	    /* 010-019 */  2680, 2741, 2801, 2861, 2919, 2977, 3034, 3090, 3145, 3198,
	    /* 020-029 */  3251, 3302, 3353, 3402, 3449, 3495, 3540, 3583, 3625, 3665,
	    /* 030-039 */  3704, 3741, 3776, 3810, 3842, 3872, 3900, 3927, 3951, 3974,
	    /* 040-049 */  3995, 4014, 4031, 4046, 4059, 4070, 4079, 4086, 4091, 4094,
	    /* 050-059 */  4095, 4094, 4091, 4086, 4079, 4070, 4059, 4046, 4031, 4014,
	    /* 060-069 */  3995, 3974, 3951, 3927, 3900, 3872, 3842, 3810, 3776, 3741,
	    /* 070-079 */  3704, 3665, 3625, 3583, 3540, 3495, 3449, 3402, 3353, 3302,
	    /* 080-089 */  3251, 3198, 3145, 3090, 3034, 2977, 2919, 2861, 2801, 2741,
	    /* 090-099 */  2680, 2619, 2557, 2494, 2431, 2368, 2304, 2240, 2176, 2112,
	    /* 100-109 */  2048, 1983, 1919, 1855, 1791, 1727, 1664, 1601, 1538, 1476,
	    /* 110-119 */  1415, 1354, 1294, 1234, 1176, 1118, 1061, 1005,  950,  897,
	    /* 120-129 */   844,  793,  742,  693,  646,  600,  555,  512,  470,  430,
	    /* 130-139 */   391,  354,  319,  285,  253,  223,  195,  168,  144,  121,
	    /* 140-149 */   100,   81,   64,   49,   36,   25,   16,    9,    4,    1,
	    /* 150-159 */     0,    1,    4,    9,   16,   25,   36,   49,   64,   81,
	    /* 160-169 */   100,  121,  144,  168,  195,  223,  253,  285,  319,  354,
	    /* 170-179 */   391,  430,  470,  512,  555,  600,  646,  693,  742,  793,
	    /* 180-189 */   844,  897,  950, 1005, 1061, 1118, 1176, 1234, 1294, 1354,
	    /* 190-199 */  1415, 1476, 1538, 1601, 1664, 1727, 1791, 1855, 1919, 1983
	};

	//DAC_SETVALUE(DAC_CHANNEL1, 1500, DAC_RES_12BITS);

	while(1){
		for (int i=0; i<200;i++){
			DAC_SetValue(DAC_CHANNEL1, array[i], DAC_RES_12BITS);
			Delay_ms(10);
		}
	}
}

void aula_15_10(){
	Utility_Init();
	USART1_Init();

	ADC_Init(ADC1,SINGLE_CHANNEL,DAC_RES_12BITS);
	ADC_SingleChannel(ADC1, ADC_IN0);

	while (1){
		uint16_t leitura = ADC_GetSingleConversion(ADC1);
		float voltagem = ((float)leitura *3.3f)/4095;

		printf("Voltagem = %.2f V\n",voltagem);
		Delay_ms(1000);
	}

}

void aula_20_10(){
	Utility_Init();
	USART1_Init();

	ADC_Init(ADC1,SINGLE_CHANNEL,DAC_RES_12BITS);
	ADC_SingleChannel(ADC1, ADC_IN0);
	GPIO_Clock_Enable(GPIOD);
	GPIO_Pin_Mode(GPIOD,PIN_6,OUTPUT);





	while(1){

		uint16_t leitura = ADC_GetSingleConversion(ADC1);
		int pulso = (((float)leitura * 2000)/4095);
		if(pulso>=2500){
			pulso=2500;
		}
		if(pulso<=500){
			pulso=500;
		}

		GPIO_Write_Pin(GPIOD,PIN_6,HIGH);
		Delay_us(pulso+500);
		GPIO_Write_Pin(GPIOD,PIN_6,LOW);
		Delay_us(20000-pulso);
	}

}

void aula_27_10(){
	Utility_Init();
	USART1_Init();

	ADC_Init(ADC1,SINGLE_CHANNEL,DAC_RES_12BITS);
	ADC_SingleChannel(ADC1, ADC_IN0);
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA,PIN_6,OUTPUT);
	int limite = 1500;

	while(1){
		uint16_t leitura = ADC_GetSingleConversion(ADC1);
		if ((int)(leitura)<limite){
			GPIO_Write_Pin(GPIOA,PIN_6,LOW);
		}
		else {
			GPIO_Write_Pin(GPIOA,PIN_6,HIGH);
		}
		Delay_ms(50);
	}

}



// Função para preencher a Lookup Table no início da execução
/*int16_t inicializa_lut(void) {
#include <math.h>
	int16_t lut_seno [100];
    for (int i = 0; i < 100; i++) {
        float angulo = (2.0f * 3.1415 * i) / 100;
        // Calcula a amplitude relativa variando de -2047 a +2047
        lut_seno[i] = (int16_t)(sinf(angulo) * 2047.0f);

    }
    return lut_seno;
}*/

/*void aula_05_11(){
	Utility_Init();
	USART1_Init();
	ADC_Init(ADC1, MULTI_CHANNEL, DAC_RES_12BITS);
	uint8_t array_de_dois [2] = {ADC_IN0, ADC_IN1};
	ADC_MultiChannel(ADC 1,2,array_de_dois);
	DAC_Init(DAC_CHANNEL1);

	ADC_Init(ADC1,SINGLE_CHANNEL,DAC_RES_12BITS);
	ADC_SingleChannel(ADC1, ADC_IN0);

	ADC_Init(ADC2,SINGLE_CHANNEL,DAC_RES_12BITS);
	ADC_SingleChannel(ADC2, ADC_IN1);

	ADC_GetMultiConversion(ADC1,2,array_de_dois);
	int16_t lut_seno [100];
    for (int i = 0; i < 100; i++) {
        float angulo = (2.0f * 3.1415 * i) / 100;
        // Calcula a amplitude relativa variando de -2047 a +2047
        lut_seno[i] = (int16_t)(sinf(angulo) * 2047.0f);

    }


	while(1){
		for (int i=0; i<100;i++){

			uint16_t leituraF = ADC_GetSingleConversion(ADC1);
			int pulso = 10+(((float)leituraF * 190)/4095);

			if(pulso>=200){
				pulso=200;
			}
			if(pulso<=10){
				pulso=10;
			}

			DAC_SetValue(DAC_CHANNEL1, lut_seno[i], DAC_RES_12BITS);
			Delay_us((1/pulso)*1000000);
		}
	}
}*/


void SysTick_Handler(void){
	  GPIOA -> ODR ^= (1<<6);
}



void aula_10_11(){
 	Utility_Init();
 	GPIO_Clock_Enable(GPIOA);
 	RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
 	GPIOA->MODER |= 1 << 12;
 	SysTick ->CTRL = 0;
 	SysTick -> LOAD = 10.5e6;
 	SysTick -> VAL = 0;
 	SysTick ->CTRL = 0b011;

 	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
 	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

 	while(1){
 		GPIO_Toggle_Pin(GPIOA, PIN_7);
 		Delay_ms(100);

 	}

 }

void aula_12_11(){
	Utility_Init();

	ADC_Init(ADC1,SINGLE_CHANNEL,DAC_RES_12BITS);
	ADC_SingleChannel(ADC1, ADC_IN0);

	GPIO_Clock_Enable(GPIOA);

	GPIO_Pin_Mode(GPIOA,PIN_6,ALTERNATE);
	GPIO_Alternate_Function(GPIOA,PIN_6,AF2);

	uint16_t leitura = 0;

	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3-> CR1 &= ~TIM_CR1_DIR;
	TIM3-> PSC = 209;
	TIM3-> ARR = 4095;
	TIM3-> CCMR2 |= TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1M_1;
	TIM3-> CCMR2 |= TIM_CCMR1_OC1PE;
	TIM3-> CCER |= TIM_CCER_CC1E;
	TIM3-> CCER |= TIM_CCER_CC1P;
	TIM3-> EGR = 1;
	TIM3-> CR1 |= TIM_CR1_CEN;

	while(1){
		leitura = ADC_GetSingleConversion(ADC1);
		TIM3 -> CCR1 = leitura;

	}
}

void lista_q1(void) {
    Utility_Init();
    DAC_Init(DAC_CHANNEL1);

    while (1) {
        for (int valor = 0; valor <= 4095; valor += 15) {
            DAC_SetValue(DAC_CHANNEL1, (uint16_t)valor, DAC_RES_12BITS);
            Delay_ms(5);
        }

        for (int valor = 4095; valor >= 0; valor -= 15) {
            DAC_SetValue(DAC_CHANNEL1, (uint16_t)valor, DAC_RES_12BITS);
            Delay_ms(5);
        }
    }
}

void lista_q2(void){
    Utility_Init();
    DAC_Init(DAC_CHANNEL2);

    float freq_hz = 200.0f;
    float vpp = 2.0f;
    float vm = 2.0f;
    float pi = 3.14f;

    uint16_t lut_seno[200];
    float vp = vpp/2.0f;

    for (int i =0;i<200;i++){
    	float tensao = vm + vp*sinf((2.0f*pi*i) / 200.0f);
    	int32_t codigo = (int32_t)roundf((tensao/3.3f)*4095.0f);


    	if (codigo<4095)codigo = 4095;
    	if (codigo<0)codigo =0;
    	lut_seno[i] = (uint16_t)codigo;

    }

    uint32_t atraso_us = (uint32_t)(5000.0f/freq_hz);

    while(1){
    	for (int i = 0;i<200;i++){
    		DAC_SetValue(DAC_CHANNEL2,lut_seno[i],DAC_RES_12BITS);
    		Delay_us(atraso_us);
    	}
    }
}
void questao_04(void) {
    Utility_Init();
    DAC_Init(DAC_CHANNEL1, AUTO_NOISE, AMP_9BITS);

    const float pi = 3.14f;
    uint16_t seno_1khz[50];

    for (int i = 0; i < 50; i++) {
        float v = 1.0f + 1.0f * sinf((2.0f * pi * i) / 50.0f);
        seno_1khz[i] = (uint16_t)roundf((v / 3.3f) * 4095.0f);
    }

    while (1) {
        for (int i = 0; i < 50; i++) {
            DAC_SetValue(DAC_CHANNEL1, seno_1khz[i], DAC_RES_12BITS);
            DAC_SWTrigger(DAC_CHANNEL1);
            Delay_us(20);
        }
    }
}
void lista_q5(void){
	Utility_Init();
	DAC_Init3(DAC_CHANNEL1,AUTO_TRIANGLE,AMP_8BITS);
	DAC_SetValue(DAC_CHANNEL1, 1000, DAC_RES_12BITS);

	DAC->CR &= ~DAC_CR_TSEL1;
	DAC->CR |= DAC_CR_TSEL1_0;

	RCC -> APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3-> CR1 &= ~TIM_CR1_DIR;
	TIM3-> PSC = 0;
	TIM3-> ARR = 132;
	TIM3-> CCMR2 |= TIM_CCMR1_OC1M_2|TIM_CCMR1_OC1M_1;
	TIM3-> CCMR2 |= TIM_CCMR1_OC1PE;
	TIM3-> CCER |= TIM_CCER_CC1E;
	TIM3-> CCER |= TIM_CCER_CC1P;
	TIM3-> EGR = 1;
	TIM3-> CR2 |= TIM_CR1_CEN;


	while(1){
		DAC_SWTrigger(DAC_CHANNEL1);
		Delay_us(3);
	}




}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  /*RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
  RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
  //GPIOA->MODER |= 0b01 << 12;
  //GPIOA->MODER |= 0b01 << 14;
  GPIOA->MODER |= 0b01 << 2;
  GPIOC->MODER |= 0b01 << 12;
  GPIOE->MODER |= 0b01 << 24;

  GPIOA->MODER |= 0b01 << 12;
  GPIOE->MODER &= ~(0b11 << 6);
  GPIOE->PUPDR |= 0b01 << 6;  //liga pull up em PE3


  GPIOA->MODER |= 0b01 << 14;
  GPIOE->MODER &= ~(0b11 << 8);
  GPIOE->PUPDR |= 0b01 << 8;  //liga pull up em PE3*/


  lista_q2();




  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
 	 /*
	  *
  GPIO_Clock_Enable(GPIOE);
  GPIO_Pin_Mode(GPIOE,PIN_3,INPUT);
  GPIO_Pin_Mode(GPIOE,PIN_4,INPUT);
  GPIO_Resistor_Enable(GPIOE,PIN_3,PULL_UP);
  GPIO_Resistor_Enable(GPIOE,PIN_4,PULL_UP);
  printf("teste\n");
  while (1)
  {
	  if(!GPIO_Read_Pin(GPIOE,PIN_3)){
		  printf("pressionei k1\n");
		  Delay_ms(1000);
	  }
	  Delay_ms(100);

	  if(!GPIO_Read_Pin(GPIOE,PIN_4)){
	  		  printf("pressionei k0\n");
	  		  Delay_ms(1000);
	  	  }
  }
	  *
	  *
	  *
	  *
	  *
	  *
	  *
	  *
	  *  GPIOA -> ODR |= 1 << 6;//PA6 nível alto
	  atraso(1000000);
	  GPIOA -> ODR |= 1 << 7;//PA7 nível alto
	  atraso(1000000);
	  GPIOA -> ODR &= ~(1 << 6);//PA6 nível baixo
	  atraso(1000000);
	  GPIOA -> ODR &= ~(1 << 7);//PA7 nível baixo
	  atraso(1000000);*/

	 /* GPIOA -> ODR |= 1 << 1;
	  atraso(20000000);
	  GPIOA -> ODR &= ~(1 << 1);
	  atraso(1000000);
	  GPIOE-> ODR |= 1 << 12;
	  atraso(20000000);
	  GPIOE -> ODR &= ~(1 << 12);
	  atraso(1000000);
	  GPIOC -> ODR |= 1 << 6;
	  atraso(10000000);
	  GPIOC -> ODR &= ~(1 << 6);
	  atraso(1000000);*/

	  /*if ((GPIOE -> IDR) & (1<<3) && (GPIOE -> IDR) & (1<<4)){
		  GPIOA -> ODR |= (1<<7);
		  GPIOA -> ODR |= (1<<6);
	  	  }
	  else if ((GPIOE -> IDR) & ~(1<<3) && (GPIOE -> IDR) & ~(1<<4)){
			    GPIOA -> ODR &= ~(1<<6);
			    GPIOA -> ODR &= ~(1<<7);
		  }*/

	  /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/*void atraso(int tempo){
	while (tempo>0) --tempo;
}*/


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
