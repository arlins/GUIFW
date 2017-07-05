## GUIFW是什么

GUIFW是一个基于GDI+的DirectUI皮肤引擎，基于这个皮肤引擎，你可以定制开发windows平台上软件的UI

GUIFW只实现了基本框架，目前还很粗糙，存在性能以及控件支持不完善等问题，因为采用GDI+，性能会低一些，主流的皮肤引擎，例如Qt和DuiLib都是基于GDI绘制，如果真正要投入到项目当中使用，需要将GDI+改成GDI。

因为精力有限，笔者并不打算继续维护GUIFW，如果需要使用该框架请自行做相应的支持，如果有疑问可以提Issues给我

基于目前GUIFW的现状，个人建议是在实现安装包的时候使用GUIFW，如果需要在项目当中使用皮肤引擎，笔者强烈建议基于Qt写一套皮肤引擎，基于Qt笔者写了一套皮肤引擎，但由于保密原因，该皮肤引擎不能开源，如果你实现皮肤引擎遇到问题，也欢迎提Issues给我。

## 框架简介

下图是GUIFW的框架图，其中底层是core模块，用于为上层和外部提供最基本的支持，基于core模块可以扩展各种各样的控件，对话框等，最终形成一个完整的皮肤库

![](https://github.com/arlins/GUIFW/blob/master/support-files/5.png)

1: xmlui主要实现了动态创建功能

2: layout实现了对GuiFrameWindow里面所有的GuiWidget的逻辑排版，支持HBox和VBox

3: application是整个程序的入口，程序所有消息都经过这里，再派发给相应的窗口

4: skinmanager实现换肤功能以及换肤广播工作

5: window是所有窗口的基类，也即GuiFrameWindow，GuiframeWindow管理着所有的GuiWidget，负责将绘制以及事件派发给相应的GuiWidget等工作

6: widget是每个窗口里面最基本的元素，也即GuiWidget，一个窗口的界面由若干个widget组成，所有的控件都由它派生，整个界面数据结构是由一颗每个节点是widget组成的树。

7: painter跟窗口有关，每个窗口都有一个painter，在需要绘制的时候将painter传给需要重绘区域里面的所有widget，GUIFW里面采用的绘图引擎是gdi+。实际上painter就是封装了对一个窗口相关的Bitmap的绘图操作，所有的widget都在这张bitmap上面画图，最终绘制出来一个窗口就是一张图。

8: eventdispatcher是事件派发者，包括application将事件派发给所有的窗口以及窗口派发事件给需要响应的widget两部分

## 详细了解

http://blog.csdn.net/sllins/article/details/38354493

## 如何编译

clone工程之后直接打开`guifw.sln`编译即可，注意启动工程需要设置为 `app`

需要使用VS2008或者更高版本编译


## 支持我

如果GUIFW能帮到你并且你愿意，欢迎对我支持

### 支付宝扫码
<img src="https://github.com/arlins/Personal/blob/master/ali-pay.jpg" alt="支付宝扫码" width="300" height="300">




