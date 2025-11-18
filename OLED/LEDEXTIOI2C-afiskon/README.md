## SSD1306 files
- https://github.com/afiskon/stm32-ssd1306

```c title="CMakeLists.txt"
# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    // highlight-start
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/ssd1306/ssd1306.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/ssd1306/ssd1306_fonts.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/ssd1306/ssd1306_tests.c
    // highlight-end
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    // highlight-next-line
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/ssd1306
)
```

