# 可见光室内定位QT端程序代码

本程序需使用QT5环境。

为了实现不同的定位算法，需要继承PostioningWorker类，并实现其纯虚函数doWork，其入参是Anchor类，该类是一个值类，包含了锚节点的位置坐标以及接收端在该节点上获得的RSSI值，有了这些值就可以运行定位算法。最终的定位结果通过emit resultReady信号发送给主程序供显示。 	

一般的三维定位实现在ThreeDimenWorker中，而运动物体的定位实现在MovingWorker中。

test ssh key
