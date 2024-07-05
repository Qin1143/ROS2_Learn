#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/u_int32.hpp"
#include "village_interfaces/srv/sell_novel.hpp"
#include "village_interfaces/msg/novel.hpp"
#include <queue> // 引入容器


using std::placeholders::_1; // 使用std::placeholders::_1; 代替占位符
using std::placeholders::_2;
// 创建一个小说章节队列
std::queue<std::string>  novels_queue;

/*
    创建一个类节点，名字叫做SingleDogNode,继承自Node.
*/
// 关键字  新类名称  ：表示继承关系  继承的类  基类名称
class SingleDogNode : public rclcpp::Node
{

// 访问修饰符，private表示下面的成员变量和函数只能在类内部访问
public:
    // 构造函数,有一个参数为节点名称
    SingleDogNode(std::string name) : Node(name) // 接受一个 std::string 类型的参数 name，并将这个参数传递给基类 Node 的构造函数
    {
        // 打印一句自我介绍
        // this是一个指针，指向当前对象的实例
        RCLCPP_INFO(this->get_logger(), "大家好，我是单身狗%s.", name.c_str());
        // 创建一个订阅者来订阅李四写的小说，通过名字sexy_girl
        sub_novel = this->create_subscription<village_interfaces::msg::Novel>("sexy_girl", 10, std::bind(&SingleDogNode::topic_callback, this, _1));
        // 创建发布者
        pub_money = this->create_publisher<std_msgs::msg::UInt32>("sexy_girl_money", 10);
        // 实例化create_callback_group类
        callback_group_service_ = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
        // 实例化服务端
        // 实例化卖二手书的服务
        server_ = this->create_service<village_interfaces::srv::SellNovel>("sell_novel",
                                    std::bind(&SingleDogNode::sell_book_callback,this,_1,_2),
                                    rmw_qos_profile_services_default,
                                    callback_group_service_);
        //声明参数
        this->declare_parameter<std::int32_t>("novel_price", novel_price);
    }

private:
    //声明一下书的单价
    unsigned int novel_price = 1;

    // 声明一个服务回调组
    rclcpp::CallbackGroup::SharedPtr callback_group_service_;
    // 创建一个小说章节队列
    std::queue<std::string>  novels_queue;
    // 声明一个服务端
    rclcpp::Service<village_interfaces::srv::SellNovel>::SharedPtr server_;

    // 声明一个订阅者（成员变量）,用于订阅小说
    rclcpp::Subscription<village_interfaces::msg::Novel>::SharedPtr sub_novel;

    // 声明一个发布者（成员变量）,用于给李四钱
    rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr pub_money;

    // 收到话题数据的回调函数
    void topic_callback(const village_interfaces::msg::Novel::SharedPtr msg)
    {
        // 新建一张人民币
        std_msgs::msg::UInt32 money;
        money.data = 10;

        // 发送人民币给李四
        pub_money->publish(money);
        // RCLCPP_INFO(this->get_logger(), "王二：我收到了：'%s' ，并给了李四：%d 元的稿费", msg->data.c_str(),money.data);
        RCLCPP_INFO(this->get_logger(), "收到的小说内容: '%s'", msg->content.c_str());

        //将小说放入novels_queue中
        novels_queue.push(msg->content);
    };

    // 声明一个回调函数，当收到买书请求时调用该函数，用于处理数据
    // 回调函数结束时，response对象会被自动发送给客户端
    void sell_book_callback(const village_interfaces::srv::SellNovel::Request::SharedPtr request,
            const village_interfaces::srv::SellNovel::Response::SharedPtr response)
    {
        RCLCPP_INFO(this->get_logger(), "收到一个买书请求，一共给了%d钱",request->money);
        //更新参数
        this->get_parameter("novel_price",novel_price);
        unsigned int novelsNum = int( request->money / novel_price ); //应给小说数量，一块钱一章

        //判断当前书库里书的数量是否满足张三要买的数量，不够则进入等待函数
        if(novels_queue.size()<novelsNum)
        {
            RCLCPP_INFO(this->get_logger(), "当前艳娘传奇章节存量为%d：不能满足需求,开始等待",novels_queue.size());

            // 设置rate周期为1s，代表1s检查一次
            rclcpp::Rate loop_rate(1);

            //当书库里小说数量小于请求数量时一直循环
            while (novels_queue.size()<novelsNum)
            {
                //判断系统是否还在运行
                if(!rclcpp::ok())
                {
                    RCLCPP_ERROR(this->get_logger(), "程序被终止了");
                    return ;
                }
                //打印一下当前的章节数量和缺少的数量
                RCLCPP_INFO(this->get_logger(), "等待中，目前已有%d章，还差%d章",novels_queue.size(),novelsNum-novels_queue.size());

                //rate.sleep()让整个循环1s运行一次
                loop_rate.sleep();
            }
        }
        // 章节数量满足需求了
        RCLCPP_INFO(this->get_logger(), "当前艳娘传奇章节存量为%d：已经满足需求",novels_queue.size());

        //一本本把书取出来，放进请求响应对象response中
        for(unsigned int i =0 ;i<novelsNum;i++)
        {
            response->novels.push_back(novels_queue.front());
            novels_queue.pop();
        }
    }

};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*产生一个Wang2的节点*/
    auto node = std::make_shared<SingleDogNode>("wang2");
    /* 运行节点，并检测退出信号*/
    rclcpp::executors::MultiThreadedExecutor exector;
    exector.add_node(node);
    exector.spin();
    rclcpp::shutdown();
    return 0;
}