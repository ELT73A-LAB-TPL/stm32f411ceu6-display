## U8G2 (Universal 8-bit Graphics Library)

- https://controllerstech.com/how-to-port-u8g2-graphic-lib-to-stm32/
- https://github.com/olikraus/u8g2

```bash
# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/u8g2
)
```