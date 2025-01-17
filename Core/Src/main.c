/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "snow_tiger.h"
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
SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_DMA_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ILI9341_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		static uint16_t x = 0;
		static uint16_t y = 0;
		static char BufferText[40];
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


		/* COUNTING MULTIPLE SEGMENTS */
		ILI9341_FillScreen(WHITE);
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_DrawText("Counting multiple segments at once", FONT2, 10, 10, BLACK, WHITE);
		HAL_Delay(2000);
		ILI9341_FillScreen(WHITE);

		for(uint16_t i = 0; i <= 10; i++)
		{
			sprintf(BufferText, "Counting: %d", i);
			ILI9341_DrawText(BufferText, FONT3, 10, 10, BLACK, WHITE);
			ILI9341_DrawText(BufferText, FONT3, 10, 30, BLUE, WHITE);
			ILI9341_DrawText(BufferText, FONT3, 10, 50, RED, WHITE);
			ILI9341_DrawText(BufferText, FONT3, 10, 70, GREEN, WHITE);
			ILI9341_DrawText(BufferText, FONT3, 10, 90, BLACK, WHITE);
			ILI9341_DrawText(BufferText, FONT3, 10, 110, BLUE, WHITE);
			ILI9341_DrawText(BufferText, FONT3, 10, 130, RED, WHITE);
			ILI9341_DrawText(BufferText, FONT3, 10, 150, GREEN, WHITE);
			ILI9341_DrawText(BufferText, FONT3, 10, 170, WHITE, BLACK);
			ILI9341_DrawText(BufferText, FONT3, 10, 190, BLUE, BLACK);
			ILI9341_DrawText(BufferText, FONT3, 10, 210, RED, BLACK);
		}
		HAL_Delay(1000);

		/* COUNTING SINGLE SEGMENT */
		ILI9341_FillScreen(WHITE);
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_DrawText("Counting single segment", FONT3, 10, 10, BLACK, WHITE);
		HAL_Delay(2000);
		ILI9341_FillScreen(WHITE);

		for(uint16_t i = 0; i <= 100; i++)
		{
			sprintf(BufferText, "Counting: %d", i);
			ILI9341_DrawText(BufferText, FONT4, 10, 10, BLACK, WHITE);
			HAL_Delay(10);
		}
		HAL_Delay(1000);

		/* ALIGNMENT TEST */
		ILI9341_FillScreen(WHITE);
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_DrawText("Rectangle alignment check", FONT3, 10, 10, BLACK, WHITE);
		HAL_Delay(2000);
		ILI9341_FillScreen(WHITE);

		ILI9341_DrawHollowRectangleCoord(50, 50, 100, 100, BLACK);
		ILI9341_DrawFilledRectangleCoord(20, 20, 50, 50, BLACK);
		ILI9341_DrawHollowRectangleCoord(10, 10, 19, 19, BLACK);
		HAL_Delay(1000);

		/* LINES EXAMPLE */
		ILI9341_FillScreen(WHITE);
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_DrawText("Randomly placed and sized", FONT3, 10, 10, BLACK, WHITE);
		ILI9341_DrawText("Horizontal and Vertical lines", FONT3, 10, 30, BLACK, WHITE);
		HAL_Delay(2000);
		ILI9341_FillScreen(WHITE);

		for(uint32_t i = 0; i < 30000; i++)
		{
			uint32_t random_num = 0;
			uint16_t xr = 0;
			uint16_t yr = 0;
			uint16_t radiusr = 0;
			uint16_t colourr = 0;

			/* Get random inputs */
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			xr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			yr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			radiusr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			colourr = random_num;

			xr &= 0x01FF;
			yr &= 0x01FF;
			radiusr &= 0x001F;

			ILI9341_DrawHLine(xr, yr, radiusr, colourr);
			ILI9341_DrawVLine(xr, yr, radiusr, colourr);
		}
		HAL_Delay(1000);

		/* HOLLOW CIRCLES EXAMPLE */
		ILI9341_FillScreen(WHITE);
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_DrawText("Randomly placed and sized", FONT3, 10, 10, BLACK, WHITE);
		ILI9341_DrawText("Circles", FONT3, 10, 30, BLACK, WHITE);
		HAL_Delay(2000);
		ILI9341_FillScreen(WHITE);

		for(uint32_t i = 0; i < 3000; i++)
		{
			uint32_t random_num = 0;
			uint16_t xr = 0;
			uint16_t yr = 0;
			uint16_t radiusr = 0;
			uint16_t colourr = 0;

			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			xr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			yr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			radiusr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			colourr = random_num;

			xr &= 0x01FF;
			yr &= 0x01FF;
			radiusr &= 0x001F;

			ILI9341_DrawHollowCircle(xr, yr, radiusr*2, colourr);
		}
		HAL_Delay(1000);

		/* FILLED CIRCLES EXAMPLE */
		ILI9341_FillScreen(WHITE);
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_DrawText("Randomly placed and sized", FONT3, 10, 10, BLACK,WHITE);
		ILI9341_DrawText("Filled Circles", FONT3, 10, 30, BLACK, WHITE);
		HAL_Delay(2000);
		ILI9341_FillScreen(WHITE);

		for(uint32_t i = 0; i < 1000; i++)
		{
			uint32_t random_num = 0;
			uint16_t xr = 0;
			uint16_t yr = 0;
			uint16_t radiusr = 0;
			uint16_t colourr = 0;

			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			xr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			yr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			radiusr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			colourr = random_num;

			xr &= 0x01FF;
			yr &= 0x01FF;
			radiusr &= 0x001F;

			ILI9341_DrawFilledCircle(xr, yr, radiusr/2, colourr);
		}
		HAL_Delay(1000);

		/* HOLLOW RECTANGLES EXAMPLE */
		ILI9341_FillScreen(WHITE);
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_DrawText("Randomly placed and sized", FONT3, 10, 10, BLACK, WHITE);
		ILI9341_DrawText("Rectangles", FONT3, 10, 30, BLACK, WHITE);
		HAL_Delay(2000);
		ILI9341_FillScreen(WHITE);

		for(uint32_t i = 0; i < 20000; i++)
		{
			uint32_t random_num = 0;
			uint16_t xr = 0;
			uint16_t yr = 0;
			uint16_t radiusr = 0;
			uint16_t colourr = 0;

			random_num = 0x12345678;//AL_RNG_GetRandomNumber(&hrng);
			xr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			yr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			radiusr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			colourr = random_num;

			xr &= 0x01FF;
			yr &= 0x01FF;
			radiusr &= 0x001F;

			ILI9341_DrawHollowRectangleCoord(xr, yr, xr+radiusr, yr+radiusr, colourr);
		}
		HAL_Delay(1000);

		/* FILLED RECTANGLES EXAMPLE */
		ILI9341_FillScreen(WHITE);
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_DrawText("Randomly placed and sized", FONT3, 10, 10, BLACK, WHITE);
		ILI9341_DrawText("Filled Rectangles", FONT3, 10, 30, BLACK, WHITE);
		HAL_Delay(2000);
		ILI9341_FillScreen(WHITE);

		for(uint32_t i = 0; i < 20000; i++)
		{
			uint32_t random_num = 0;
			uint16_t xr = 0;
			uint16_t yr = 0;
			uint16_t radiusr = 0;
			uint16_t color = 0;

			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			xr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			yr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			radiusr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			color = random_num;

			xr &= 0x01FF;
			yr &= 0x01FF;
			radiusr &= 0x001F;

			ILI9341_DrawRectangle(xr, yr, radiusr, radiusr, color);
		}
		HAL_Delay(1000);

		/* INDIVIDUAL PIXEL EXAMPLE */

		ILI9341_FillScreen(WHITE);
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_DrawText("Slow draw by selecting", FONT3, 10, 10, BLACK, WHITE);
		ILI9341_DrawText("and adressing pixels", FONT3, 10, 30, BLACK, WHITE);
		HAL_Delay(2000);
		ILI9341_FillScreen(WHITE);

		x = 0;
		y = 0;

		while (y < ILI9341_SCREEN_HEIGHT)
		{
			while ((x < ILI9341_SCREEN_WIDTH) && (y < ILI9341_SCREEN_HEIGHT))
			{
				if(x % 2)
				{
					ILI9341_DrawPixel(x, y, BLACK);
				}
				x++;
			}
			y++;
			x = 0;
		}

		x = 0;
		y = 0;

		while (y < ILI9341_SCREEN_HEIGHT)
		{
			while ((x < ILI9341_SCREEN_WIDTH) && (y < ILI9341_SCREEN_HEIGHT))
			{
				if(y % 2)
				{
					ILI9341_DrawPixel(x, y, BLACK);
				}
				x++;
			}
			y++;
			x = 0;
		}
		HAL_Delay(2000);

		/* INDIVIDUAL PIXEL EXAMPLE */
		ILI9341_FillScreen(WHITE);
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_DrawText("Random position and color", FONT3, 10, 10, BLACK, WHITE);
		ILI9341_DrawText("500000 pixels", FONT3, 10, 30, BLACK, WHITE);
		HAL_Delay(2000);
		ILI9341_FillScreen(WHITE);

		for(uint32_t i = 0; i < 500000; i++)
		{
			uint32_t random_num = 0;
			uint16_t xr = 0;
			uint16_t yr = 0;

			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			xr = random_num;
			random_num = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);
			yr = random_num;
			uint16_t color = 0x12345678;//HAL_RNG_GetRandomNumber(&hrng);

			xr &= 0x01FF;
			yr &= 0x01FF;

			ILI9341_DrawPixel(xr, yr, color);
		}
		HAL_Delay(2000);

		/* 565 GRAYSCALE EXAMPLE */
		ILI9341_FillScreen(WHITE);
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_DrawText("Color gradient", FONT3, 10, 10, BLACK, WHITE);
		ILI9341_DrawText("Grayscale", FONT3, 10, 30, BLACK, WHITE);
		HAL_Delay(2000);

		for(uint16_t i = 0; i <= ILI9341_SCREEN_WIDTH; i++)
		{
			uint16_t Red = 0;
			uint16_t Green = 0;
			uint16_t Blue = 0;

			Red = i/(10);
			Red <<= 11;
			Green = i/(5);
			Green <<= 5;
			Blue = i/(10);

			uint16_t RGB = Red + Green + Blue;
			ILI9341_DrawRectangle(i, x, 1, 240, RGB);

		}
		HAL_Delay(2000);

		/* IMAGE EXAMPLE */
		ILI9341_FillScreen(WHITE);
		ILI9341_SetRotation(SCREEN_HORIZONTAL_2);
		ILI9341_DrawText("RGB Picture", FONT3, 10, 10, RED, YELLOW);
		ILI9341_DrawText("TIGER", FONT3, 10, 30, BLACK, WHITE);
		HAL_Delay(2000);
		ILI9341_DrawImage(snow_tiger, SCREEN_VERTICAL_2);
		ILI9341_SetRotation(SCREEN_VERTICAL_1);
		HAL_Delay(5000);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LCD_CS_Pin|LCD_DC_Pin|LCD_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LCD_CS_Pin LCD_DC_Pin LCD_RST_Pin */
  GPIO_InitStruct.Pin = LCD_CS_Pin|LCD_DC_Pin|LCD_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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

#ifdef  USE_FULL_ASSERT
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
