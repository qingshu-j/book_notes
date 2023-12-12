// screen_calibration.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
#include <iostream>

// 定义触摸屏坐标和实际坐标的结构体
struct Point {
	double touchX, touchY;  // 触摸屏上的坐标
	double actualX, actualY;  // 实际坐标
};

// 计算触摸屏校正矩阵
void calculateCorrectionMatrix(const Point(&points)[5], double(&correctionMatrix)[3][3]) {
	double a[3][3] = { { 0 } };
	double b[3] = { 0 };

	for (int i = 0; i < 5; ++i) {
		a[0][0] += points[i].touchX * points[i].actualX;
		a[0][1] += points[i].touchX * points[i].actualY;
		a[0][2] += points[i].touchX;

		a[1][0] += points[i].touchY * points[i].actualX;
		a[1][1] += points[i].touchY * points[i].actualY;
		a[1][2] += points[i].touchY;

		a[2][0] += points[i].actualX;
		a[2][1] += points[i].actualY;
		a[2][2] += 1;

		b[0] += points[i].touchX;
		b[1] += points[i].touchY;
		b[2] += 1;
	}

	// 利用高斯消元法解线性方程组
	for (int i = 0; i < 2; ++i) {
		for (int j = i + 1; j < 3; ++j) {
			double ratio = a[j][i] / a[i][i];
			for (int k = 0; k < 3; ++k) {
				a[j][k] -= ratio * a[i][k];
			}
			b[j] -= ratio * b[i];
		}
	}

	// 回代求解
	for (int i = 2; i >= 0; --i) {
		for (int j = i + 1; j < 3; ++j) {
			b[i] -= a[i][j] * b[j];
		}
		correctionMatrix[i][2] = b[i] / a[i][i];
	}

	// 填充矩阵
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			correctionMatrix[i][j] = a[i][j];
		}
	}

	correctionMatrix[2][0] = correctionMatrix[2][1] = 0;
	correctionMatrix[2][2] = 1;
}

// 校正触摸坐标
void correctTouch(const double correctionMatrix[3][3], double touchX, double touchY, double& correctedX, double& correctedY) {
	double homogeneousX = correctionMatrix[0][0] * touchX + correctionMatrix[0][1] * touchY + correctionMatrix[0][2];
	double homogeneousY = correctionMatrix[1][0] * touchX + correctionMatrix[1][1] * touchY + correctionMatrix[1][2];
	double homogeneousZ = correctionMatrix[2][0] * touchX + correctionMatrix[2][1] * touchY + correctionMatrix[2][2];

	correctedX = homogeneousX / homogeneousZ;
	correctedY = homogeneousY / homogeneousZ;
}

int main() {
	// 五个校准点，你可以根据实际情况替换成你的触摸屏上的坐标和对应的实际坐标
	Point calibrationPoints[5] = {
		{ 100, 100, 100, 100 },
		{ 300, 100, 300, 100 },
		{ 500, 100, 500, 100 },
		{ 300, 300, 300, 300 },
		{ 500, 300, 500, 300 }
	};

	// 计算校正矩阵
	double correctionMatrix[3][3];
	calculateCorrectionMatrix(calibrationPoints, correctionMatrix);

	// 测试校正效果
	double touchX = 250, touchY = 250;
	double correctedX, correctedY;

	correctTouch(correctionMatrix, touchX, touchY, correctedX, correctedY);

	std::cout << "触摸屏坐标 (" << touchX << ", " << touchY << ") 校正后的实际坐标为 ("
		<< correctedX << ", " << correctedY << ")" << std::endl;

	return 0;
}
*/


