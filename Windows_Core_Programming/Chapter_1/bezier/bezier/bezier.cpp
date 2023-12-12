// bezier.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

/*
#include <iostream>
#include <cmath>

// ������֪����
const double xa = 0.6; // �滻ΪA���x����
//const double ya =  // �滻ΪA���y����
const double a_x = 0 ;// �滻Ϊ��Ӧ�Ŀ��Ƶ��x����
const double a_y = 0 ;// �滻Ϊ��Ӧ�Ŀ��Ƶ��y����
const double b_x = 0.3 ;// �滻Ϊ��Ӧ�Ŀ��Ƶ��x����
const double b_y = 0.2 ;// �滻Ϊ��Ӧ�Ŀ��Ƶ��y����
const double c_x = 0.7 ;// �滻Ϊ��Ӧ�Ŀ��Ƶ��x����
const double c_y = 0.8 ;// �滻Ϊ��Ӧ�Ŀ��Ƶ��y����
const double d_x =  1;// �滻Ϊ��Ӧ�Ŀ��Ƶ��x����
const double d_y =  1;// �滻Ϊ��Ӧ�Ŀ��Ƶ��y����
const double epsilon = 1e-15;  // ���ȣ����Ը�����Ҫ����
const int max_iterations = 1000;  // ��������������ֹ����ѭ��

								  // ���巽�̼��䵼��
double equation(double t) {
	return std::pow(1 - t, 3) * a_x + 3 * t * std::pow(1 - t, 2) * b_x + 3 * std::pow(t, 2) * (1 - t) * c_x + std::pow(t, 3) * d_x - xa;
}

double derivative(double t) {
	return -3 * std::pow(1 - t, 2) * a_x + 3 * (3 * t - 4 * std::pow(t, 2)) * b_x + 3 * (2 * std::pow(t, 2) - 3 * t + 1) * c_x + 3 * std::pow(t, 2) * d_x;
}

// ţ�ٵ�������ⷽ��
double solve() {
	double t = 0.5;  // ��ʼ�²�ֵ�����Ը���ʵ���������

	for (int i = 0; i < max_iterations; ++i) {
		double delta_t = equation(t) / derivative(t);
		t -= delta_t;

		if (std::abs(delta_t) < epsilon) {
			break;  // �ﵽ����Ҫ���˳�ѭ��
		}
	}

	return t;
}

int main() {
	// ʹ��ţ�ٵ�������ⷽ��
	double t_solution = solve();

	// �����Ӧ��A���y����
	double y_solution = std::pow(1 - t_solution, 3) * a_y + 3 * t_solution * std::pow(1 - t_solution, 2) * b_y + 3 * std::pow(t_solution, 2) * (1 - t_solution) * c_y + std::pow(t_solution, 3) * d_y;

	std::cout << "��õ�tֵΪ: " << t_solution << std::endl;
	std::cout << "��Ӧ��A���y����Ϊ: " << y_solution << std::endl;

	return 0;
}
*/


#include <iostream>
#include <cmath>

// ������֪����
const double xa = 0.6; // �滻ΪA���x����
//const double ya =  // �滻ΪA���y����
const double a_x =  0;// �滻Ϊ���Ƶ�a��x����
const double a_y =  0;// �滻Ϊ���Ƶ�a��y����
const double b_x =  0.15;// �滻Ϊ���Ƶ�b��x����
const double b_y =  0.7;// �滻Ϊ���Ƶ�b��y����
const double c_x =  1;// �滻Ϊ���Ƶ�c��x����
const double c_y =  1;// �滻Ϊ���Ƶ�c��y����
const double epsilon = 1e-15;  // ���ȣ����Ը�����Ҫ����
const int max_iterations = 1000;  // ��������������ֹ����ѭ��

								  // ���巽�̼��䵼��
double equation(double t) {
	return std::pow(1 - t, 2) * a_x + 2 * t * (1 - t) * b_x + std::pow(t, 2) * c_x - xa;
}

double derivative(double t) {
	return -2 * (1 - t) * a_x + 2 * (1 - 2 * t) * b_x + 2 * t * c_x;
}

// ţ�ٵ�������ⷽ��
double solve() {
	double t = 0.5;  // ��ʼ�²�ֵ�����Ը���ʵ���������

	for (int i = 0; i < max_iterations; ++i) {
		double delta_t = equation(t) / derivative(t);
		t -= delta_t;

		if (std::abs(delta_t) < epsilon) {
			break;  // �ﵽ����Ҫ���˳�ѭ��
		}
	}

	return t;
}

int main() {
	// ʹ��ţ�ٵ�������ⷽ��
	double t_solution = solve();

	// �����Ӧ��A���y����
	double y_solution = std::pow(1 - t_solution, 2) * a_y + 2 * t_solution * (1 - t_solution) * b_y + std::pow(t_solution, 2) * c_y;

	std::cout << "��õ�tֵΪ: " << t_solution << std::endl;
	std::cout << "��Ӧ��A���y����Ϊ: " << y_solution << std::endl;

	double T = 0;
	double P0 = 0;
	double P1 = 0.15;
	double P1_Y = 0.7;
	double P2 = 1;
	double A = 0.6;
	// ///////////////////////////////////////////////////////////////
	//��ʽ��(1 - t)^2P0 + 2 t (1 - t) P1 + t^2 P2=A
	//A�Ǳ��������x���꣬����ȥ�����t��Ȼ���ٸ���t������������y����
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
	std::cout << "---��Ӧ��A���y����Ϊ: " << BY << std::endl;
	return 0;
}
