# Breastfeeding_clock<br/>
[开发过程记录](https://github.com/bandianxuediao/Breastfeeding_clock/blob/master/project_process.md)<br/>
详细的开发过程请点击上面的链接，或者直接访问project_process.md<br/>
更丰富的内容请访问我的个人网站[文禾每](http://www.wenhemei.com)<br/>
哺乳记录器，记录宝宝的哺乳时间，大小便时间、补水时间，以及距离上次相关事件的时间间隔。<br/>

## 项目背景
“丁酉年 冬月 癸巳日 卯时，爱妻诞下吾儿，重斤七整，性温良，状安详。及彼时新年初阳将醒，万物复苏。”这是我在2018年1月1日宝宝出生当天发表的朋友圈，而后妻子便开始了她照顾宝宝的忙碌生活。<br/>
数日之后，妻子提议：能不能做个软件来方便记录宝宝大小便和哺乳的时间。<br/>
本来想着只做一个android应用，方便随时使用手机来做记录、查看历史。后面我又觉得如果只做一个android应用的话之后就会被忘掉，随着时间的流逝什么也留不下来。干脆自己做一个实物的吧，于是便有了这个东西。<br/>
没有合适的工具，所有的隼都是使用雕刻刀一刀一刀刻出来的（还好当时买了较软的松木板，否则就不仅仅只是几个刀口几个水泡的事儿了）。<br/>
**通过这件事情算是真正的从心底里承认了一句话“不能随便评判别人的工作难易程度”。在预言阶段我仅仅是想拿几块木板用胶水粘起来，或者用钉子钉起来；采购物料期间看到淘宝推荐的雕刻刀，心想何不来几个卯榫，而且看起来也很简单。<br/>
实施阶段在我调整新打的PCB的时候我还在想着做个盒子也就一天的工作量。对，不出你们所料，做这个木盒子比画板子+写代码用的时间还长，而且还是如此的~不好看，"(￣▽￣)"""。<br/>**
从此项目的GitHub推进流程文档可以看出，项目建立时间是3月28日。中间还插入了其他的事情，不过总算是初步完成了。具体的项目推进流程可以在GitHub查看我的project_process.md文档。<br/>
## 项目介绍
简单介绍一下操作：<br/>
开机进入主界面后按下左按键进入项目列表，项目列表列出（哺乳、补水、小便、大便）项目；按上下键选择需要记录或查看的项目，按左键进入选中项目列表；列表中详细列出一共记录了多少条记录，距离上次记录过去了多少小时，按上下键翻页列表，按左按键增加一条当前时间的新记录（每个项目都有超时时间，在超时时间之内不允许再次存储此项目）。<br/>
主界面按下右按键可以进入时间设置的菜单，此处有时钟设置功能。同样是按上下键调整时间。<br/>
该记录器使用6000ma电池供电，红外对管检测物体靠近会点亮屏幕2分钟，其他任何按键均能触发1分钟倒计时重载。<br/>
## 硬件概述
硬件上面倒没什么复杂的：主控芯片使用的是STM32F103C8T6；12864的主控是ST7920；存储器使用了AT24CM01（1M位的EEPROM）；红外感应使用的是红外对管+LM393比较器。<br/>
### ST7920主控的12864<br/>
我这块12864不知道怎么回事，屏幕刷新几次就会出现乱码。之前用的同一批屏幕都没有这种情况，因为只剩下了一块，就只能先勉强用着。网上说可能驱动能力不足，于是加了上拉电阻4.7k-10k均没有效果；也有说时序不对，我是用逻辑分析仪抓的波形是没问题的；也有说在写屏幕的数据时没有控制好数据长度，这一条我还是有点赞同的，查了很久也没找到能出问题的地方，后边的项目结束后还的回头过来再解决一下。<br/>
原本怀疑的电源经过测试已经排除。  
乱码问题已经解决，是我之前已经遇到的但是却没引起我注意的一个bug。查出来之后才恍然大悟，我在RTC秒中断里面调用了屏幕刷新函数，而屏幕刷新函数里面有延时。所以**中断里面一定不能有延时**
### EEPROM的空间分配<br/>
#define INDEX_ADDR_LACTATION     10//哺乳索引存储地址<br/>
#define INDEX_ADDR_DRINK     20//补水索引存储地址<br/>
#define INDEX_ADDR_SHIT      30//大便索引存储地址<br/>
#define INDEX_ADDR_URINATE       40//小便索引存储地址<br/>
#define BASE_ADDR_LACTATION     100//哺乳存储的起始地址<br/>
#define BASE_ADDR_DRINK     30100//补水存储的起始地址<br/>
#define BASE_ADDR_SHIT      60100//大便存储的起始地址<br/>
#define BASE_ADDR_URINATE       90100//小便存储的起始地址<br/>
我的存储信息每条占用6个字节，假设每个项目每天存储6条，能够一直使用833天。<br/>

### 红外感应<br/>
红外这块初步设计时准备使用热释电来做的，调试过程中发现热释电的感应范围太大了，远远超过了我的需求。经过吴哥的提点，更换热释电为对管。直接淘宝5块钱包邮买了两个红外对管+LM393的模块，上机测试后完全符合我的预期效果，只是太阳光也对这东西有影响。<br/>

做板子的时候几个地方都是板子回来以后后期处理的，这些问题点我会在下一版本中修复。<br/>
V2完美版正在开发中……<br/>