/*
#include <iostream>
#include <cmath>

struct Point {
	double x;
	double y;
};

struct CalibrationData {
	Point actual[5];
	Point standard[5];
};

struct CalibrationParameters {
	double Tx, Ty;  // 平移参数
	double Sx, Sy;  // 缩放参数
	double R;       // 旋转参数
};

// 计算坐标点数组的均值
double calculateMean(Point points[], int size, bool isX) {
	double sum = 0.0;
	for (int i = 0; i < size; ++i) {
		sum += isX ? points[i].x : points[i].y;
	}
	return sum / size;
}

// 计算五点校准参数
CalibrationParameters calculateCalibrationParameters(CalibrationData& data) {
	CalibrationParameters params;

	// 计算平移参数
	params.Tx = calculateMean(data.actual, 5, true) - calculateMean(data.standard, 5, true);
	params.Ty = calculateMean(data.actual, 5, false) - calculateMean(data.standard, 5, false);

	// 计算缩放参数
	double sumXY = 0.0, sumX2 = 0.0, sumY2 = 0.0;
	double meanX = calculateMean(data.actual, 5, true);
	double meanY = calculateMean(data.actual, 5, false);
	double meanXs = calculateMean(data.standard, 5, true);
	double meanYs = calculateMean(data.standard, 5, false);

	for (int i = 0; i < 5; ++i) {
		sumXY += (data.actual[i].x - meanX) * (data.standard[i].x - meanXs) + (data.actual[i].y - meanY) * (data.standard[i].y - meanYs);
		sumX2 += std::pow(data.actual[i].x - meanX, 2);
		sumY2 += std::pow(data.actual[i].y - meanY, 2);
	}

	params.Sx = sumXY / sumX2;
	params.Sy = sumXY / sumY2;

	// 计算旋转参数
	double sumNum = 0.0, sumDen = 0.0;
	for (int i = 0; i < 5; ++i) {
		sumNum += (data.actual[i].x - meanX) * (data.standard[i].y - meanYs) - (data.actual[i].y - meanY) * (data.standard[i].x - meanXs);
		sumDen += (data.actual[i].x - meanX) * (data.standard[i].x - meanXs) + (data.actual[i].y - meanY) * (data.standard[i].y - meanYs);
	}

	params.R = std::atan2(sumNum, sumDen);

	return params;
}

// 应用校准参数
Point applyCalibration(Point& point, CalibrationParameters& params) {
	Point calibrated;
	calibrated.x = params.Sx * (point.x - params.Tx) * std::cos(params.R) - params.Sy * (point.y - params.Ty) * std::sin(params.R);
	calibrated.y = params.Sx * (point.x - params.Tx) * std::sin(params.R) + params.Sy * (point.y - params.Ty) * std::cos(params.R);
	return calibrated;
}

int main() {
	CalibrationData calibrationData;

	// 模拟触摸屏上的五个校准点的实际触摸位置
	calibrationData.actual[0] = { 58, 50 };
	calibrationData.actual[1] = { 52, 1026 };
	calibrationData.actual[2] = { 1876, 1035 };
	calibrationData.actual[3] = { 1870, 52 };
	calibrationData.actual[4] = { 958, 840 };

	// 模拟触摸屏上的五个校准点的标准位置
	calibrationData.standard[0] = { 50, 50 };
	calibrationData.standard[1] = { 50, 1030 };
	calibrationData.standard[2] = { 1870, 1030 };
	calibrationData.standard[3] = { 1870, 50 };
	calibrationData.standard[4] = { 960, 540 };

	// 计算校准参数
	CalibrationParameters calibrationParams = calculateCalibrationParameters(calibrationData);

	// 应用校准参数
	Point touchPoint = { 1870, 1030 };
	Point calibratedPoint = applyCalibration(touchPoint, calibrationParams);

	// 输出校准前后的坐标
	std::cout << "Original Touch Point: (" << touchPoint.x << ", " << touchPoint.y << ")\n";
	std::cout << "Calibrated Point: (" << calibratedPoint.x << ", " << calibratedPoint.y << ")\n";

	return 0;
}
*/

