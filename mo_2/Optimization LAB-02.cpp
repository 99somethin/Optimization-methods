#include <iostream>

using namespace std;

//f(x1,x2):
double f(double x_1, double x_2) {
	return 6 * x_1 * x_1 + 0.6 * x_1 * x_1 + 3 * x_2 * x_2;
}

// частная производная по x1 от f(x1,x2):
double chast_x1(double x_1, double x_2) {
	return 12 * x_1 + 0.6 * x_2;

}

// частная производная по x2 от f(x1,x2):
double chast_x2(double x_1, double x_2) {

	return 0.6 * x_1 + 6 * x_2;
}

void main() {

	setlocale(LC_ALL, "Russian");
	//данные x^k, E1, E2, M:
	double x_k[2] = { 0, 0.5 };
	cout << "x_0={0, 0.5}" << endl;
	double x_k_prev[2];
	double E1 = 0.15;
	cout << "E1=0,15" << endl;
	double E2 = 0.2;
	cout << "E2=0,2" << endl;
	int M = 10;
	cout << "M=10" << endl<<endl;
	double x_k_absdif2 = 0;
	double function_raz2 = 0;

	int Exit = 0;
	//Задаём k = 0
	int k = 0;
	int superflag = 1;

	while (superflag) {

		double Gradient[2] = { chast_x1(x_k[0], x_k[1]), chast_x2(x_k[0], x_k[1]) };
		cout << "Gradient= {" << Gradient[0] <<"," << Gradient[1] << "}" << endl;

		double Abs_Gradient = sqrt(Gradient[0] * Gradient[0] + Gradient[1] * Gradient[1]);
		cout << "Abs_Gradient =" << Abs_Gradient << endl;
		cout << Abs_Gradient << "<?" << E1 << endl;
		if (Abs_Gradient < E1) {
			cout << "itog_x = x^k = " << "(" << x_k[0] << ", " << x_k[1] << ")";
			break;
		}
		else if (k >= M) {
			cout << k << ">=?" << M << endl;
			cout << "itog_x = x^k = " << "(" << x_k[0] << ", " << x_k[1] << ")";
			break;
		}
		else {
			cout << k << ">=?" << M << endl;
			int flag = 1;
			double t_k = 0.5; //t_к
			while (flag) {
				double x_k_next[2] = { x_k[0] - (t_k * chast_x1(x_k[0], x_k[1])), x_k[1] - (t_k * chast_x2(x_k[0], x_k[1])) };
				cout << "x_k_next= {" << x_k_next[0] << "," << x_k_next[1]<<"}" << endl;
				if ((f(x_k_next[0], x_k_next[1]) - f(x_k[0], x_k[1])) < 0) {
					flag = 0;
					double x_k_absdif1 = sqrt((x_k_next[0] - x_k[0]) * (x_k_next[0] - x_k[0]) + (x_k_next[1] - x_k[1]) * (x_k_next[1] - x_k[1]));
					cout << "x_k_modul=" << x_k_absdif1 << endl;
					double function_raz1 = abs(f(x_k_next[0], x_k_next[1]) - f(x_k[0], x_k[1]));
					cout << "function_raz_now =" << function_raz1;
					if (k >= 1)
					{
						double x_k_absdif2 = sqrt((x_k[0] - x_k_prev[0]) * (x_k[0] - x_k_prev[0]) + (x_k[1] - x_k_prev[1]) * (x_k[1] - x_k_prev[1]));
						cout << " x_k_modul_prev=" << x_k_absdif2<<endl;
						double function_raz2 = abs(f(x_k[0], x_k[1]) - f(x_k_prev[0], x_k_prev[1]));
						cout << "function_raz_prev=" << function_raz2 << endl;
					}
					cout << x_k_absdif1 << "<" << E2 << " && " << function_raz1 << " < " << E2 << " && " << k << " >=1 && " << x_k_absdif2 << " < " << E2 << " && " << function_raz2 << " < " << E2 << endl;
					if (x_k_absdif1 < E2 && function_raz1 < E2 && k >= 1 && x_k_absdif2 < E2 && function_raz2 < E2)
					{

						cout << "\n" <<  "x* = " << "(" << x_k_next[0] << ", " << x_k_next[1] << ")" << endl;
						cout << "F(x*) = " << f(x_k_next[0], x_k_next[1]) << endl;
						Exit = 1;
						break;
					}
					else {
						k = k + 1;
						cout << "k=" << k << endl;
						cout << "now_x = x^k+1 = " << "(" << x_k_next[0] << ", " << x_k_next[1] << ")" << endl;
						cout << "F(now_x) = " << f(x_k_next[0], x_k_next[1]) << endl << endl;
						x_k_prev[0] = x_k[0];
						x_k_prev[1] = x_k[1];
						x_k[0] = x_k_next[0];
						x_k[1] = x_k_next[1];

					}
				}
				else {
					t_k = t_k / 2;
					cout << "t_k=" << t_k << endl;
				}
			}

		}

		if (Exit == 1)
			break;
	}

}

