# Cop on Zephyr

This is a sample project to use cop for zephyr

## Setup

Use the following commands to clone all necessary repos
```cpp
west init -m https://github.com/thurnheer/copOnZephyr.git copOnZephyr
cd copOnZephyr
west update
west build -b nucleo_f030r8 copOnZephyr/app/
```

This project only builds with the (currently alpha) toolchain version 0.12.0

For linux on x86 64Bit versions:
wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.12.0-alpha-1/zephyr-sdk-0.12.0-alpha-1-x86_64-linux-setup.run
chmod +x zephyr-sdk-0.12.0-alpha-1-x86_64-linux-setup.run
./zephyr-sdk-0.12.0-alpha-1-x86_64-linux-setup.run


