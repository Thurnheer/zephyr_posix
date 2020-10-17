# Cop on Zephyr

This is a sample project to use cop for zephyr

## Setup

Use the following commands to clone all necessary repos
...
west init -m https://github.com/thurnheer/copOnZephyr.git copOnZephyr
cd copOnZephyr
west update
west build -b nucleo_f030r8 copOnZephyr/app/