/*
#include <iostream>
using namespace  std;

#define N 9 // number of reference points for calibration algorithm
// ideal position of reference points
double ReferencePoint[N][2] = 
{
	//{50,50},{ 50,1030 },{ 1870,1030 },{ 1870,50 },{ 960,540 }
	{ 50,50 },{ 50,540 },{ 50,1030 },{ 960,1030 },{ 1870,1030 },{ 1870,540 },{ 1870,50 },{ 960,50 },{ 960,540 }
};
// sampling position of reference points
double SamplePoint[N][2] =
{
	//{ 58,50 },{ 52,1026 },{ 1876,1035 },{ 1870,52 },{ 958,540 }
	{ 55,49 },{ 52,542 },{ 52,1029 },{ 964,1027 },{ 1872,1032 },{ 1871,546 },{ 1871,56 },{ 962,51 },{ 960,542 }
};
double KX1, KX2, KX3, KY1, KY2, KY3; // coefficients for calibration algorithm
void Do_Calibration(double *Px, double *Py) // do calibration for point (Px, Py) using the calculated coefficients
{
	*Px = (double)(KX1*(*Px) + KX2*(*Py) + KX3 );
	*Py = (double)(KY1*(*Px) + KY2*(*Py) + KY3 );
}
int Get_Calibration_Coefficient() // calculate the coefficients for calibration algorithm: KX1, KX2, KX3, KY1, KY2, KY3
{
	int i;
	int Points = N;
	double a[3],b[3],c[3],d[3],k;
	if (Points < 3)
	{
		return 0;
	}
	else
	{
		if (Points == 3)
		{
			for (i = 0; i < Points; i++)
			{
				a[i] = (double)(SamplePoint[i][0]);
				b[i] = (double)(SamplePoint[i][1]);
				c[i] = (double)(ReferencePoint[i][0]);
				d[i] = (double)(ReferencePoint[i][1]);
			}
		}
		else if (Points > 3)
		{
			for (i = 0; i < 3; i++)
			{
				a[i] = 0;
				b[i] = 0;
				c[i] = 0;
				d[i] = 0;
			}
			for (i = 0; i < Points; i++)
			{
				a[2] = a[2] + (double)(SamplePoint[i][0]);
				b[2] = b[2] + (double)(SamplePoint[i][1]);
				c[2] = c[2] + (double)(ReferencePoint[i][0]);
				d[2] = d[2] + (double)(ReferencePoint[i][1]);
				a[0] = a[0] + (double)(SamplePoint[i][0])*(double)(SamplePoint[i][0]);
				a[1] = a[1] + (double)(SamplePoint[i][0])*(double)(SamplePoint[i][1]);
				b[0] = a[1];
				b[1] = b[1] + (double)(SamplePoint[i][1])*(double)(SamplePoint[i][1]);
				c[0] = c[0] + (double)(SamplePoint[i][0])*(double)(ReferencePoint[i][0]);
				c[1] = c[1] + (double)(SamplePoint[i][1])*(double)(ReferencePoint[i][0]);
				d[0] = d[0] + (double)(SamplePoint[i][0])*(double)(ReferencePoint[i][1]);
				d[1] = d[1] + (double)(SamplePoint[i][1])*(double)(ReferencePoint[i][1]);
			}
			a[0] = a[0] / a[2];
			a[1] = a[1] / b[2];
			b[0] = b[0] / a[2];
			b[1] = b[1] / b[2];
			c[0] = c[0] / a[2];
			c[1] = c[1] / b[2];
			d[0] = d[0] / a[2];
			d[1] = d[1] / b[2];
			a[2] = a[2] / Points;
			b[2] = b[2] / Points;
			c[2] = c[2] / Points;
			d[2] = d[2] / Points;
		}
		k = (a[0] - a[2])*(b[1] - b[2]) - (a[1] - a[2])*(b[0] - b[2]);
		KX1 = ((c[0] - c[2])*(b[1] - b[2]) - (c[1] - c[2])*(b[0] - b[2])) / k;
		KX2 = ((c[1] - c[2])*(a[0] - a[2]) - (c[0] - c[2])*(a[1] - a[2])) / k;
		KX3 = (b[0] * (a[2] * c[1] - a[1] * c[2]) + b[1] * (a[0] * c[2] - a[2] * c[0]) + b[2] * (a[1] * c[0] - a[0] * c[1])) / k;
		KY1 = ((d[0] - d[2])*(b[1] - b[2]) - (d[1] - d[2])*(b[0] - b[2])) / k;
		KY2 = ((d[1] - d[2])*(a[0] - a[2]) - (d[0] - d[2])*(a[1] - a[2])) / k;
		KY3 = (b[0] * (a[2] * d[1] - a[1] * d[2]) + b[1] * (a[0] * d[2] - a[2] * d[0]) + b[2] * (a[1] * d[0] - a[0] * d[1])) / k;
		return Points;
	}
}

int main()
{
	int p = Get_Calibration_Coefficient();
	double px = 960, py = 540;
	cout << "before:" << px << "," << py << endl;
	Do_Calibration(&px,&py);
	cout << "after:" << px << "," << py << endl;
	return 0;
}
*/

