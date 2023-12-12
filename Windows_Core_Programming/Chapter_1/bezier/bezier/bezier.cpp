// bezier.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
#include <iostream>
#include <cmath>

// 定义已知数据
const double xa = 0.6; // 替换为A点的x坐标
//const double ya =  // 替换为A点的y坐标
const double a_x = 0 ;// 替换为对应的控制点的x坐标
const double a_y = 0 ;// 替换为对应的控制点的y坐标
const double b_x = 0.3 ;// 替换为对应的控制点的x坐标
const double b_y = 0.2 ;// 替换为对应的控制点的y坐标
const double c_x = 0.7 ;// 替换为对应的控制点的x坐标
const double c_y = 0.8 ;// 替换为对应的控制点的y坐标
const double d_x =  1;// 替换为对应的控制点的x坐标
const double d_y =  1;// 替换为对应的控制点的y坐标
const double epsilon = 1e-15;  // 精度，可以根据需要调整
const int max_iterations = 1000;  // 最大迭代次数，防止无限循环

								  // 定义方程及其导数
double equation(double t) {
	return std::pow(1 - t, 3) * a_x + 3 * t * std::pow(1 - t, 2) * b_x + 3 * std::pow(t, 2) * (1 - t) * c_x + std::pow(t, 3) * d_x - xa;
}

double derivative(double t) {
	return -3 * std::pow(1 - t, 2) * a_x + 3 * (3 * t - 4 * std::pow(t, 2)) * b_x + 3 * (2 * std::pow(t, 2) - 3 * t + 1) * c_x + 3 * std::pow(t, 2) * d_x;
}

// 牛顿迭代法求解方程
double solve() {
	double t = 0.5;  // 初始猜测值，可以根据实际情况调整

	for (int i = 0; i < max_iterations; ++i) {
		double delta_t = equation(t) / derivative(t);
		t -= delta_t;

		if (std::abs(delta_t) < epsilon) {
			break;  // 达到精度要求，退出循环
		}
	}

	return t;
}

int main() {
	// 使用牛顿迭代法求解方程
	double t_solution = solve();

	// 计算对应的A点的y坐标
	double y_solution = std::pow(1 - t_solution, 3) * a_y + 3 * t_solution * std::pow(1 - t_solution, 2) * b_y + 3 * std::pow(t_solution, 2) * (1 - t_solution) * c_y + std::pow(t_solution, 3) * d_y;

	std::cout << "解得的t值为: " << t_solution << std::endl;
	std::cout << "对应的A点的y坐标为: " << y_solution << std::endl;

	return 0;
}
*/


#include <iostream>
#include <cmath>

// 定义已知数据
const double xa = 0.6; // 替换为A点的x坐标
//const double ya =  // 替换为A点的y坐标
const double a_x =  0;// 替换为控制点a的x坐标
const double a_y =  0;// 替换为控制点a的y坐标
const double b_x =  0.15;// 替换为控制点b的x坐标
const double b_y =  0.7;// 替换为控制点b的y坐标
const double c_x =  1;// 替换为控制点c的x坐标
const double c_y =  1;// 替换为控制点c的y坐标
const double epsilon = 1e-15;  // 精度，可以根据需要调整
const int max_iterations = 1000;  // 最大迭代次数，防止无限循环

								  // 定义方程及其导数
double equation(double t) {
	return std::pow(1 - t, 2) * a_x + 2 * t * (1 - t) * b_x + std::pow(t, 2) * c_x - xa;
}

double derivative(double t) {
	return -2 * (1 - t) * a_x + 2 * (1 - 2 * t) * b_x + 2 * t * c_x;
}

// 牛顿迭代法求解方程
double solve() {
	double t = 0.5;  // 初始猜测值，可以根据实际情况调整

	for (int i = 0; i < max_iterations; ++i) {
		double delta_t = equation(t) / derivative(t);
		t -= delta_t;

		if (std::abs(delta_t) < epsilon) {
			break;  // 达到精度要求，退出循环
		}
	}

	return t;
}

int main() {
	// 使用牛顿迭代法求解方程
	double t_solution = solve();

	// 计算对应的A点的y坐标
	double y_solution = std::pow(1 - t_solution, 2) * a_y + 2 * t_solution * (1 - t_solution) * b_y + std::pow(t_solution, 2) * c_y;

	std::cout << "解得的t值为: " << t_solution << std::endl;
	std::cout << "对应的A点的y坐标为: " << y_solution << std::endl;

	double T = 0;
	double P0 = 0;
	double P1 = 0.15;
	double P1_Y = 0.7;
	double P2 = 1;
	double A = 0.6;
	// ///////////////////////////////////////////////////////////////
	//公式：(1 - t)^2P0 + 2 t (1 - t) P1 + t^2 P2=A
	//A是贝塞尔点的x坐标，带进去先求出t，然后再根据t求出贝塞尔点的y坐标
	// ////////////////////////////////////////////////////////////////////////
	double dTmp = A*P0 - 2 * A*P1 + A*P2 - P0*P2 + P1*P1;
	//T=(-sqrt(dTmp)+P0-P1)/(P0-2*P1+P2);
	if (dTmp < 0)
		dTmp = 0;
	if (P0 - 2 * P1 + P2 == 0)
	{
		T = (P0 - A) / (2 * (P0 - P1));
	}
	else
		T = (sqrt(dTmp) + P0 - P1) / (P0 - 2 * P1 + P2);
	if (T < 0)
		T = 0;
	if (T > 1)
		T = 1;
	double BY = 2 * T*(1 - T)*P1_Y + T*T;
	std::cout << "---对应的A点的y坐标为: " << BY << std::endl;
	return 0;
}
