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

  aula_01_09();
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

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 /* GPIOA -> ODR |= 1 << 6;//PA6 nível alto
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
}

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
