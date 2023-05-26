## 一. CAN协议概念

### 1.1 CAN 协议简介

CAN 是控制器局域网络 (Controller Area Network) 的简称，它是由研发和生产汽车电子产品著称的德国 BOSCH 公司开发的，并最终成为国际标准(ISO11519以及ISO11898),是国际上应用最广泛的现场总线之一。差异点如下：

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmGhObw3Yn6cpGsgpfq1pcTR7xs144vqFTBjyJLicXREX8t4c6RbPff7w/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

CAN 总线协议已经成为汽车计算机控制系统和嵌入式工业控制局域网的标准总线，并且拥有以CAN 为底层协议专为大型货车和重工机械车辆设计的 J1939 协议。近年来，它具有的高可靠性和良好的错误检测能力受到重视，被广泛应用于汽车计算机控制系统和环境温度恶劣、电磁辐射强及振动大的工业环境。

我们来贴图一个车载网络构想图

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmFXLalwKEwLBPCr8s8t3ccm1IP8rFxic7mGpfMiawuOqrlJgOVrpvkZ7g/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

### 1.2 CAN 物理层

与 I2C、SPI 等具有时钟信号的同步通讯方式不同，CAN 通讯并不是以时钟信号来进行同步的，它是一种异步通讯，只具有 CAN_High 和 CAN_Low 两条信号线，共同构成一组差分信号线，以差分信号的形式进行通讯。我们来看一个示意图

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmbHfNFZYjWDFPzhn8GcjR9mKXIibBVy3yWr4IRcr9WPKE2DbMw8oe3fQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

#### 1.2.1 闭环总线网络

CAN 物理层的形式主要有两种，图中的 CAN 通讯网络是一种遵循 ISO11898 标准的高速、短距离“闭环网络”，它的总线最大长度为 40m，通信速度最高为 1Mbps，总线的两端各要求有一个“120 欧”的电阻。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKm6wXtQmTR6vtCX6GgCaLjksk0yVeBngtzzbiaFicNiaUdrlk791cf1xAQw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

#### 1.2.2 开环总线网络

图中的是遵循 ISO11519-2 标准的低速、远距离“开环网络”，它的最大传输距离为 1km，最高通讯速率为 125kbps，两根总线是独立的、不形成闭环，要求每根总线上各串联有一个“2.2千欧”的电阻。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmu46ofJvDiaMIo7pNTq8FWhZMdV1J63r4SllD9mphm5bqT5s0jh9FjLw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

#### 1.2.3 通讯节点

从 CAN 通讯网络图可了解到，CAN 总线上可以挂载多个通讯节点，节点之间的信号经过总线传输，实现节点间通讯。由于 CAN 通讯协议不对节点进行地址编码，而是对数据内容进行编码的，所以网络中的节点个数理论上不受限制，只要总线的负载足够即可，可以通过中继器增强负载。

CAN 通讯节点由一个 CAN 控制器及 CAN 收发器组成，控制器与收发器之间通过 CAN_Tx 及CAN_Rx 信号线相连，收发器与 CAN 总线之间使用 CAN_High 及 CAN_Low 信号线相连。其中CAN_Tx 及 CAN_Rx 使用普通的类似 TTL 逻辑信号，而 CAN_High 及 CAN_Low 是一对差分信号线，使用比较特别的差分信号，下一小节再详细说明。

当 CAN 节点需要发送数据时，控制器把要发送的二进制编码通过 CAN_Tx 线发送到收发器，然后由收发器把这个普通的逻辑电平信号转化成差分信号，通过差分线 CAN_High 和 CAN_Low 线输出到 CAN 总线网络。而通过收发器接收总线上的数据到控制器时，则是相反的过程，收发器把总线上收到的 CAN_High 及 CAN_Low 信号转化成普通的逻辑电平信号，通过 CAN_Rx 输出到控制器中。

例如，STM32 的 CAN 片上外设就是通讯节点中的控制器，为了构成完整的节点，还要给它外接一个收发器，在我们实验板中使用型号为 TJA1050 的芯片作为 CAN 收发器。 CAN 控制器与 CAN收发器的关系如同 TTL 串口与 MAX3232 电平转换芯片的关系， MAX3232 芯片把 TTL 电平的串口信号转换成 RS-232 电平的串口信号，CAN 收发器的作用则是把 CAN 控制器的 TTL 电平信号转换成差分信号 (或者相反) 。

目前有以下CAN电平转换芯片（不全）

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmuJIMOhjWXuM6ggJr3bQm8vS2AaktSsicEY5lTNZawmibF8lhnfuaZv4g/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

我们来用TJA1050来看下原理图：

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmvdGHFPzybjdnNWA6kr7mUSI0p0qBCoZqDPBSAH2Liandtiax4Cb5GTnw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

#### 1.2.4 差分信号

差分信号又称差模信号，与传统使用单根信号线电压表示逻辑的方式有区别，使用差分信号传输时，需要两根信号线，这两个信号线的振幅相等，相位相反，通过两根信号线的电压差值来表示

逻辑 0 和逻辑 1。见图，它使用了 V+ 与 V-信号的差值表达出了图下方的信号。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmEb8sJibg02QslsQTIqzW1hRzdwko7sWBKrgic12kejUfWtic5DVicPibrwA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

相对于单信号线传输的方式，使用差分信号传输具有如下优点：

• 抗干扰能力强，当外界存在噪声干扰时，几乎会同时耦合到两条信号线上，而接收端只关心两个信号的差值，所以外界的共模噪声可以被完全抵消。

举一个例子，正常的单线假设逻辑1是3.3V，逻辑0假设是0V，但是如果有噪声，把3.3V弄成了0V(极端)，把0V弄成了-3.3V，此时就逻辑错误，但是有Can高/Can低一般都作用于两根线，所以两个虽然都有噪声影响，但是差值还是不变的

• 能有效抑制它对外部的电磁干扰，同样的道理，由于两根信号的极性相反，他们对外辐射的电磁场可以相互抵消，耦合的越紧密，泄放到外界的电磁能量越少。

举一个例子，假设一根是10V，一根是-10V，单跟都会对外部造成电磁干扰，但是CAN可以把线拧在一起，跟编麻花一样，可以互相抵消电子干扰

• 时序定位精确，由于差分信号的开关变化是位于两个信号的交点，而不像普通单端信号依靠高低两个阈值电压判断，因而受工艺，温度的影响小，能降低时序上的误差，同时也更适合于低幅度信号的电路。

由于差分信号线具有这些优点，所以在 USB 协议、485 协议、以太网协议及 CAN 协议的物理层中，都使用了差分信号传输。

#### 1.2.5 CAN 协议中的差分信号

CAN 协议中对它使用的 CAN_High 及 CAN_Low 表示的差分信号做了规定，见表及图。以高速 CAN 协议为例，当表示逻辑 1 时 (隐性电平) ，CAN_High 和 CAN_Low 线上的电压均为 2.5v，即它们的电压差 VH-V:sub:L=0V；而表示逻辑 0 时 (显性电平) ，CAN_High 的电平为 3.5V，CAN_Low 线的电平为 1.5V，即它们的电压差为 VH-V:sub:L=2V。例如，当 CAN收发器从 CAN_Tx 线接收到来自 CAN 控制器的低电平信号时 (逻辑 0)，它会使 CAN_High 输出3.5V，同时 CAN_Low 输出 1.5V，从而输出显性电平表示逻辑 0 。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmG3Lo4ntWUTlblhcBmsP1bAAyFFtEKXQSI5ApKzoKepPTYpt5OWibfzw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmUtITjffENWBOhd9fcaXydn88tCLt8ERgZH7R21pqS8cREyAS7q68FA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

