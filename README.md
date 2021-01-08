# Zephyr posix bug

Zephyr posix hangs when executing unit tests with coverage enabled

## Reproduce bug

```cpp
west init -m git@github.com:thurnheer/zephyr_posix.git zephyr_posix
cd zephyr_posix
west update
export ZEPHYR_TOOLCHAIN_VARIANT=zephyr
west build -b native_posix fibonacci/unittests -DCONFIG_COVERAGE=y
./build/zephyr/zephyr.elf
```

Test hangs and no coverage files are generated (no *.gcda files)


