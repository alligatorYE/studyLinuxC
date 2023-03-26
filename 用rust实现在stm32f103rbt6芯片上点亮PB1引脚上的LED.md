

# 用rust实现在stm32f103rbt6芯片上点亮PB1引脚上的LED



### ChatGPT

在Rust中，可以使用“Cortex-M”和“stm32f1xx_hal”库来控制STM32F103芯片。以下是一个简单的例子，演示如何在PB1引脚上点亮LED：

```rust
#![no_std]
#![no_main]

use cortex_m_rt::entry;
use stm32f1xx_hal::{
    prelude::*,
    pac,
    gpio::{Output, PushPull},
};

#[entry]
fn main() -> ! {
    // 获取设备的所有资源
    let cp = cortex_m::Peripherals::take().unwrap();
    let dp = pac::Peripherals::take().unwrap();

    // 获取时钟资源
    let mut flash = dp.FLASH.constrain();
    let mut rcc = dp.RCC.constrain();

    // 配置时钟，使得系统时钟为72MHz
    let clocks = rcc.cfgr.sysclk(72.mhz()).freeze(&mut flash.acr);

    // 获取GPIOB资源，并将PB1引脚配置为输出模式
    let mut gpiob = dp.GPIOB.split(&mut rcc.apb2);
    let mut led = gpiob.pb1.into_push_pull_output(&mut gpiob.crh);

    // 点亮LED
    led.set_high().unwrap();

    loop {}
}
```

上述代码中，`entry`宏表示程序入口点，`no_std`和`no_main`宏表示不使用标准库和main函数。首先获取Cortex-M和STM32F1xx_HAL库提供的所有资源，并使用`constrain`方法初始化flash和rcc资源。然后，使用`sysclk`方法将系统时钟配置为72MHz，并使用`freeze`方法将时钟配置应用于系统。接下来，使用`split`方法获取GPIOB资源，并使用`into_push_pull_output`方法将PB1引脚配置为输出模式。最后，使用`set_high`方法点亮LED，并在无限循环中保持程序运行。



### 我

我需要一个可以运行的工程



### ChatGPT

很抱歉，我不知道你需要哪种类型的工程。请提供更多细节和上下文，这样我可以更好地帮助你。



### 我

你的程序有一下报错error[E0433]: failed to resolve: use of undeclared crate or module `stm32f1xx_hal`
 --> src\main.rs:5:5
  |