///*
using namespace std;
#include <iostream>
#include <vector>

// 结构体定义坐标点
struct Point {
	double x1, x2, x3;  // 代表方程组的系数
	double y;           // 代表方程组的右侧常数
};

// 最小二乘法拟合三个未知数的线性模型
void leastSquaresFit(const std::vector<Point>& data, double& a, double& b, double& c) {
	int n = data.size();

	// 构造方程组的矩阵表示
	double A[3][3] = { 0 };
	double B[3] = { 0 };

	for (const Point& p : data) {
		A[0][0] += p.x1 * p.x1;
		A[0][1] += p.x1 * p.x2;
		A[0][2] += p.x1;
		A[1][0] += p.x1 * p.x2;
		A[1][1] += p.x2 * p.x2;
		A[1][2] += p.x2;
		A[2][0] += p.x1;
		A[2][1] += p.x2;
		A[2][2] += 1;

		B[0] += p.x1 * p.y;
		B[1] += p.x2 * p.y;
		B[2] += p.y;
	}

	// 高斯消元法解方程组
	for (int i = 0; i < 3; ++i) {
		// 主元归一
		double pivot = A[i][i];
		for (int j = 0; j < 3; ++j) {
			A[i][j] /= pivot;
		}
		B[i] /= pivot;

		// 消元
		for (int k = 0; k < 3; ++k) {
			if (k != i) {
				double factor = A[k][i];
				for (int j = 0; j < 3; ++j) {
					A[k][j] -= factor * A[i][j];
				}
				B[k] -= factor * B[i];
			}
		}
	}

	// 结果
	a = B[0];
	b = B[1];
	c = B[2];
}

int main() {
	// 模拟数据点
	//{ 50, 50 }, { 50,540 }, { 50,1030 }, { 960,1030 }, { 1870,1030 }, { 1870,540 }, { 1870,50 }, { 960,50 }, { 960,540 }
	std::vector<Point> data = {
		{ 55, 49, 1, 50 },
		{ 52, 542, 1, 50 },
		{ 52, 1029, 1, 50 },
		{ 964, 1027, 1, 960 },
		{ 1872, 1032, 1, 1870 },
		{ 1871, 546, 1, 1870 },
		{ 1871, 56, 1, 1870 },
		{ 962, 51, 1, 960 },
		{ 960, 542, 1, 960 }
	};
	//{ 55, 49 }, { 52,542 }, { 52,1029 }, { 964,1027 }, { 1872,1032 }, { 1871,546 }, { 1871,56 }, { 962,51 }, { 960,542 }
	std::vector<Point> datay = {
		{ 55, 49, 1, 50 },
		{ 52, 542, 1, 540 },
		{ 52, 1029, 1, 1030 },
		{ 964, 1027, 1, 1030 },
		{ 1872, 1032, 1, 1030 },
		{ 1871, 546, 1, 540 },
		{ 1871, 56, 1, 50 },
		{ 962, 51, 1, 50 },
		{ 960, 542, 1, 540 }
	};

	// 计算最小二乘法拟合模型的系数
	double a, b, c;
	leastSquaresFit(data, a, b, c);
	double d, e, f;
	leastSquaresFit(datay, d, e, f);

	// 输出拟合结果
	std::cout << "Fit Model Equation: x = " << a << "x + " << b << "y + " << c << "\n";
	std::cout << "Fit Model Equation: y = " << d << "x + " << e << "y + " << f << "\n";

	double px = 960, py = 540;
	cout << "before:" << px << "," << py << endl;
	px = a*px+b*py+c;
	py = d*px + e*py + f;
	cout << "after:" << px << "," << py << endl;

	return 0;
}
//*/
