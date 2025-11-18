/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
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
#include "u8g2.h"

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
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
// https://controllerstech.com/how-to-port-u8g2-graphic-lib-to-stm32/
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,
                            void *arg_ptr);
uint8_t u8x8_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
u8g2_t myDisplay;

// https://lopaka.app
static const uint8_t image_DolphinSuccess_bits[] = {
    0x00, 0x00, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xb8, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x06, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x0b, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x60, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xb0, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x58, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xac, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x16, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x2b, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x05, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x2a, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x05, 0x00, 0x3e, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xc0, 0x0a, 0x80, 0xc1, 0x00, 0x80, 0x00, 0x00, 0x00, 0x44, 0x04, 0x00,
    0x40, 0x01, 0x40, 0x7c, 0x01, 0x80, 0x00, 0x00, 0x00, 0x44, 0x04, 0x00,
    0xc0, 0x0a, 0x20, 0x9e, 0x03, 0x80, 0x00, 0x00, 0x40, 0x48, 0x42, 0x00,
    0x60, 0x01, 0x20, 0x0f, 0x03, 0x00, 0x01, 0x00, 0x80, 0x48, 0x22, 0x00,
    0xa0, 0x0a, 0x10, 0x0f, 0x07, 0x00, 0x01, 0x00, 0x00, 0x01, 0x10, 0x00,
    0x60, 0x01, 0x90, 0x9f, 0x07, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xa0, 0x0a, 0x90, 0xff, 0x04, 0x00, 0xf1, 0x03, 0x00, 0xbc, 0x03, 0x06,
    0x50, 0x00, 0x90, 0xbf, 0x06, 0x00, 0x0f, 0x0c, 0x18, 0x02, 0x84, 0x01,
    0xb0, 0x0a, 0x90, 0xff, 0x07, 0xc0, 0x01, 0x10, 0x60, 0x82, 0x09, 0x00,
    0x50, 0x00, 0x20, 0x7f, 0x03, 0x38, 0x00, 0x20, 0x00, 0x02, 0x12, 0x00,
    0xb0, 0x0a, 0x20, 0xff, 0x03, 0x07, 0x00, 0x20, 0x00, 0x82, 0x15, 0x00,
    0x50, 0x00, 0x40, 0x03, 0x03, 0x00, 0x00, 0x20, 0x78, 0x82, 0x95, 0x07,
    0xb0, 0x0a, 0x80, 0x01, 0x04, 0x00, 0x00, 0x3f, 0x00, 0x02, 0x00, 0x00,
    0x50, 0x00, 0x80, 0x00, 0x00, 0x00, 0xe0, 0x20, 0x00, 0x02, 0x10, 0x00,
    0xb0, 0x0a, 0x80, 0x00, 0x00, 0x00, 0x18, 0x20, 0x00, 0x02, 0x10, 0x00,
    0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x20, 0x60, 0x02, 0x90, 0x01,
    0xb0, 0x0a, 0x00, 0x00, 0x00, 0x80, 0x01, 0x20, 0x18, 0x02, 0x10, 0x06,
    0x58, 0x00, 0x00, 0x20, 0x00, 0x60, 0x00, 0x10, 0x00, 0xfc, 0x0f, 0x00,
    0xa8, 0x0a, 0x00, 0x20, 0x00, 0x18, 0x00, 0x08, 0x00, 0x00, 0x40, 0x00,
    0x58, 0x00, 0x00, 0x40, 0x00, 0x06, 0x00, 0x04, 0x80, 0x00, 0x80, 0x00,
    0xa8, 0x0a, 0x00, 0x80, 0xc1, 0x01, 0x00, 0x03, 0x40, 0x44, 0x04, 0x01,
    0x58, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x80, 0x00, 0x00, 0x44, 0x04, 0x00,
    0xa8, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x42, 0x08, 0x00,
    0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x42, 0x08, 0x00,
    0xac, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x3c, 0x00, 0x00, 0x00,
    0xae, 0x2a, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x00, 0x42, 0xc0, 0x01, 0x00,
    0x5f, 0x05, 0x00, 0x00, 0x00, 0xf8, 0x03, 0x00, 0x81, 0x30, 0x02, 0x00,
    0xaf, 0xaa, 0x00, 0x00, 0x00, 0xff, 0x02, 0x80, 0x80, 0x08, 0x04, 0x00,
    0x5f, 0x05, 0x00, 0x00, 0xc0, 0xff, 0x02, 0x60, 0x80, 0x04, 0x04, 0x00,
    0xaf, 0xaa, 0x02, 0x00, 0x00, 0x3f, 0x02, 0x10, 0x80, 0x02, 0x04, 0x00,
    0x5f, 0x05, 0x00, 0x04, 0x00, 0x00, 0x06, 0x08, 0x80, 0x01, 0x04, 0x00,
    0xaf, 0xaa, 0x00, 0x18, 0x00, 0x00, 0x0e, 0x06, 0x80, 0x00, 0x02, 0x00,
    0x57, 0x01, 0x00, 0x60, 0x00, 0x00, 0xfe, 0x01, 0x40, 0x00, 0x02, 0x00,
    0xaf, 0x2a, 0x00, 0x80, 0x01, 0x00, 0x7e, 0x00, 0x40, 0x00, 0x02, 0x00,
    0x57, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x0f, 0x00, 0x20, 0x00, 0x01, 0x00,
    0xaf, 0x2a, 0x00, 0x00, 0xf0, 0xff, 0x00, 0x00, 0x20, 0x00, 0x01, 0x00,
    0x57, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x80, 0x00, 0x00,
    0xaf, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x40, 0x00, 0x00,
    0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x40, 0x00, 0x00,
    0xab, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x20, 0x00, 0x00,
    0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0x12, 0x00, 0x00};

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick.
   */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  u8g2_Setup_ssd1306_i2c_128x64_noname_f(&myDisplay, U8G2_R0, u8x8_i2c,
                                         u8x8_gpio_and_delay);
  u8g2_InitDisplay(&myDisplay); // send init sequence to the display, display is
                                // in sleep mode after this,
  u8g2_SetPowerSave(&myDisplay, 0); // wake up display

  u8g2_ClearDisplay(&myDisplay);
  u8g2_SetFont(&myDisplay, u8g2_font_ncenB14_tr);
  u8g2_DrawStr(&myDisplay, 0, 15, "Hello world!");
  u8g2_DrawCircle(&myDisplay, 60, 30, 10, U8G2_DRAW_ALL);
  u8g2_SendBuffer(&myDisplay);

  // DolphinSuccess https://lopaka.app
  u8g2_ClearDisplay(&myDisplay);
  u8g2_DrawXBM(&myDisplay, 2, 3, 91, 55, image_DolphinSuccess_bits);
  u8g2_SendBuffer(&myDisplay);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
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
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
}

