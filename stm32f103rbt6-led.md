# stm32f103rbt6-led

### 如何基于STM32HAL库在CLion中创建一个rust工程点亮stm32f103rbt6芯片上点亮PC13引脚上的LED，并在编译时生成hex文件



### ChatGPT

首先，需要安装好CLion、Rust和STM32CubeMX，并在STM32CubeMX中生成一个基于STM32F103RBT6芯片的工程。

接下来，按照以下步骤创建rust工程：

1. 在CLion中创建一个新的rust工程。

2. 在工程根目录下创建一个Cargo.toml文件，并添加以下内容：

```toml
[package]
name = "stm32f103rbt6-led"
version = "0.1.0"
edition = "2018"

[dependencies]
cortex-m = "0.7.2"
cortex-m-rt = "0.6.13"
panic-halt = "0.2.0"
stm32f1xx-hal = "0.10.0"
```

这里使用了cortex-m、cortex-m-rt、panic-halt和stm32f1xx-hal这些依赖库。

3. 在src目录下创建main.rs文件，并添加以下内容：

```rust
#![no_main]
#![no_std]

use panic_halt as _;

use cortex_m_rt::entry;
use stm32f1xx_hal::{prelude::*, stm32};

#[entry]
fn main() -> ! {
    if let (Some(dp), Some(cp)) = (stm32::Peripherals::take(), cortex_m::peripheral::Peripherals::take()) {
        let mut rcc = dp.RCC.constrain();
        let mut gpio_c = dp.GPIOC.split(&mut rcc.apb2);
        let mut led = gpio_c.pc13.into_push_pull_output(&mut gpio_c.crh);

        loop {
            led.set_high().unwrap();
            cortex_m::asm::delay(8_000_000);
            led.set_low().unwrap();
            cortex_m::asm::delay(8_000_000);
        }
    }

    loop {}
}
```

这里的代码使用了STM32F1xx HAL库来控制PC13引脚上的LED点亮和熄灭。

4. 在工程根目录下创建一个build.rs文件，并添加以下内容：

```rust
use std::process::Command;

fn main() {
    let output = Command::new("arm-none-eabi-gcc")
        .arg("-print-file-name=libc.a")
        .output()
        .expect("failed to execute process");

    let path = String::from_utf8(output.stdout).unwrap().trim().to_string();

    println!("cargo:rustc-link-search=native={}", path);
    println!("cargo:rustc-link-lib=c");
}
```

这里的代码用于告诉rust编译器去哪里查找libc.a库文件。

5. 配置CLion的工程设置，以便正确编译和链接rust代码。在工程根目录下创建一个.cargo/config.toml文件，并添加以下内容：

```toml
[target.thumbv7m-none-eabi]
rustflags = [
    "-C", "link-arg=-Tlink.x",
    "-C", "linker=arm-none-eabi-ld",
    "-C", "target-cpu=cortex-m3",
    "-C", "relocation-model=static",
    "-C", "thumb-mode",
    "-C", "no-stack-check",
    "-C", "no-redzone",
]

[build]
target = "thumbv7m-none-eabi"
```

这里的配置用于告诉rust编译器使用thumbv7m-none-eabi目标，以及一些编译和链接选项。

6. 在工程根目录下创建一个link.x文件，并添加以下内容：

```ld
MEMORY
{
    FLASH : ORIGIN = 0x08000000, LENGTH = 64K
    RAM : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .text :
    {
        KEEP(*(.vector_table))
        *(.text*)
    } > FLASH

    .rodata :
    {
        *(.rodata*)
    } > FLASH

    .data :
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > RAM

    .bss :
    {
        _sbss = .;
        *(.bss*)
        _ebss = .;
    } > RAM

    _stack_start = ORIGIN(RAM) + LENGTH(RAM);
    _stack_end = ORIGIN(RAM);
}
```

这里的配置用于告诉链接器如何将代码和数据放置在内存中。

7. 在工程根目录下创建一个build目录，并在其中创建一个build.sh文件，并添加以下内容：

```sh
#!/bin/bash

# build the rust code
cargo build --release

# convert the elf file to hex file
arm-none-eabi-objcopy -O ihex target/thumbv7m-none-eabi/release/stm32f103rbt6-led target/thumbv7m-none-eabi/release/stm32f103rbt6-led.hex
```

这里的脚本用于编译rust代码，并将生成的elf文件转换为hex文件。

8. 最后，在CLion中设置好编译器和调试器，然后就可以通过build.sh脚本编译和生成hex文件了。

注意，如果stm32f103rbt6芯片上的BOOT0引脚为高电平时，芯片将进入串口下载模式，此时无法通过STLink下载程序。需要将BOOT0引脚拉低后再进行下载。





```bash
cargo clone cortex-m-quickstart --vers 0.3.4
```