在 CAN 总线中，必须使它处于隐性电平 (逻辑 1) 或显性电平 (逻辑 0) 中的其中一个状态。假如有两个 CAN 通讯节点，在同一时间，一个输出隐性电平，另一个输出显性电平，类似 I2C 总线的“线与”特性将使它处于显性电平状态，显性电平的名字就是这样来的，即可以认为显性具有优先的意味。

由于 CAN 总线协议的物理层只有 1 对差分线，在一个时刻只能表示一个信号，所以对通讯节点来说，CAN 通讯是半双工的，收发数据需要分时进行。在 CAN 的通讯网络中，因为共用总线，在整个网络中同一时刻只能有一个通讯节点发送信号，其余的节点在该时刻都只能接收。

### 1.3 CAN 协议层

#### 1.3.1 CAN 的波特率及位同步

由于 CAN 属于异步通讯，没有时钟信号线，连接在同一个总线网络中的各个节点会像串口异步通讯那样，节点间使用约定好的波特率进行通讯，特别地， CAN 还会使用“位同步”的方式来抗干扰、吸收误差，实现对总线电平信号进行正确的采样，确保通讯正常。

#### 1.3.2 位时序分解

为了实现位同步，CAN 协议把每一个数据位的时序分解成如图 所示的 SS 段、PTS 段、PBS1 段、PBS2 段，这四段的长度加起来即为一个 CAN 数据位的长度。分解后最小的时间单位是 Tq，而一个完整的位由 8~25 个 Tq 组成。为方便表示，图 中的高低电平直接代表信号逻辑 0 或逻辑 1(不是差分信号)。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmMGstsBtwsUJZugjV16Tj6HUu2VD9pk5eYqYRe9UWZs2OSrlm1EjfXw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

该图中表示的 CAN 通讯信号每一个数据位的长度为 19Tq，其中 SS 段占 1Tq， PTS 段占 6Tq， PBS1段占 5Tq， PBS2 段占 7Tq。信号的采样点位于 PBS1 段与 PBS2 段之间，通过控制各段的长度，可以对采样点的位置进行偏移，以便准确地采样。

各段的作用如介绍下：

• SS 段 (SYNC SEG)

SS 译为同步段，若通讯节点检测到总线上信号的跳变沿被包含在 SS 段的范围之内，则表示节点与总线的时序是同步的，当节点与总线同步时，采样点采集到的总线电平即可被确定为该位的电平。SS 段的大小固定为 1Tq。

• PTS 段 (PROP SEG)

PTS 译为传播时间段，这个时间段是用于补偿网络的物理延时时间。是总线上输入比较器延时和输出驱动器延时总和的两倍。PTS 段的大小可以为 1~8Tq。

• PBS1 段 (PHASE SEG1)，

PBS1 译为相位缓冲段，主要用来补偿边沿阶段的误差，它的时间长度在重新同步的时候可以加长。PBS1 段的初始大小可以为 1~8Tq。

• PBS2 段 (PHASE SEG2)

PBS2 这是另一个相位缓冲段，也是用来补偿边沿阶段误差的，它的时间长度在重新同步时可以缩短。PBS2 段的初始大小可以为 2~8Tq。

#### 1.3.3 通讯的波特率

总线上的各个通讯节点只要约定好 1 个 Tq 的时间长度以及每一个数据位占据多少个 Tq，就可以确定 CAN 通讯的波特率。

例如，假设上图中的 1Tq=1us，而每个数据位由 19 个 Tq 组成，则传输一位数据需要时间 T1bit=19us，从而每秒可以传输的数据位个数为：1x10次方/19 = 52631.6 (bps)

这个每秒可传输的数据位的个数即为通讯中的波特率。

#### 1.3.4 同步过程分析

波特率只是约定了每个数据位的长度，数据同步还涉及到相位的细节，这个时候就需要用到数据位内的 SS、PTS、PBS1 及 PBS2 段了。根据对段的应用方式差异， CAN 的数据同步分为硬同步和重新同步。其中硬同步只是当存在“帧起始信号”时起作用，无法确保后续一连串的位时序都是同步的，而重新同步方式可解决该问题，这两种方式具体介绍如下：

**(1) 硬同步**

若某个 CAN 节点通过总线发送数据时，它会发送一个表示通讯起始的信号 (即下一小节介绍的帧起始信号)，该信号是一个由高变低的下降沿。而挂载到 CAN 总线上的通讯节点在不发送数据时，会时刻检测总线上的信号。见图 ，可以看到当总线出现帧起始信号时，某节点检测到总线的帧起始信号不在节点内部时序的 SS 段范围，所以判断它自己的内部时序与总线不同步，因而这个状态的采样点采集得的数据是不正确的。所以节点以硬同步的方式调整，把自己的位时序中的 SS 段平移至总线出现下降沿的部分，获得同步，同步后采样点就可以采集得正确数据了。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmWqibrFCV14lMFZPQAY9IX6X558t1zJe1Bia3PG65bqUdAUf17aO0cPRg/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

**(2) 重新同步**

前面的硬同步只是当存在帧起始信号时才起作用，如果在一帧很长的数据内，节点信号与总线信号相位有偏移时，这种同步方式就无能为力了。因而需要引入重新同步方式，它利用普通数据位的高至低电平的跳变沿来同步 (帧起始信号是特殊的跳变沿)。重新同步与硬同步方式相似的地方是它们都使用 SS 段来进行检测，同步的目的都是使节点内的 SS 段把跳变沿包含起来。重新同步的方式分为超前和滞后两种情况，以总线跳变沿与 SS 段的相对位置进行区分。第一种相位超前的情况如图 ，节点从总线的边沿跳变中，检测到它内部的时序比总线的时序相对超前 2Tq，这时控制器在下一个位时序中的 PBS1 段增加 2Tq 的时间长度，使得节点与总线时序重新同步。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmJLLq1LHdiaoreibMia0iauWhzYvUDe95TB6NCu9FGDHZK4pLQXq5yjL1Fw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

第二种相位滞后的情况如图 ，节点从总线的边沿跳变中，检测到它的时序比总线的时序相对滞后 2Tq，这时控制器在前一个位时序中的 PBS2 段减少 2Tq 的时间长度，获得同步。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmR8nC5MeFgVFs4lI9ORcQCJjdribSOrcjG1kL6X8m4iaXricOqZgqkctNQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

在重新同步的时候，PBS1 和 PBS2 中增加或减少的这段时间长度被定义为“重新同步补偿宽度SJW* (reSynchronization Jump Width)”。一般来说 CAN 控制器会限定 SJW 的最大值，如限定了最大 SJW=3Tq 时，单次同步调整的时候不能增加或减少超过 3Tq 的时间长度，若有需要，控制器会通过多次小幅度调整来实现同步。当控制器设置的 SJW 极限值较大时，可以吸收的误差加大，但通讯的速度会下降

#### 1.3.5 CAN 的报文种类及结构

在 SPI 通讯中，片选、时钟信号、数据输入及数据输出这 4 个信号都有单独的信号线，I2C 协议包含有时钟信号及数据信号 2 条信号线，异步串口包含接收与发送 2 条信号线，这些协议包含的信号都比 CAN 协议要丰富，它们能轻易进行数据同步或区分数据传输方向。而 CAN 使用的是两条差分信号线，只能表达一个信号，简洁的物理层决定了 CAN 必然要配上一套更复杂的协议，如何用一个信号通道实现同样、甚至更强大的功能呢？CAN 协议给出的解决方案是对数据、操作命令 (如读/写) 以及同步信号进行打包，打包后的这些内容称为报文。

