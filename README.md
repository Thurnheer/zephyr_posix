# Zephyr posix bug

Zephyr posix hangs when executing unit tests with coverage enabled

## Reproduce bug

```cpp
west init -m https://github.com/thurnheer/copOnZephyr.git zephyr_posix
cd zephyr_posix
west update
west build -b native_posix fibonacci/unittests -DCONFIG_COVERAGE=y
./build/zephyr/zephyr.elf
```

No coverage files are generated (no *.gcda files)


