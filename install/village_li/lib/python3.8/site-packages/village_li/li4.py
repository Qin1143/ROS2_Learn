#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
# 1. 导入消息类型
from std_msgs.msg import String
from std_msgs.msg import UInt32
from village_interfaces.srv import BorrowMoney
#导入系统内置的图片消息类型
from sensor_msgs.msg import Image
#从村庄接口话题消息类中导入小说消息类型
from village_interfaces.msg import Novel


class WriterNode(Node):
    """
    创建一个李四节点，并在初始化时输出一个话
    """
    def __init__(self,name):
        super().__init__(name)
        self.get_logger().info("大家好，我是%s,我是一名作家！" % name)
        # 声明参数,参数名字，默认值
        self.declare_parameter("write_timer_period",5)
        # 2.创建并初始化发布者成员属性pubnovel
        # 共有三个参数，第一个是话题类型，第二个是话题名称，第三个是消息队列长度
        self.pub_novel = self.create_publisher(Novel,"sexy_girl", 10)
        self.borrow_server = self.create_service(BorrowMoney, "borrow_money", self.borrow_money_callback)

        #声明一个空的图像
        self.image = Image()
        # 开始获取图片
        self.create_subscription(Image,"image",self.recv_image_callback,10)

        #3. 编写发布逻辑
        # 创建定时器成员属性timer
        self.i = 0 # i 是个计数器，用来算章节编号的
        timer_period = 5  #每5s写一章节话
        self.timer = self.create_timer(timer_period, self.timer_callback)  #启动一个定时装置，每 1 s,调用一次time_callback函数

        # 账户钱的数量
        self.account = 70
        # 创建并初始化订阅者成员属性submoney
        self.sub_money = self.create_subscription(UInt32,"sexy_girl_money",self.recv_money_callback,10)

    def recv_image_callback(self,image):
        # self.get_logger().info('接收到图片“%s”' % image.data)
        self.image = image

    def timer_callback(self):
        """
        定时器回调函数
        """

        msg = Novel()
        msg.content = '第%d回:潋滟湖 %d 次偶遇胡艳娘' % (self.i, self.i)
        msg.image = self.image
        self.pub_novel.publish(msg)  #将小说内容发布出去
        self.get_logger().info('李四:我发布了艳娘传奇："%s"' % msg.content)    #打印一下发布的数据，供我们看
        self.get_logger().info('李四:并且为艳娘传奇配上了插图，长："%d"，宽：%d' % (int(msg.image.height),int(msg.image.width)))    #打印一下发布的插图尺寸，供我们看        
        self.i += 1 #章节编号+1
        
        # 回调之后更新回调周期
        timer_period = self.get_parameter('write_timer_period').get_parameter_value().integer_value
        # 更新回调周期
        self.timer.timer_period_ns = timer_period * (1000*1000*1000)

    def recv_money_callback(self,money):
        """
        4. 编写订阅回调处理逻辑
        """
        self.account += money.data
        self.get_logger().info('李四：我已经收到了%d的稿费' % self.account)

    def borrow_money_callback(self, request, response):
        """
        借钱回调函数
        参数:request 客户端请求对象，携带着来自客户端的数据
            response 服务端响应，返回服务端的处理结果
        返回值:response
        """
        self.get_logger().info("收到来自: %s 的借钱请求，目前账户内还有%d元" % (request.name, self.account))
        #根据李四借钱规则，借出去的钱不能多于自己所有钱的十分之一，不然就不借
        if request.money <= int(self.account*0.1):
            response.success = True
            response.money = request.money
            self.account = self.account - request.money
            self.get_logger().info("借钱成功，借出%d 元 ,目前账户余额%d 元" % (response.money,self.account))
        else:
            response.success = False
            response.money = 0
            self.get_logger().info("对不起兄弟，手头紧,不能借给你")
        return response



def main(args=None):
    """
    ros2运行该节点的入口函数
    1. 导入库文件
    2. 初始化客户端库
    3. 新建节点
    4. spin循环节点
    5. 关闭客户端库
    """
    rclpy.init(args=args) # 初始化rclpy
    node = WriterNode("li4")  # 新建一个节点
    rclpy.spin(node) # 保持节点运行，检测是否收到退出指令（Ctrl+C）
    rclpy.shutdown() # 关闭rclpy