/**
 * @brief I2C1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C1_Init(void) {

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Blue_LED_GPIO_Port, Blue_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : Blue_LED_Pin */
  GPIO_InitStruct.Pin = Blue_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Blue_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : User_Key_Pin */
  GPIO_InitStruct.Pin = User_Key_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(User_Key_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,
                            void *arg_ptr) {
  switch (msg) {
  case U8X8_MSG_DELAY_MILLI:
    HAL_Delay(arg_int);
    break;
  }
  return 1;
}

uint8_t u8x8_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr) {
  static uint8_t buffer[32]; /* u8g2/u8x8 will never send more than 32 bytes
                                between START_TRANSFER and END_TRANSFER */
  static uint8_t buf_idx;
  uint8_t *data;

  switch (msg) {
  case U8X8_MSG_BYTE_SEND:
    data = (uint8_t *)arg_ptr;
    while (arg_int > 0) {
      buffer[buf_idx++] = *data;
      data++;
      arg_int--;
    }
    break;
  case U8X8_MSG_BYTE_START_TRANSFER:
    buf_idx = 0;
    break;
  case U8X8_MSG_BYTE_END_TRANSFER:
    HAL_I2C_Master_Transmit(&hi2c1, 0x78, buffer, buf_idx, 1000);
    break;
  default:
    return 0;
  }
  return 1;
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1) {
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
void assert_failed(uint8_t *file, uint32_t line) {
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line
     number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
     line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
