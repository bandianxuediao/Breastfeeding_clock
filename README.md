# Breastfeeding_clock
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

