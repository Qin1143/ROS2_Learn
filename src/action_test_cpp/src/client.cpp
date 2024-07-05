// 包含必要的头文件
#include <inttypes.h> // 为了使用整型定义
#include <memory> // 为了使用智能指针
#include <string> // 为了使用字符串
#include <iostream> // 为了输入输出操作
#include "example_interfaces/action/fibonacci.hpp" // 包含Fibonacci动作接口
#include "rclcpp/rclcpp.hpp" // 包含ROS2 C++客户端库的核心功能
// TODO: 一旦rclcpp_action成为rclcpp的一部分，就移除下面的包含
#include "rclcpp_action/rclcpp_action.hpp" // 包含ROS2动作客户端功能

// 定义MinimalActionClient类，继承自rclcpp::Node
class MinimalActionClient : public rclcpp::Node
{
public:
  // 使用Fibonacci动作和目标句柄的别名，简化代码
  using Fibonacci = example_interfaces::action::Fibonacci;
  using GoalHandleFibonacci = rclcpp_action::ClientGoalHandle<Fibonacci>;

  // 构造函数，可选地接受节点选项
  explicit MinimalActionClient(const rclcpp::NodeOptions & node_options = rclcpp::NodeOptions())
  : Node("minimal_action_client", node_options), goal_done_(false)
  {
    // 创建Fibonacci动作客户端
    this->client_ptr_ = rclcpp_action::create_client<Fibonacci>(
      this->get_node_base_interface(),
      this->get_node_graph_interface(),
      this->get_node_logging_interface(),
      this->get_node_waitables_interface(),
      "fibonacci");

    // 创建定时器，每500毫秒尝试发送目标
    this->timer_ = this->create_wall_timer(
      std::chrono::milliseconds(500),
      std::bind(&MinimalActionClient::send_goal, this));
  }

  // 返回目标是否完成
  bool is_goal_done() const
  {
    return this->goal_done_;
  }

  // 发送目标到动作服务器
  void send_goal()
  {
    using namespace std::placeholders;

    // 取消定时器以避免重复发送目标
    this->timer_->cancel();

    // 标记目标为未完成
    this->goal_done_ = false;

    // 检查动作客户端是否已初始化
    if (!this->client_ptr_) {
      RCLCPP_ERROR(this->get_logger(), "Action client not initialized");
    }

    // 等待动作服务器变得可用
    if (!this->client_ptr_->wait_for_action_server(std::chrono::seconds(10))) {
      RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
      this->goal_done_ = true;
      return;
    }

    // 创建并设置目标消息
    auto goal_msg = Fibonacci::Goal();
    goal_msg.order = 10; // 设置Fibonacci序列的长度

    RCLCPP_INFO(this->get_logger(), "Sending goal");

    // 设置发送目标的选项
    auto send_goal_options = rclcpp_action::Client<Fibonacci>::SendGoalOptions();
    send_goal_options.goal_response_callback =
      std::bind(&MinimalActionClient::goal_response_callback, this, _1);
    send_goal_options.feedback_callback =
      std::bind(&MinimalActionClient::feedback_callback, this, _1, _2);
    send_goal_options.result_callback =
      std::bind(&MinimalActionClient::result_callback, this, _1);
    // 异步发送目标
    auto goal_handle_future = this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
  }

private:
  // 成员变量
  rclcpp_action::Client<Fibonacci>::SharedPtr client_ptr_; // 动作客户端指针
  rclcpp::TimerBase::SharedPtr timer_; // 定时器
  bool goal_done_; // 目标完成标志

  // 目标响应回调
  void goal_response_callback(std::shared_future<GoalHandleFibonacci::SharedPtr> future)
  {
    auto goal_handle = future.get();
    if (!goal_handle) {
      RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
    } else {
      RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
    }
  }

  // 反馈回调
  void feedback_callback(
    GoalHandleFibonacci::SharedPtr,
    const std::shared_ptr<const Fibonacci::Feedback> feedback)
  {
    RCLCPP_INFO(
      this->get_logger(),
      "Next number in sequence received: %" PRId32,
      feedback->sequence.back());
  }

  // 结果回调
  void result_callback(const GoalHandleFibonacci::WrappedResult & result)
  {
    this->goal_done_ = true; // 标记目标为完成
    switch (result.code) {
      case rclcpp_action::ResultCode::SUCCEEDED:
        break;
      case rclcpp_action::ResultCode::ABORTED:
        RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
        return;
      case rclcpp_action::ResultCode::CANCELED:
        RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
        return;
      default:
        RCLCPP_ERROR(this->get_logger(), "Unknown result code");
        return;
    }

    // 打印结果
    RCLCPP_INFO(this->get_logger(), "Result received");
    for (auto number : result.result->sequence) {
      RCLCPP_INFO(this->get_logger(), "%" PRId32, number);
    }
  }
};  // class MinimalActionClient 结束

// 主函数
int main(int argc, char ** argv)
{
  // 初始化ROS2
  rclcpp::init(argc, argv);
  // 创建动作客户端对象
  auto action_client = std::make_shared<MinimalActionClient>();

  // 循环直到目标完成
  while (!action_client->is_goal_done()) {
    rclcpp::spin_some(action_client);
  }

  // 关闭ROS2
  rclcpp::shutdown();
  return 0;
}