##### 1.3.5.1 报文的种类

在原始数据段的前面加上传输起始标签、片选 (识别) 标签和控制标签，在数据的尾段加上 CRC校验标签、应答标签和传输结束标签，把这些内容按特定的格式打包好，就可以用一个通道表达各种信号了，各种各样的标签就如同 SPI 中各种通道上的信号，起到了协同传输的作用。当整个数据包被传输到其它设备时，只要这些设备按格式去解读，就能还原出原始数据，这样的报文就被称为 CAN 的“数据帧”。

为了更有效地控制通讯，CAN 一共规定了 5 种类型的帧，它们的类型及用途说明如表

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmQlZUTjfhHjgSxBrfVrEKSOIYVKpLt9mWx6CkcqiaZFZ1wHe5IQ0axGA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

##### 1.3.5.2 数据帧的结构

数据帧是在 CAN 通讯中最主要、最复杂的报文，我们来了解它的结构，见图

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmTwGShElrRMmPrZBp3JBNY2bmxn14VMQoSk7fALdhNcJlDiabv1pBvYg/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

数据帧以一个显性位 (逻辑 0) 开始，以 7 个连续的隐性位 (逻辑 1) 结束，在它们之间，分别有仲裁段、控制段、数据段、CRC 段和 ACK 段。

• 帧起始

SOF 段 (Start OfFrame)，译为帧起始，帧起始信号只有一个数据位，是一个显性电平，它用于通知各个节点将有数据传输，其它节点通过帧起始信号的电平跳变沿来进行硬同步。

• 仲裁段

当同时有两个报文被发送时，总线会根据仲裁段的内容决定哪个数据包能被传输，这也是它名称的由来。

仲裁段的内容主要为本数据帧的 ID 信息 (标识符)，数据帧具有标准格式和扩展格式两种，区别就在于 ID 信息的长度，标准格式的 ID 为 11 位，扩展格式的 ID 为 29 位，它在标准 ID 的基础上多出 18 位。在 CAN 协议中， ID 起着重要的作用，它决定着数据帧发送的优先级，也决定着其它节点是否会接收这个数据帧。

CAN 协议不对挂载在它之上的节点分配优先级和地址，对总线的占有权是由信息的重要性决定的，即对于重要的信息，我们会给它打包上一个优先级高的 ID，使它能够及时地发送出去。也正因为它这样的优先级分配原则，使得 CAN 的扩展性大大加强，在总线上增加或减少节点并不影响其它设备。报文的优先级，是通过对 ID 的仲裁来确定的。根据前面对物理层的分析我们知道如果总线上同时出现显性电平和隐性电平，总线的状态会被置为显性电平，CAN 正是利用这个特性进行仲裁。

若两个节点同时竞争 CAN 总线的占有权，当它们发送报文时，若首先出现隐性电平，则会失去对总线的占有权，进入接收状态。见图 ，在开始阶段，两个设备发送的电平一样，所以它们一直继续发送数据。到了图中箭头所指的时序处，节点单元 1 发送的为隐性电平，而此时节点单元 2 发送的为显性电平，由于总线的“线与”特性使它表达出显示电平，因此单元 2 竞争总线成功，这个报文得以被继续发送出去。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKm3sJnoyY1nib9nicIChZLniaWGbu1lYibfJFTzE6uugX9qIrZZsHP3HFyjw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

仲裁段 ID 的优先级也影响着接收设备对报文的反应。因为在 CAN 总线上数据是以广播的形式发送的，所有连接在 CAN 总线的节点都会收到所有其它节点发出的有效数据，因而我们的 CAN

控制器大多具有根据 ID 过滤报文的功能，它可以控制自己只接收某些 ID 的报文。回看数据帧格式，可看到仲裁段除了报文 ID 外，还有 RTR、IDE 和 SRR 位。

(1) RTR 位 (Remote Transmission Request Bit)，译作远程传输请求位，它是用于区分数据帧和遥控帧的，当它为显性电平时表示数据帧，隐性电平时表示遥控帧。

(2) IDE 位 (Identifier ExtensionBit)，译作标识符扩展位，它是用于区分标准格式与扩展格式，当它为显性电平时表示标准格式，隐性电平时表示扩展格式。

(3) SRR 位 (Substitute Remote Request Bit)，只存在于扩展格式，它用于替代标准格式中的 RTR位。由于扩展帧中的 SRR 位为隐性位，RTR 在数据帧为显性位，所以在两个 ID 相同的标准格式报文与扩展格式报文中，标准格式的优先级较高。

• 控制段

在控制段中的 r1 和 r0 为保留位，默认设置为显性位。它最主要的是 DLC 段 (Data Length Code)，译为数据长度码，它由 4 个数据位组成，用于表示本报文中的数据段含有多少个字节， DLC 段表示的数字为 0~8。

• 数据段

数据段为数据帧的核心内容，它是节点要发送的原始信息，由 0~8 个字节组成，MSB 先行。

• CRC 段

为了保证报文的正确传输，CAN 的报文包含了一段 15 位的 CRC 校验码，一旦接收节点算出的CRC 码跟接收到的 CRC 码不同，则它会向发送节点反馈出错信息，利用错误帧请求它重新发送。CRC 部分的计算一般由 CAN 控制器硬件完成，出错时的处理则由软件控制最大重发数。在 CRC 校验码之后，有一个 CRC 界定符，它为隐性位，主要作用是把 CRC 校验码与后面的 ACK段间隔起来。

• ACK 段

ACK 段包括一个 ACK 槽位，和 ACK 界定符位。类似 I2C 总线，在 ACK 槽位中，发送节点发送的是隐性位，而接收节点则在这一位中发送显性位以示应答。在 ACK 槽和帧结束之间由 ACK 界定符间隔开。

• 帧结束

EOF 段 (End Of Frame)，译为帧结束，帧结束段由发送节点发送的 7 个隐性位表示结束。

##### 1.3.5.3 其它报文的结构

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKm7bprg1nrqTwKmZicmrRwGAfbpSBCeqWHv7eXhuKYthc0pNic2Rzia2PZA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmpAQ5AJ4Q1HMick2stVMn0t8dfPcw08qRw4k23xnMicIMwYlM6F5GyE2w/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

## 二. STM32 CAN 控制器介绍

STM32 的芯片中具有 bxCAN 控制器 (Basic Extended CAN)，它支持 CAN 协议 2.0A 和 2.0B 标准。该 CAN 控制器支持最高的通讯速率为 1Mb/s；可以自动地接收和发送 CAN 报文，支持使用标准ID 和扩展 ID 的报文；外设中具有 3 个发送邮箱，发送报文的优先级可以使用软件控制，还可以记录发送的时间；具有 2 个 3 级深度的接收 FIFO，可使用过滤功能只接收或不接收某些 ID 号的报文；可配置成自动重发；不支持使用 DMA 进行数据收发。框架示意图如下：

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmBKTSz7TynAVPJPETgfR30WPMWo2kaWlb7U1aoyThKtP2HOwJrnemQw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

STM32 的有两组 CAN 控制器，其中 CAN1 是主设备，框图中的“存储访问控制器”是由 CAN1控制的，CAN2 无法直接访问存储区域，所以使用 CAN2 的时候必须使能 CAN1 外设的时钟。框图中主要包含 CAN 控制内核、发送邮箱、接收 FIFO 以及验收筛选器，下面对框图中的各个部分进行介绍。

