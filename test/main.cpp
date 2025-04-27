#include <iostream>
#include <vector>
#include <cmath>
#include <functional>

// 示例：这里是你要测试的数值分析方法，比如数值积分
double numericalIntegration(const std::function<double(double)> &func, double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (func(a) + func(b));
    for (int i = 1; i < n; ++i) {
        sum += func(a + i * h);
    }
    return sum * h;
}

// 解析解（用于验证）
double exactIntegralOfSin(double a, double b) {
    return -cos(b) + cos(a);
}

int main() {
    std::cout << "数值分析测试程序\n";
    std::cout << "请选择功能：\n";
    std::cout << "1. 数值积分测试\n";
    std::cout << "输入选择：";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        double a, b;
        int n;
        std::cout << "请输入积分下限 a: ";
        std::cin >> a;
        std::cout << "请输入积分上限 b: ";
        std::cin >> b;
        std::cout << "请输入划分区间数量 n: ";
        std::cin >> n;

        // 测试函数，这里用 sin(x) 演示
        auto func = [](double x) { return sin(x); };

        double numericalResult = numericalIntegration(func, a, b, n);
        double exactResult = exactIntegralOfSin(a, b);
        double error = std::abs(numericalResult - exactResult);

        std::cout << "\n数值积分结果: " << numericalResult << "\n";
        std::cout << "解析解结果:   " << exactResult << "\n";
        std::cout << "误差:         " << error << "\n";
    } else {
        std::cout << "未实现的功能。\n";
    }

    return 0;
}