5 | use stm32f1xx_hal::{
  |     ^^^^^^^^^^^^^ use of undeclared crate or module `stm32f1xx_hal`



### ChatGPT

这个错误提示说明你的代码中使用了`stm32f1xx_hal`但是编译器无法找到这个模块。

解决这个问题需要检查以下几点：

1. 确认你的程序依赖中是否包含了`stm32f1xx_hal`模块。可以在`Cargo.toml`文件中查看依赖列表，确认是否有`stm32f1xx_hal`模块。

2. 确认你的代码中是否正确导入了`stm32f1xx_hal`模块。可以检查代码中的`use`语句，确认是否正确导入了`stm32f1xx_hal`模块。

3. 确认你的代码中是否正确使用了`stm32f1xx_hal`模块。如果你的代码中使用了`stm32f1xx_hal`模块中的函数或结构体，需要确认是否正确使用了这些函数或结构体。

如果以上检查都没有问题，可以尝试重新编译程序，有时候编译器会出现一些奇怪的错误，重新编译可能会解决问题。如果问题仍然存在，可以在开发者社区中寻求帮助。



### 我

怎么在Cargo.toml文件中包含stm32f1xx_hal模块



### ChatGPT

在Cargo.toml文件中包含stm32f1xx_hal模块，需要在[dependencies]部分添加以下内容：

```toml
[dependencies.stm32f1xx-hal]
version = "0.8.3"
features = ["rt"]
```

其中，version为需要使用的版本号，features为需要使用的特性，例如rt为Real-time support。添加完成后，在代码中就可以使用stm32f1xx_hal模块了。例如：

```rust
use stm32f1xx_hal::gpio::GpioExt;
use stm32f1xx_hal::stm32;
```

这里通过use语句导入了gpio和stm32模块中的内容，这些内容都是stm32f1xx_hal模块提供的。



### 我

怎么生成hex文件呢



### ChatGPT

生成hex文件需要使用编译器或者集成开发环境（IDE）。以下是一般的步骤：

1. 编写源代码。

2. 打开编译器或IDE，将源代码文件添加到项目中。

3. 配置编译器或IDE的编译选项，如选择目标芯片、编译器优化等。

4. 编译源代码，生成目标文件（通常是 .obj 或 .o 格式）。

5. 使用链接器将目标文件链接成可执行文件（可选）。

6. 将可执行文件转换为 hex 文件。这可以通过使用命令行工具或者 IDE 提供的选项来完成。

在使用命令行工具的情况下，可以使用 objcopy 命令将目标文件转换为 hex 文件。例如，使用以下命令将目标文件转换为 hex 文件：

```
objcopy -O ihex input_file output_file.hex
```

其中，input_file 是目标文件，output_file.hex 是生成的 hex 文件。

在使用 IDE 的情况下，通常可以在项目属性或者生成选项中找到将可执行文件转换为 hex 文件的选项。



### 我

CLion的rust工程中，让它编译后产生hex文件需要怎么配置



### ChatGPT

要让 CLion 的 Rust 工程编译后产生 hex 文件，需要进行以下配置：

1. 在项目根目录下创建一个 Cargo.toml 文件，内容如下：

   ```
   [package]
   name = "my_project"
   version = "0.1.0"
   authors = ["Your Name <your.email@example.com>"]
   edition = "2018"

   [dependencies]
   cortex-m = "0.6.3"
   cortex-m-rt = "0.6.13"
   panic-halt = "0.2.0"

   [profile.dev]
   panic = "abort"

   [profile.release]
   panic = "abort"

   [target.thumbv7em-none-eabihf]
   rustflags = [
       "-C", "link-arg=-Tlink.x",
       "-C", "linker=arm-none-eabi-ld",
   ]
   ```

   这个文件定义了项目的名称、版本、作者等信息，还列出了项目所依赖的一些库。其中，`cortex-m` 和 `cortex-m-rt` 是用于编写嵌入式程序的 Rust 库，`panic-halt` 是一个用于崩溃时停止程序运行的库。

2. 在项目根目录下创建一个 build.rs 文件，内容如下：

   ```
   use std::process::Command;

   fn main() {
       let output = Command::new("cargo")
           .args(&["build", "--release", "--target=thumbv7em-none-eabihf"])
           .output()
           .expect("Failed to execute command");

       if output.status.success() {
           println!("cargo build succeeded");
       } else {
           println!("cargo build failed");
           println!("{}", String::from_utf8_lossy(&output.stderr));
           std::process::exit(1);
       }

       let output = Command::new("arm-none-eabi-objcopy")
           .args(&[
               "-O",
               "ihex",
               "target/thumbv7em-none-eabihf/release/my_project",
               "target/thumbv7em-none-eabihf/release/my_project.hex",
           ])
           .output()
           .expect("Failed to execute command");

       if output.status.success() {
           println!("objcopy succeeded");
       } else {
           println!("objcopy failed");
           println!("{}", String::from_utf8_lossy(&output.stderr));
           std::process::exit(1);
       }
   }
   ```

   这个文件定义了一个 Rust 脚本，它会在项目构建时被执行。脚本首先调用 `cargo build` 命令编译项目，然后调用 `arm-none-eabi-objcopy` 命令将编译出的可执行文件转换为 hex 文件。

3. 在项目根目录下创建一个 link.x 文件，内容如下：

   ```
   MEMORY
   {
       FLASH : ORIGIN = 0x08000000, LENGTH = 512K
       RAM : ORIGIN = 0x20000000, LENGTH = 128K
   }

   ENTRY(_start)

   SECTIONS
   {
       .text :
       {
           *(.vector_table)
           *(.text*)
       } > FLASH

       .rodata :
       {
           *(.rodata*)
       } > FLASH

       .data :
       {
           *(.data*)
       } > RAM AT > FLASH

       .bss :
       {
           *(.bss*)
       } > RAM

       _stack_end = ORIGIN(RAM) + LENGTH(RAM);
   }
   ```

   这个文件定义了程序的内存布局，以及程序的入口点。它指定了程序的代码和只读数据存放在 flash 中，可读写数据存放在 ram 中。

4. 在 CLion 中打开项目，选择 `File -> Settings -> Build, Execution, Deployment -> Toolchains`，添加一个 Rust 工具链。如果你还没有安装 Rust，需要先安装 Rust 工具链。

5. 在 CLion 中打开项目，选择 `File -> Settings -> Build, Execution, Deployment -> CMake`，在 `CMake options` 中添加 `-DCMAKE_TOOLCHAIN_FILE=arm-none-eabi.cmake`。这个选项告诉 CLion 使用 arm-none-eabi 工具链编译项目。

6. 在 CLion 中打开项目，选择 `File -> Settings -> Build, Execution, Deployment -> Build Tools -> Cargo`，在 `Command` 中输入 `build --release`，在 `Arguments` 中输入 `--target=thumbv7em-none-eabihf`。这个设置告诉 CLion 使用 Cargo 编译项目，并指定编译目标为 thumbv7em-none-eabihf。

7. 在 CLion 中打开项目，选择 `Run -> Edit Configurations`，添加一个 `Embedded GDB Server` 配置。在 `Executable` 中输入 `arm-none-eabi-gdb`，在 `Target` 中输入 `target/thumbv7em-none-eabihf/release/my_project`，在 `GDB Init` 中输入以下内容：

   ```
   target remote :3333
   monitor reset halt
   monitor arm semihosting enable
   load
   ```

   这个配置告诉 CLion 使用 arm-none-eabi-gdb 调试项目，并指定调试目标为编译出的可执行文件。它还启用了半主机调试，使得程序可以在开发板上输出调试信息。

8. 在 CLion 中打开项目，选择 `Run -> Debug 'Embedded GDB Server'`，开始调试项目。调试时，CLion 会连接开发板，并在开发板上运行程序。你可以在 CLion 的调试窗口中看到程序的输出，并在代码中打断点，查看变量的值等。调试完成后，可以使用 `Ctrl+C` 停止调试。此时，编译出的 hex 文件会保存在 `target/thumbv7em-none-eabihf/release/my_project.hex` 中。