### 2.1 CAN 控制内核

框图中标号处的 CAN 控制内核包含了各种控制寄存器及状态寄存器，我们主要讲解其中的主控制寄存器 CAN_MCR 及位时序寄存器 CAN_BTR。

#### 2.1.1 主控制寄存器 CAN_MCR

主控制寄存器 CAN_MCR 负责管理 CAN 的工作模式，它使用以下寄存器位实现控制。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmfbEndVWWgelD9IXrMcAtB8xaTK4Ob6cqYN4ySQg4orS8icTb0coQbbg/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

**(1) DBF 调试冻结功能**

DBF(Debug freeze) 调试冻结，使用它可设置 CAN 处于工作状态或禁止收发的状态，禁止收发时仍可访问接收 FIFO 中的数据。这两种状态是当 STM32 芯片处于程序调试模式时才使用的，平时使用并不影响。

**(2) TTCM 时间触发模式**

TTCM(Time triggered communication mode) 时间触发模式，它用于配置 CAN 的时间触发通信模式，在此模式下，CAN 使用它内部定时器产生时间戳，并把它保存在CAN_RDTxR、CAN_TDTxR 寄存器中。内部定时器在每个 CAN 位时间累加，在接收和发送的帧起始位被采样，并生成时间戳。利用它可以实现 ISO 11898-4 CAN 标准的分时同步通信功能。

**(3) ABOM 自动离线管理**

ABOM (Automatic bus-off management) 自动离线管理，它用于设置是否使用自动离线管理功能。当节点检测到它发送错误或接收错误超过一定值时，会自动进入离线状态，在离线状态中， CAN 不能接收或发送报文。处于离线状态的时候，可以软件控制恢复或者直接使用这个自动离线管理功能，它会在适当的时候自动恢复。

**(4) AWUM 自动唤醒**

AWUM (Automatic bus-off management)，自动唤醒功能，CAN 外设可以使用软件进入低功耗的睡眠模式，如果使能了这个自动唤醒功能，当 CAN 检测到总线活动的时候，会自动唤醒。

**(5) NART 自动重传**

NART(No automatic retransmission) 报文自动重传功能，设置这个功能后，当报文发送失败时会自动重传至成功为止。若不使用这个功能，无论发送结果如何，消息只发送一次。

**(6) RFLM 锁定模式**

RFLM(Receive FIFO locked mode)FIFO 锁定模式，该功能用于锁定接收 FIFO 。锁定后，当接收 FIFO 溢出时，会丢弃下一个接收的报文。若不锁定，则下一个接收到的报文会覆盖原报文。

**(7) TXFP 报文发送优先级的判定方法**

TXFP(Transmit FIFO priority) 报文发送优先级的判定方法，当 CAN 外设的发送邮箱中有多个待发送报文时，本功能可以控制它是根据报文的 ID 优先级还是报文存进邮箱的顺序来发送。

#### 2.1.2 位时序寄存器 (CAN_BTR) 及波特率

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmuyFnKNQ5I5ibRViasQgTwmCJYsgXicIccpbo5RwTgkQPGB82kDDIjT1ZQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

CAN 外设中的位时序寄存器 CAN_BTR 用于配置测试模式、波特率以及各种位内的段参数。

##### 2.1.2.1 模式

位31 SILM：静默模式（调试）(Silent mode (debug))

0：正常工作

1：静默模式

位30 LBKM：环回模式（调试）(Loop back mode (debug))

0：禁止环回模式

1：使能环回模式

为方便调试，STM32 的 CAN 提供了测试模式，配置位时序寄存器 CAN_BTR 的 SILM 及 LBKM寄存器位可以控制使用正常模式、静默模式、回环模式及静默回环模式，见图。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmVdbzv8iaTfoKJm8KBAKiaAmlcSjnjib8j6Mltvm2ZwXAQsaMsJsde8Faw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

各个工作模式介绍如下：

• 正常模式

正常模式下就是一个正常的 CAN 节点，可以向总线发送数据和接收数据。

• 静默模式

静默模式下，它自己的输出端的逻辑 0 数据会直接传输到它自己的输入端，逻辑 1 可以被发送到总线，所以它不能向总线发送显性位 (逻辑 0)，只能发送隐性位 (逻辑 1)。输入端可以从总线接收内容。由于它只可发送的隐性位不会强制影响总线的状态，所以把它称为静默模式。这种模式一般用于监测，它可以用于分析总线上的流量，但又不会因为发送显性位而影响总线。

• 回环模式

回环模式下，它自己的输出端的所有内容都直接传输到自己的输入端，输出端的内容同时也会被传输到总线上，即也可使用总线监测它的发送内容。输入端只接收自己发送端的内容，不接收来自总线上的内容。使用回环模式可以进行自检。

• 回环静默模式

回环静默模式是以上两种模式的结合，自己的输出端的所有内容都直接传输到自己的输入端，并且不会向总线发送显性位影响总线，不能通过总线监测它的发送内容。输入端只接收自己发送端的内容，不接收来自总线上的内容。这种方式可以在“热自检”时使用，即自我检查的时候，不会干扰总线。

以上说的各个模式，是不需要修改硬件接线的，例如，当输出直接连输入时，它是在 STM32 芯片内部连接的，传输路径不经过 STM32 的 CAN_Tx/Rx 引脚，更不经过外部连接的 CAN 收发器，只有输出数据到总线或从总线接收的情况下才会经过 CAN_Tx/Rx 引脚和收发器

##### 2.1.2.2 位时序及波特率

STM32 外设定义的位时序与我们前面解释的 CAN 标准时序有一点区别，见图

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmXt2picE7a8Pf6mko4uQps1oJOR9214FtNG3YzgQqjPz2PsBEJcBbrTQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

STM32 的 CAN 外设位时序中只包含 3 段，分别是同步段 SYNC_SEG、位段 BS1 及位段 BS2，采样点位于 BS1 及 BS2 段的交界处。其中 SYNC_SEG 段固定长度为 1Tq，而 BS1 及 BS2 段可以

在位时序寄存器 CAN_BTR 设置它们的时间长度，它们可以在重新同步期间增长或缩短，该长度SJW 也可在位时序寄存器中配置。

理解 STM32 的 CAN 外设的位时序时，可以把它的 BS1 段理解为是由前面介绍的 CAN 标准协议中 PTS 段与 PBS1 段合在一起的，而 BS2 段就相当于 PBS2 段。

了解位时序后，我们就可以配置波特率了。通过配置位时序寄存器 CAN_BTR 的 TS1[3:0] 及

TS2[2:0] 寄存器位设定 BS1 及 BS2 段的长度后，我们就可以确定每个 CAN 数据位的时间：

BS1 段时间：TS1=Tq x (TS1[3:0] + 1)，

BS2 段时间：TS2= Tq x (TS2[2:0] + 1)，

一个数据位的时间：T1bit =1Tq+TS1+TS2=1+ (TS1[3:0] + 1)+ (TS2[2:0] + 1)= N Tq

其中单个时间片的长度 Tq 与 CAN 外设的所挂载的时钟总线及分频器配置有关，CAN1 和 CAN2外设都是挂载在 APB1 总线上的，而位时序寄存器 CAN_BTR 中的 BRP[9:0] 寄存器位可以设置

