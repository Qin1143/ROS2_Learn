// 引入必要的头文件
#include <inttypes.h> // 为整数类型定义了一些宏
#include <memory> // 提供std::shared_ptr等智能指针
#include "example_interfaces/action/fibonacci.hpp" // 引入Fibonacci action接口
#include "rclcpp/rclcpp.hpp" // ROS 2的C++客户端库
// TODO: 一旦rclcpp_action作为rclcpp的一部分，就移除下面这行
#include "rclcpp_action/rclcpp_action.hpp" // 提供ROS 2 action服务器和客户端的支持

// 定义MinimalActionServer类，继承自rclcpp::Node
class MinimalActionServer : public rclcpp::Node
{
public:
  // 使用Fibonacci action类型和对应的GoalHandle类型
  using Fibonacci = example_interfaces::action::Fibonacci;
  using GoalHandleFibonacci = rclcpp_action::ServerGoalHandle<Fibonacci>;

  // 构造函数，可选地接受NodeOptions
  explicit MinimalActionServer(const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
  : Node("minimal_action_server", options)
  {
    using namespace std::placeholders; // 用于std::bind中的占位符

    // 创建action服务器
    this->action_server_ = rclcpp_action::create_server<Fibonacci>(
      this->get_node_base_interface(),
      this->get_node_clock_interface(),
      this->get_node_logging_interface(),
      this->get_node_waitables_interface(),
      "fibonacci", // Action名称
      std::bind(&MinimalActionServer::handle_goal, this, _1, _2), // 处理目标请求的回调
      std::bind(&MinimalActionServer::handle_cancel, this, _1), // 处理取消请求的回调
      std::bind(&MinimalActionServer::handle_accepted, this, _1)); // 处理接受目标的回调
  }

private:
  // Action服务器的智能指针
  rclcpp_action::Server<Fibonacci>::SharedPtr action_server_;

  // 处理目标请求的函数
  rclcpp_action::GoalResponse handle_goal(
    const rclcpp_action::GoalUUID & uuid,
    std::shared_ptr<const Fibonacci::Goal> goal)
  {
    RCLCPP_INFO(this->get_logger(), "Received goal request with order %d", goal->order);
    (void)uuid; // uuid未使用，避免编译器警告
    // 如果请求的序列大于9000，拒绝它
    if (goal->order > 9000) {
      return rclcpp_action::GoalResponse::REJECT;
    }
    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
  }

  // 处理取消请求的函数
  rclcpp_action::CancelResponse handle_cancel(
    const std::shared_ptr<GoalHandleFibonacci> goal_handle)
  {
    RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
    (void)goal_handle; // goal_handle未使用，避免编译器警告
    return rclcpp_action::CancelResponse::ACCEPT;
  }

  // 执行目标的函数
  void execute(const std::shared_ptr<GoalHandleFibonacci> goal_handle)
  {
    RCLCPP_INFO(this->get_logger(), "Executing goal");
    rclcpp::Rate loop_rate(1); // 设置循环频率为1Hz
    const auto goal = goal_handle->get_goal();
    auto feedback = std::make_shared<Fibonacci::Feedback>();
    auto & sequence = feedback->sequence;
    sequence.push_back(0); // 初始化斐波那契序列
    sequence.push_back(1);

    auto result = std::make_shared<Fibonacci::Result>();

    // 生成斐波那契序列
    for (int i = 1; (i < goal->order) && rclcpp::ok(); ++i) {
      if (goal_handle->is_canceling()) { // 检查是否有取消请求
        result->sequence = sequence;
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Goal Canceled");
        return;
      }
      sequence.push_back(sequence[i] + sequence[i - 1]); // 更新序列
      goal_handle->publish_feedback(feedback); // 发布反馈
      RCLCPP_INFO(this->get_logger(), "Publish Feedback");

      loop_rate.sleep();
    }

    if (rclcpp::ok()) { // 检查目标是否完成
      result->sequence = sequence;
      goal_handle->succeed(result);
      RCLCPP_INFO(this->get_logger(), "Goal Succeeded");
    }
  }

  // 处理接受目标的函数
  void handle_accepted(const std::shared_ptr<GoalHandleFibonacci> goal_handle)
  {
    using namespace std::placeholders;
    // 为避免阻塞执行器，需要快速返回，因此在新线程中执行
    std::thread{std::bind(&MinimalActionServer::execute, this, _1), goal_handle}.detach();
  }
};  // class MinimalActionServer

// 主函数
int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv); // 初始化ROS 2

  auto action_server = std::make_shared<MinimalActionServer>(); // 创建Action服务器实例

  rclcpp::spin(action_server); // 进入循环，等待事件发生

  rclcpp::shutdown(); // 关闭ROS 2
  return 0;
}