# Breastfeeding_clock
【此文档暂时记录开发过程】

 哺乳记录器，记录宝宝的哺乳时间，大小便时间、补水时间，以及距离上次相关事件的时间间隔。

2018年3月29日23:33
 使用储物柜的源代码，调通PA0-PA7作为12864的数据线；增加资料，主要是红外感应的资料；修改引脚分配表；DXP文件定义一些引脚。

2018年3月31日23:00
  关于电源这方面，之前没有做过电源的升压电路，也为安全考虑不敢轻易尝试。所以在淘宝购买了现成的充电宝的升压电路板，有过压过流保护，可以放心使用。
连接稳压电源时USB_5V负责给主板供电、给电池充电；
没有连接外部电源时，开关拨到电池供电端，此时就由电池给主板提供5V电源。
  
2018年4月1日（补）
  元件选择封装，错误检查，PCB布局。

2018年4月2日23:30
  修改部分元器件封装，修改原理图（将一些不确定，不需要插座的元件做成PIN1、空置引脚全部引出）
PB2(BOOT1)接地。
PCB电源布线、12864布线。

2018年4月17日20：00
  前面这段时间确定了PCB，并且打了样板。在老家焊接并初步调试完成。
之前准备采用热释电红外作为感应模组，通过对手头现成的热释电红外模块（BISS0001）的测试发现其感应范围太大，不适合做近距离的感应。
经同事点拨，红外对管似乎更适合我的需求。
使用明哥的寻迹小车上的红外对管测试之后发现确实能很好的满足我的需求，遂淘宝下单买了两个红外对管模块--抱愧一对红外对管，一个LM393比较器。


 