CAN波特率=Fpclk1/((CAN_BS1+CAN_BS2+1)*CAN_Prescaler)

其中clk为42M！

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKm05zNT016Cw7fQqIRyujWST3jUlMiceSPibsbuEQbBcviawicFic8vcVrLpA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmnibKFialLC3odcTNicNic1bibS7de0J2Rdsckpc6vOwc3hicFDwuW3D4ibkcA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

推荐一个CAN波特率计算器

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmY2BjGAy9ZxxACkAibRz1FVjWvETvWPibxic5FAq8oaNz5jxNq8y1o0eIA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

📎CAN波特率计算 f103AHP1_36M f407AHP1_42M 采样点软件有说明.rar

### 2.2 CAN 发送邮箱

回到图 中的 CAN 外设框图，在标号处的是 CAN 外设的发送邮箱，它一共有 3 个发送邮箱，即最多可以缓存 3 个待发送的报文。每个发送邮箱中包含有标识符寄存器 CAN_TIxR、数据长度控制寄存器 CAN_TDTxR 及 2 个数据寄存器 CAN_TDLxR、CAN_TDHxR，它们的功能见表

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKm1wibZicH8kJiaRUJQat9YIbFK4xDw3MFTKqlPJUleo64Tj8cwwZy9ic7sw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

当我们要使用 CAN 外设发送报文时，把报文的各个段分解，按位置写入到这些寄存器中，并对标识符寄存器 CAN_TIxR 中的发送请求寄存器位 TMIDxR_TXRQ 置 1，即可把数据发送出去。其中标识符寄存器 CAN_TIxR 中的 STDID 寄存器位比较特别。我们知道 CAN 的标准标识符的总位数为 11 位，而扩展标识符的总位数为 29 位的。当报文使用扩展标识符的时候，标识符寄存器 CAN_TIxR 中的 STDID[10:0] 等效于 EXTID[18:28] 位，它与 EXTID[17:0] 共同组成完整的 29位扩展标识符。

### 2.3 CAN 接收 FIFO

图 中的 CAN 外设框图，在标号处的是 CAN 外设的接收 FIFO，它一共有 2 个接收 FIFO，每个 FIFO 中有 3 个邮箱，即最多可以缓存 6 个接收到的报文。当接收到报文时，FIFO 的报文计数器会自增，而 STM32 内部读取 FIFO 数据之后，报文计数器会自减，我们通过状态寄存器可获知报文计数器的值，而通过前面主控制寄存器的 RFLM 位，可设置锁定模式，锁定模式下 FIFO溢出时会丢弃新报文，非锁定模式下 FIFO 溢出时新报文会覆盖旧报文。跟发送邮箱类似，每个接收 FIFO 中包含有标识符寄存器 CAN_RIxR、数据长度控制寄存器CAN_RDTxR 及 2 个数据寄存器 CAN_RDLxR、CAN_RDHxR，它们的功能见表。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmyVapPjic1dt14OnNVQglFxfnctdQ04pf5TF9AwzWSm19PoLef8eSiaMg/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

通过中断或状态寄存器知道接收 FIFO 有数据后，我们再读取这些寄存器的值即可把接收到的报文加载到 STM32 的内存中

### 2.4 验收筛选器

图 中的 CAN 外设框图，在标号处的是 CAN 外设的验收筛选器，一共有 28 个筛选器组，每个筛选器组有 2 个寄存器，CAN1 和 CAN2 共用的筛选器的。在 CAN 协议中，消息的标识符与节点地址无关，但与消息内容有关。因此，发送节点将报文广播给所有接收器时，接收节点会根据报文标识符的值来确定软件是否需要该消息，为了简化软件的工作，STM32 的 CAN 外设接收报文前会先使用验收筛选器检查，只接收需要的报文到 FIFO中。

筛选器工作的时候，可以调整筛选 ID 的长度及过滤模式。根据筛选 ID 长度来分类有有以下两种：

(1) 检查 STDID[10:0]、EXTID[17:0]、IDE 和 RTR 位，一共 31 位。

(2) 检查 STDID[10:0]、RTR、IDE 和 EXTID[17:15]，一共 16 位。

通过配置筛选尺度寄存器 CAN_FS1R 的 FSCx 位可以设置筛选器工作在哪个尺度。而根据过滤的方法分为以下两种模式：

(1) 标识符列表模式，它把要接收报文的 ID 列成一个表，要求报文 ID 与列表中的某一个标识符完全相同才可以接收，可以理解为白名单管理。

(2) 掩码模式，它把可接收报文 ID 的某几位作为列表，这几位被称为掩码，可以把它理解成关键字搜索，只要掩码 (关键字) 相同，就符合要求，报文就会被保存到接收 FIFO。通过配置筛选模式寄存器 CAN_FM1R 的 FBMx 位可以设置筛选器工作在哪个模式。不同的尺度和不同的过滤方法可使筛选器工作在图 的 4 种状态。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmlpIo7HmzPgympqweumg8LUt8C44bXNKSjx7yzZzXib7aq2M1xIjUzSA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

每组筛选器包含 2 个 32 位的寄存器，分别为 CAN_FxR1 和 CAN_FxR2，它们用来存储要筛选的ID 或掩码，各个寄存器位代表的意义与图中两个寄存器下面“映射”的一栏一致，各个模式的说明见表。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmibJymX75Z4KkrWg7GBsffVHrGBLXp7yERfeyy7sm0hwTibHTZKIetj5w/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

例如下面的表格所示，在掩码模式时，第一个寄存器存储要筛选的 ID，第二个寄存器存储掩码，掩码为 1 的部分表示该位必须与 ID 中的内容一致，筛选的结果为表中第三行的 ID 值，它是一组包含多个的 ID 值，其中 x 表示该位可以为 1 可以为 0。

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmzkV1MOo5IjYp5q0KgGpUgArdHRSZic1ibMbLRFc2JuQEH5ZO21NZmEOw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

而工作在标识符模式时，2 个寄存器存储的都是要筛选的 ID，它只包含 2 个要筛选的 ID 值 (32位模式时)。

如果使能了筛选器，且报文的 ID 与所有筛选器的配置都不匹配，CAN 外设会丢弃该报文，不存入接收 FIFO。

### 2.5 整体控制逻辑

回到图 结构框图，图中的标号处表示的是 CAN2 外设的结构，它与 CAN1 外设是一样的，他们共用筛选器且由于存储访问控制器由 CAN1 控制，所以要使用 CAN2 的时候必须要使能CAN1 的时钟。其中 STM32F103 系列芯片不具有 CAN2 控制器。

### 2.6 STM32 HAL库代码逻辑

#### 2.6.1 初始化

注意：网络上基本上用的很久的HAL库，我们采用很新的1.25.2，最新的库还是差异挺大的！

从 STM32 的 CAN 外设我们了解到它的功能非常多，控制涉及的寄存器也非常丰富，而使用STM32 HAL 库提供的各种结构体及库函数可以简化这些控制过程。跟其它外设一样，STM32

HAL 库提供了 CAN 初始化结构体及初始化函数来控制 CAN 的工作方式，提供了收发报文使用的结构体及收发函数，还有配置控制筛选器模式及 ID 的结构体。这些内容都定义在库文件“STM32F4xx_hal_can.h”及“STM32F4xx_hal_can.c”中，编程时我们可以结合这两个文件内的注释使用或参考库帮助文档。首先我们来学习初始化结构体的内容，见代码清单 1。代码清单 CAN 初始化结构

