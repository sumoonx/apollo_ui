## 2016/07/10
1. 解决AnchorItem不能打印anchor ID的问题：需要重新设置QPen的pixSize；
2. 制定FPGA串口输出的帧格式：F + ledi, rssi, dcnt + F，以十六进制F开头并以F结束。发现串口的数据位只能设置5,6,7,8而不能再多；
3. 解决Linux下串口的权限问题：在/etc/udev/下创建新的规则文件70-ttyusb.rules，并在文件中加入一行：KERNEL=="ttyUSB[0-9]*",MODE="0666"，注意上述代码中的两个=号，拔掉串口再插上即可；
4. 增加从串口读取数据的功能：使用QSerialPort**定时**异步读取串口输入；
5. 增加在Qt程序中显示rssi值的功能：使用QSerialPort**定时**异步读取串口输入，然后在工作线程中运行RssiWorker，得到anchor值后传递给AnchorItem进行显示。其中，修改了Anchor类，加入rssi值，相应的也需要修改AnchorItem，在刷新rssi显示时，发现QGraphicsItem的update方法并不即时刷新，而是进入操作队列，因此只有最近的一次update才有效，解决方法是调用scene的update方法。为了加快update的速度，建议指定QRectF进行update。在显示过程中，发现FPGA程序中的BUG，原因是所有的rssi都公用一个FIFO进行窗口平均，该窗口平均的设计初衷是使得数码管显示较为平滑。解决方法是将窗口平均前的数据直接输出。

下阶段工作：添加算法模块，在MainWindow中新开启工作线程，然后创建算法模块（类似Anroid中的Runable接口）。

## 2016/07/11
1. 在linux下安装FGPA下载工具：安装Labtools，记住source安装目录下的setting64.sh到/etc/profile文件中。主要的问题在于USB Cable驱动的安装。第一步是安装usb-driver：git clone git://git.zerfleddert.de/usb-driver，然后sudo make，当然需要先安装编译环境sudo apt-get install gitk git-gui libusb-dev build-essential libc6-dev-i386 fxload。然后把生成的usb-driver.so文件cp到安装目录下，最后还需要在profile文件中加入export LD_PRELOAD=/yourpath/libusb-driver.so。如果还是不能工作，需要follow如下的步骤：将安装目录下的xusbdfwu.rules文件cp到/etc/udev/rules.d/下，然后sed -i -e 's/TEMPNODE/tempnode/' -e 's/SYSFS/ATTRS/g' -e 's/BUS/SUBSYSTEMS/' /etc/udev/rules.d/xusbdfw.rules。即修改三个对应的字符串。确定安装了fxload工具，然后将安装目录下的xusb*.hex文件全都cp到/usr/shar/目录下，重新启动udev，sudo /etc/init.d/udev restart，再重新插拔一下cable即可。使用lsusb指令查看usb状态，如果显示位03fd:0008说明已经可以用了。
2. Windows到linux的文件传输，使用SecureCRT软件，使用rz和sz命令，只需要在进入SecreCRT后输入rz选择文件即可，文件会被自动传输到用户主目录下。

