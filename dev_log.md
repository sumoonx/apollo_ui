## 2016/07/10
1. 解决AnchorItem不能打印anchor ID的问题：需要重新设置QPen的pixSize；
2. 制定FPGA串口输出的帧格式：F + ledi, rssi, dcnt + F，以十六进制F开头并以F结束。发现串口的数据位只能设置5,6,7,8而不能再多；
3. 解决Linux下串口的权限问题：在/etc/udev/下创建新的规则文件70-ttyusb.rules，并在文件中加入一行：KERNEL=="ttyUSB[0-9]*",MODE="0666"，注意上述代码中的两个=号，拔掉串口再插上即可；
4. 增加从串口读取数据的功能：使用QSerialPort**定时**异步读取串口输入；
5. 增加在Qt程序中显示rssi值的功能：使用QSerialPort**定时**异步读取串口输入，然后在工作线程中运行RssiWorker，得到anchor值后传递给AnchorItem进行显示。其中，修改了Anchor类，加入rssi值，相应的也需要修改AnchorItem，在刷新rssi显示时，发现QGraphicsItem的update方法并不即时刷新，而是进入操作队列，因此只有最近的一次update才有效，解决方法是调用scene的update方法。为了加快update的速度，建议指定QRectF进行update。在显示过程中，发现FPGA程序中的BUG，原因是所有的rssi都公用一个FIFO进行窗口平均，该窗口平均的设计初衷是使得数码管显示较为平滑。解决方法是将窗口平均前的数据直接输出。

下阶段工作：添加算法模块，在MainWindow中新开启工作线程，然后创建算法模块（类似Anroid中的Runable接口）。