```
typedef struct
{
  uint32_t Prescaler;  /* 配置 CAN 外设的时钟分频，可设置为 1-1024*/
  uint32_t Mode;       /* 配置 CAN 的工作模式，回环或正常模式 */
  uint32_t SyncJumpWidth;  /* 配置 SJW 极限值 */
  uint32_t TimeSeg1;   /* 配置 BS1 段长度 */
  uint32_t TimeSeg2;   /* 配置 BS2 段长度 */
  FunctionalState TimeTriggeredMode;   /* 是否使能 TTCM 时间触发功能 */
  FunctionalState AutoBusOff;     /* 是否使能 ABOM 自动离线管理功能 */
  FunctionalState AutoWakeUp;   /* 是否使能 AWUM 自动唤醒功能 */
  FunctionalState AutoRetransmission;  /* 是否使能 NART 自动重传功能 */
  FunctionalState ReceiveFifoLocked;   /* 是否使能 RFLM 锁定 FIFO 功能 */
  FunctionalState TransmitFifoPriority;/* 配置 TXFP 报文优先级的判定方法 */
} CAN_InitTypeDef;
```

体这些结构体成员说明如下，其中括号内的文字是对应参数在 STM32 HAL 库中定义的宏

(1) Prescaler

本成员设置 CAN 外设的时钟分频，它可控制时间片 Tq 的时间长度，这里设置的值最终会减 1 后再写入 BRP 寄存器位，即前面介绍的 Tq 计算公式：

Tq = (BRP[9:0]+1) x TPCLK

等效于：Tq = CAN_Prescaler x TPCLK

(2) Mode

本成员设置 CAN 的工作模式，可设置为正常模式 (CAN_MODE_NORMAL)、回环模式 (CAN_MODE_LOOPBACK)、静默模式 (CAN_MODE_SILENT) 以及回环静默模式(CAN_MODE_SILENT_LOOPBACK)。

(3) SyncJumpWidth

本成员可以配置 SJW 的极限长度，即 CAN 重新同步时单次可增加或缩短的最大长度，它可以被配置为 1-4Tq(CAN_SJW_1/2/3/4tq)。

(4) TimeSeg1

本成员用于设置 CAN 位时序中的 BS1 段的长度，它可以被配置为 1-16 个 Tq 长度(CAN_BS1_1/2/3…16tq)。

(5) TimeSeg2

本成员用于设置 CAN 位时序中的 BS2 段的长度，它可以被配置为 1-8 个 Tq 长度(CAN_BS2_1/2/3…8tq)。SYNC_SEG、 BS1 段及 BS2 段的长度加起来即一个数据位的长度，即前面介绍的原来

计算公式：T1bit =1Tq+TS1+TS2=1+ (TS1[3:0] + 1)+ (TS2[2:0] + 1)

等效于：T1bit= 1Tq+CAN_BS1+CAN_BS2

(6) TimeTriggeredMode

本成员用于设置是否使用时间触发功能 (ENABLE/DISABLE)，时间触发功能在某些CAN 标准中会使用到。

(7) AutoBusOff

本成员用于设置是否使用自动离线管理 (ENABLE/DISABLE)，使用自动离线管理可以在节点出错离线后适时自动恢复，不需要软件干预。

(8) AutoWakeUp

本成员用于设置是否使用自动唤醒功能 (ENABLE/DISABLE)，使能自动唤醒功能后它会在监测到总线活动后自动唤醒。

(9) AutoWakeUp

本成员用于设置是否使用自动离线管理功能 (ENABLE/DISABLE)，使用自动离线管理可以在出错时离线后适时自动恢复，不需要软件干预。

(10) AutoRetransmission

本成员用于设置是否使用自动重传功能 (ENABLE/DISABLE)，使用自动重传功能时，会一直发送报文直到成功为止。

(11) ReceiveFifoLocked

本成员用于设置是否使用锁定接收 FIFO(ENABLE/DISABLE)，锁定接收 FIFO 后，若FIFO 溢出时会丢弃新数据，否则在 FIFO 溢出时以新数据覆盖旧数据。

(12) TransmitFifoPriority

本成员用于设置发送报文的优先级判定方法 (ENABLE/DISABLE)，使能时，以报文存入发送邮箱的先后顺序来发送，否则按照报文 ID 的优先级来发送。配置完这些结构体成员后，我们调用库函数 HAL_CAN_Init 即可把这些参数写入到 CAN 控制寄存器中，实现 CAN 的初始化

#### 2.6.2 CAN 发送及接收结构体

在发送或接收报文时，需要往发送邮箱中写入报文信息或从接收 FIFO 中读取报文信息，利用STM32HAL 库的发送及接收结构体可以方便地完成这样的工作，它们的定义见代码清单 。代码清单 39‑2 CAN 发送及接收结构体

```
typedef struct
{
  uint32_t StdId;    /* 存储报文的标准标识符 11 位，0-0x7FF. */
  uint32_t ExtId;    /* 存储报文的扩展标识符 29 位，0-0x1FFFFFFF. */
  uint32_t IDE;     /* 存储 IDE 扩展标志 */
  uint32_t RTR;    /* 存储 RTR 远程帧标志 */
  uint32_t DLC;     /* 存储报文数据段的长度，0-8 */
  FunctionalState TransmitGlobalTime; 
} CAN_TxHeaderTypeDef;
typedef struct
{
  uint32_t StdId;    /* 存储报文的标准标识符 11 位，0-0x7FF. */
  uint32_t ExtId;    /* 存储报文的扩展标识符 29 位，0-0x1FFFFFFF. */
  uint32_t IDE;     /* 存储 IDE 扩展标志 */
  uint32_t RTR;      /* 存储 RTR 远程帧标志 */
  uint32_t DLC;     /* 存储报文数据段的长度，0-8 */
  uint32_t Timestamp; 
  uint32_t FilterMatchIndex; 
} CAN_RxHeaderTypeDef;
```

这些结构体成员, 说明如下：

(1) StdId

本成员存储的是报文的 11 位标准标识符，范围是 0-0x7FF。

(2) ExtId

本成员存储的是报文的 29 位扩展标识符，范围是 0-0x1FFFFFFF。ExtId 与 StdId 这两个成员根据下面的 IDE 位配置，只有一个是有效的。

(3) IDE

本成员存储的是扩展标志 IDE 位，当它的值为宏 CAN_ID_STD 时表示本报文是标准帧，使用 StdId 成员存储报文 ID；当它的值为宏 CAN_ID_EXT 时表示本报文是扩展帧，使用 ExtId 成员存储报文 ID。

(4) RTR

本成员存储的是报文类型标志 RTR 位，当它的值为宏 CAN_RTR_Data 时表示本报文是数据帧；当它的值为宏 CAN_RTR_Remote 时表示本报文是遥控帧，由于遥控帧没有数据段，所以当报文是遥控帧时，数据是无效的

(5) DLC

本成员存储的是数据帧数据段的长度，它的值的范围是 0-8，当报文是遥控帧时 DLC值为 0。

#### 2.6.3 CAN 筛选器结构体

CAN 的筛选器有多种工作模式，利用筛选器结构体可方便配置，它的定义见代码清单 。代码清单CAN 筛选器结构体

