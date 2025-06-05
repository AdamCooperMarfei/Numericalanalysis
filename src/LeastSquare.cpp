#include <iostream>
#include <eigen3/Eigen/Dense>
#include <vector>

class LeastSquaresSolver {
public:
    // 构造函数
    LeastSquaresSolver() = default;

    // 设置数据: 输入特征矩阵X（每行是一个样本），标签向量y
    void setData(const Eigen::MatrixXd& X, const Eigen::VectorXd& y) {
        int n_samples = X.rows();
        int n_features = X.cols();

        // 构建加1列的设计矩阵（考虑偏置项）
        A_.resize(n_samples, n_features + 1);
        A_.block(0, 0, n_samples, n_features) = X;
        A_.col(n_features) = Eigen::VectorXd::Ones(n_samples);

        b_ = y;
    }

    // 计算最小二乘解
    void solve() {
        // Solve (A^T * A) * x = A^T * b
        x_ = (A_.transpose() * A_).ldlt().solve(A_.transpose() * b_);
    }

    // 预测新的数据
    Eigen::VectorXd predict(const Eigen::MatrixXd& X_new) const {
        int n_samples = X_new.rows();
        int n_features = X_new.cols();

        Eigen::MatrixXd A_new(n_samples, n_features + 1);
        A_new.block(0, 0, n_samples, n_features) = X_new;
        A_new.col(n_features) = Eigen::VectorXd::Ones(n_samples);

        return A_new * x_;
    }

    // 获取权重和偏置
    Eigen::VectorXd getCoefficients() const {
        return x_;
    }

private:
    Eigen::MatrixXd A_; // 增广矩阵
    Eigen::VectorXd b_; // 观测值
    Eigen::VectorXd x_; // 解向量 (包含权重和偏置)
};

// 示例程序
int main() {
    // 准备训练数据
    Eigen::MatrixXd X(5, 2);
    X << 1.0, 2.0,
         2.0, 0.5,
         3.0, 2.5,
         4.0, 4.0,
         5.0, 3.5;
    
    Eigen::VectorXd y(5);
    y << 2.5, 2.0, 4.5, 6.0, 6.5;

    // 创建并使用最小二乘求解器
    LeastSquaresSolver solver;
    solver.setData(X, y);
    solver.solve();

    Eigen::VectorXd coeffs = solver.getCoefficients();
    std::cout << "模型参数:" << std::endl;
    std::cout << "w1 = " << coeffs(0) << std::endl;
    std::cout << "w2 = " << coeffs(1) << std::endl;
    std::cout << "b  = " << coeffs(2) << std::endl;

    // 测试预测
    Eigen::MatrixXd X_test(2, 2);
    X_test << 6.0, 5.0,
              2.5, 1.5;
    
    Eigen::VectorXd y_pred = solver.predict(X_test);
    std::cout << "预测结果:" << std::endl;
    std::cout << y_pred << std::endl;

    return 0;
}