```c
typedef struct
{
  uint32_t FilterIdHigh;         /*CAN_FxR1 寄存器的高 16 位 */
  uint32_t FilterIdLow;         /*CAN_FxR1 寄存器的低 16 位 */
  uint32_t FilterMaskIdHigh;   /*CAN_FxR2 寄存器的高 16 位 */
  uint32_t FilterMaskIdLow;    /*CAN_FxR2 寄存器的低 16 位 */
  uint32_t FilterFIFOAssignment;  /* 设置经过筛选后数据存储到哪个接收 FIFO */
  uint32_t FilterBank;            /* 筛选器编号，范围 0-27，数据手册上说0-27是CAN1/CAN2共享，但是实测发现并不是这样，CAN1是0-13，CAN2是14-27 */
  uint32_t FilterMode;            /* 筛选器模式 */
  uint32_t FilterScale;           /* 设置筛选器的尺度 */
  uint32_t FilterActivation;      /* 是否使能本筛选器 */
  uint32_t SlaveStartFilterBank;  
} CAN_FilterTypeDef;
```

这些结构体成员都是“41.2.14 验收筛选器”小节介绍的内容，可对比阅读，各个结构体成员的介绍如下：

(1) FilterIdHigh

FilterIdHigh 成员用于存储要筛选的 ID，若筛选器工作在 32 位模式，它存储的是所筛选 ID 的高 16 位；若筛选器工作在 16 位模式，它存储的就是一个完整的要筛选的 ID。

(2) FilterIdLow

类似地，FilterIdLow 成员也是用于存储要筛选的 ID，若筛选器工作在 32 位模式，它存储的是所筛选 ID 的低 16 位；若筛选器工作在 16 位模式，它存储的就是一个完整的要筛选的 ID。

(3) FilterMaskIdHigh

FilterMaskIdHigh 存储的内容分两种情况，当筛选器工作在标识符列表模式时，它的功能与 FilterIdHigh 相同，都是存储要筛选的 ID；而当筛选器工作在掩码模式时，它存储的是 FilterIdHigh 成员对应的掩码，与 FilterIdLow 组成一组筛选器。

(4) FilterMaskIdLow

类似地， FilterMaskIdLow 存储的内容也分两种情况，当筛选器工作在标识符列表模式时，它的功能与 FilterIdLow 相同，都是存储要筛选的 ID；而当筛选器工作在掩码模式时，它存储的是 FilterIdLow 成员对应的掩码，与 FilterIdLow 组成一组筛选器。上面四个结构体的存储的内容很容易让人糊涂，请结合前面的图 39_0_15 和下面的表 39‑7 理解，如果还搞不清楚，再结合库函数 FilterInit 的源码来分析。

表不同模式下各结构体成员的内容

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmNdL64MA4icODeCbiaCAjspBvvVKlbiblLUYIibNZxibvvW4IXTqY6Dbibdicw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

对这些结构体成员赋值的时候，还要注意寄存器位的映射，即注意哪部分代表 STID，哪部分代表 EXID 以及 IDE、RTR 位。

(5) FilterFIFOAssignment

本成员用于设置当报文通过筛选器的匹配后，该报文会被存储到哪一个接收 FIFO，它的可选值为 FIFO0 或 FIFO1(宏 CAN_FILTER_FIFO0/1)。

(6) FilterBank

本成员用于设置筛选器的编号，即本过滤器结构体配置的是哪一组筛选器，CAN 一共有 28 个筛选器，所以它的可输入参数范围为 0-27。

(7) FilterMode

本 成 员 用 于 设 置 筛 选 器 的 工 作 模 式， 可 以 设 置 为 列 表 模 式 (宏CAN_FILTERMODE_IDLIST) 及掩码模式 (宏 CAN_FILTERMODE_IDMASK)。

(8) FilterScale

本成员用于设置筛选器的尺度，可以设置为 32 位长 (宏 CAN_FILTERSCALE_32BIT)及 16 位长 (宏 CAN_FILTERSCALE_16BIT)。

(9) FilterActivation

本成员用于设置是否激活这个筛选器 (宏 ENABLE/DISABLE)。

## 三. CAN Cubemx配置

我们通过问题来熟悉下cubemx配置，你熟悉了这些问题基本就知道怎么配置了！

问题：Parameter Settings分别都是设置什么的？ 答案：如图

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmrYIYFys9aDhTFbbMDmrogoFHDyuNsDZ3HLOOXTO1Bia4GQHvVFf3HeA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

#### 问题：怎么配置波特率呢？

**答案：**用我上面贴的工具(**CAN波特率计算 f103AHP1_36M  f407AHP1_42M  采样点软件有说明.rar**)直接配置,举两个个例子

**例子1：**我们要配置成500KHz,那么我们这样配置

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKm3ia1MpHicTVsBGSjKVhsXEl5foTpfuxHjx5B4icjsgiblIQ4z6ic96CBmDg/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmTlLZeetAFicRZRgYBn6ZiaHzKVDmrsze6A25iajU1IHySDf0cFUVmIbiaw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

我们用采集点为80%，所以BS1为4tq,BS2为2tq,分频系数为12，代进公式Fpclk1/((CAN_BS1+CAN_BS2+1)*CAN_Prescaler)=42M/(4+2+1)/12=500kHz

**例子2：**我们要配置成1M Hz,那么我们这样配置

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKm7dRIcBfoeZZQpzibAwOZaBdTkSibmy5O9jQNz70T9EIPKwhrpRxvHfyQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

我们用采集点为75%，所以BS1为3tq,BS2为2tq,分频系数为7，代进公式Fpclk1/((CAN_BS1+CAN_BS2+1)*CAN_Prescaler)=42M/(3+2+1)/7=1MHz

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmfOfx63CBgclUVhgJuqX6gLh7YknULgxqte4mS7TsNIZcl8Bia5jZf3Q/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

#### 问题：Basic Parameter分别是啥意思呢?

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmicAO0JDXYgialWyMZ0VwkibZeuCv7PyH4cCeVEg0RBeGPWP0Rs2h1MDCw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

Timer Triggered Communication Mode:否使用时间触发功能 (ENABLE/DISABLE)，时间触发功能在某些CAN 标准中会使用到。

Automatic Bus-Off Management:用于设置是否使用自动离线管理功能 (ENABLE/DISABLE)，使用自动离线管理可以在出错时离线后适时自动恢复，不需要软件干预。

Automatic Wake-Up Mode:用于设置是否使用自动唤醒功能 (ENABLE/DISABLE)，使能自动唤醒功能后它会在监测到总线活动后自动唤醒。

Automatic Retransmission:用于设置是否使用自动重传功能 (ENABLE/DISABLE)，使用自动重传功能时，会一直发送报文直到成功为止。

Receive Fifo Locked Mode:用于设置是否使用锁定接收 FIFO(ENABLE/DISABLE)，锁定接收 FIFO 后，若FIFO 溢出时会丢弃新数据，否则在 FIFO 溢出时以新数据覆盖旧数据。

Transmit Fifo Priority:用于设置发送报文的优先级判定方法 (ENABLE/DISABLE)，使能时，以报文存入发送邮箱的先后顺序来发送，否则按照报文 ID 的优先级来发送。配置完这些结构体成员后，我们调用库函数 HAL_CAN_Init 即可把这些参数写入到 CAN 控制寄存器中，实现 CAN 的初始化

#### 问题：为啥CAN分为RX0,RX1中断呢？

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmmzemBozpW2Dz87Wq6iamwDsgQZUrWwZHYRroJic80AbahhYB1yvoQFDw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

答案：STM32有2个3级深度的接收缓冲区：FIFO0和FIFO1，每个FIFO都可以存放3个完整的报文，它们完全由硬件来管理。如果是来自FIFO0的接收中断，则用CAN1_RX0_IRQn中断来处理。如果是来自FIFO1的接收中断，则用CAN1_RX1_IRQn中断来处理，如图：![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmfrwdx1H0WsxWwjHfJ5z4BoghdbZHO1E47poq7S87XZj0D7xMXu1VSQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

#### 问题：CAN SCE中断时什么？

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKm334kvEmvUv6mzL2ibyg5uk0YbxGAtwLvRpl73rDziaxg4NYfHZQBXGgA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

**答案：**status chanege error,错误和状态变化中断!

## 四.CAN分析工具的使用

下面我们会用到CAN分析工具，还是比较好用的，此部分使用作为自己使用

> https://www.zhcxgd.com/h-col-112.html

## 五. 实验

### 1.Normal模式测试500K 波特率（定时发送，轮询接收）

#### 1.1 CubeMx配置

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmiaoJN4XjgMXP7ecr4H9H63etBkILCibGZyfanHQxog0ofVDWV8nePDEg/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmowBXveKFxf6IIXmdN2wLrDCmicbh1t2JTWV59qFoX6qFsFxVA209W7g/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

#### 1.2 设置Filter过滤，我们只使能FIFO0，并且不过滤任何消息

```c
uint8_t bsp_can1_filter_config(void)
{
    CAN_FilterTypeDef filter = {0};
    filter.FilterActivation = ENABLE;
    filter.FilterMode = CAN_FILTERMODE_IDMASK;
    filter.FilterScale = CAN_FILTERSCALE_32BIT;
    filter.FilterBank = 0;
    filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    filter.FilterIdLow = 0;
    filter.FilterIdHigh = 0;
    filter.FilterMaskIdLow = 0;
    filter.FilterMaskIdHigh = 0;
    HAL_CAN_ConfigFilter(&hcan1, &filter);
    return BSP_CAN_OK;
}
```

#### 1.3 开启CAN（注意，默认Cubemx生成的代码并没有can start）

```c
HAL_CAN_Start(&hcan1);
```

#### 1.4 编写发送函数

我们开出了几个参数，id_type是扩展帧还是标准帧，basic_id标准帧ID(在标准帧中有效)，ex_id扩展帧ID(在扩展帧中有效)，data要发送的数据，data_len要发送的数据长度

```c
uint8_t bsp_can1_send_msg(uint32_t id_type,uint32_t basic_id,uint32_t ex_id,uint8_t *data,uint32_t data_len)
{
    uint8_t index = 0;
    uint32_t *msg_box;
 uint8_t send_buf[8] = {0};
    CAN_TxHeaderTypeDef send_msg_hdr;
    send_msg_hdr.StdId = basic_id;
    send_msg_hdr.ExtId = ex_id;
    send_msg_hdr.IDE = id_type;
    send_msg_hdr.RTR = CAN_RTR_DATA;
    send_msg_hdr.DLC = data_len;
 send_msg_hdr.TransmitGlobalTime = DISABLE;
 for(index = 0; index < data_len; index++)
          send_buf[index] = data[index];
 
    HAL_CAN_AddTxMessage(&hcan1,&send_msg_hdr,send_buf,msg_box);
    return BSP_CAN_OK;
}
```

我们在main函数中1s发送一帧，标准帧跟扩展帧交叉调用，代码如下：

```c
send_data[0]++;
send_data[1]++;
send_data[2]++;
send_data[3]++;
send_data[4]++;
send_data[5]++;
send_data[6]++;
send_data[7]++;
if(id_type_std == 1)
{
    bsp_can1_send_msg(CAN_ID_STD,1,2,send_data,8);
    id_type_std = 0;
}
else
{
    bsp_can1_send_msg(CAN_ID_EXT,1,2,send_data,8);
    id_type_std = 1;
}
HAL_Delay(1000);
```

我们通过CAN协议分析仪来抓下结果

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmngTWTkaIM06yHUOXkrA8oLT2gwMR3TcM9MFEt3ExBWZ9nfKoY1YMew/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

#### 1.5 编写轮询接收函数

```c
uint8_t bsp_can1_polling_recv_msg(uint32_t *basic_id,uint32_t *ex_id,uint8_t *data,uint32_t *data_len)
{
 uint8_t index = 0;
 uint8_t recv_data[8];
    CAN_RxHeaderTypeDef header;
 
    while (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) != 0)
    {
        if (__HAL_CAN_GET_FLAG(&hcan1, CAN_FLAG_FOV0) != RESET)
            printf("[CAN] FIFO0 overrun!\n");

        HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &header, recv_data);
        if(header.IDE == CAN_ID_STD)
        {
            printf("StdId ID:%d\n",header.StdId);
        }
        else
        {
            printf("ExtId ID:%d\n",header.ExtId);
        }
        printf("CAN IDE:0x%x\n",header.IDE);
        printf("CAN RTR:0x%x\n",header.RTR);
        printf("CAN DLC:0x%x\n",header.DLC);
        printf("RECV DATA:");
        for(index = 0; index < header.DLC; index++)
        {
            printf("0x%x ",recv_data[index]);
        }
        printf("\n");
    }
}
```

实验一总结：

1.没用调用HAL_CAN_Start(&hcan1);使能CAN

2.没有编写Filter函数，我开始自认为不设置就默认不过滤，现在看来是我想多了，其实想想也合理，你如果不过滤分配FIFO，STM32怎么决定把收到的放到哪个FIFO中

待提升：

1.目前只用到FIFO0，待把FIFO1使用起来2.Normal模式测试500K 波特率（定时发送，中断接收）

#### 2.1 CubeMx配置

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmb0S0hvlzGcjOlpcOk7BKhPQl22ObFDvJDo4L61znV3qlicTGn9PEmAQ/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

![图片](https://mmbiz.qpic.cn/mmbiz_png/PnO7BjBKUz9Qicq5B86HYqBZGoNEKunKmSK7iaYaK5sHW2s8TDOAPsLbmtm9ABPiaW1ficwMSzicgkDIHqygpY2Zs4Q/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

步骤2,3,4跟polling完全一致，我们来直接说下中断怎么用（主要是使能notifity就行了）

```c
static void MX_CAN1_Init(void)
{
  /* USER CODE BEGIN CAN1_Init 0 */
  /* USER CODE END CAN1_Init 0 */
  /* USER CODE BEGIN CAN1_Init 1 */
  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 12;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_4TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = ENABLE;
  hcan1.Init.AutoWakeUp = ENABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */
  bsp_can1_filter_config();
 HAL_CAN_Start(&hcan1);
 HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);
  /* USER CODE END CAN1_Init 2 */
}
```

下面我们来编写下中断函数

```c
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
 uint8_t index = 0;
 uint8_t recv_data[8];
      CAN_RxHeaderTypeDef header;
 
 HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &header, recv_data);
 if(header.IDE == CAN_ID_STD)
 {
          printf("StdId ID:%d\n",header.StdId);
 }
 else
 {
          printf("ExtId ID:%d\n",header.ExtId);
 }
 printf("CAN IDE:0x%x\n",header.IDE);
 printf("CAN RTR:0x%x\n",header.RTR);
 printf("CAN DLC:0x%x\n",header.DLC);
 printf("RECV DATA:");
 for(index = 0; index < header.DLC; index++)
 {
          printf("0x%x ",recv_data[index]);
 }
 printf("\n");
}
```

## 参考内容：

1.[野火EmbedFire]《STM32 HAL库开发实战指南——基于野火挑战者开发板》.pdf

2.STM32F4参考手册.pdf

3.CAN入门书.pdf