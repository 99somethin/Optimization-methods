using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;


namespace MO_FINAL_LAB
{
    internal class Program
    {
        static double Original_Function(double x_1, double x_2)
        {
            return 2 * Math.Pow(x_1, 2) + Math.Pow(x_2, 2);
        }

        static double Limit_Function_G(double x_1, double x_2)
        {
            return 3 * x_1 + x_2 - 2;
        }

        static double Penalty_Function(double x_1, double x_2)
        {
            return (r_k / 2) * Math.Pow(Limit_Function_G(x_1, x_2), 2);
        }

        static double Assist_Function(double x_1, double x_2)
        {
            return Original_Function(x_1, x_2) + Penalty_Function(x_1, x_2);
        }


        static double[] GradF(double x_1, double x_2)
        {
            x_1 = Math.Round(x_1, 2);
            x_2 = Math.Round(x_2, 2);
            // Градиент функции f(x, y)
            return new double[] {
            4 * x_1 + 9 * r_k * x_1 + 3 * r_k * x_2 - 6 * r_k,
            2 * x_2 + 3 * r_k * x_1 + 1 * r_k * x_2 - 2 * r_k
        };
        }

        static double[,] HessianF(double x, double y)
        {
            // Гессиан функции f(x, y)
            return new double[,] {
            { 4 + 9 * r_k,3 * r_k },
            { 3 * r_k,  2 + r_k }
        };
        }

        static void printMatrix(double[,] mx, string mes = "")
        {
            Console.Write(mes);
            for (int i = 0; i < mx.GetLength(0); i++)
            {
                for (int j = 0; j < mx.GetLength(0); j++)
                    Console.Write(mx[i, j] + " ");
                Console.WriteLine();
            }
        }
        static double[,] InverseMatrix(double[,] matrix)
        {
            // Пока простейший способ - обратная матрица для 2x2 матрицы
            double determinant = matrix[0, 0] * matrix[1, 1] - matrix[0, 1] * matrix[1, 0];
            double[,] inversedMatrix = new double[2, 2];
            inversedMatrix[0, 0] = (matrix[1, 1] / determinant);
            inversedMatrix[1, 1] = (matrix[0, 0] / determinant);
            inversedMatrix[0, 1] = (-matrix[0, 1] / determinant);
            inversedMatrix[1, 0] = (-matrix[1, 0] / determinant);

            return inversedMatrix;
        }

        static double[] MatrixVectorMultiplication(double[,] matrix, double[] vector)
        {
            double[] result = new double[2];
            result[0] = matrix[0, 0] * vector[0] + matrix[0, 1] * vector[1];
            result[1] = matrix[1, 0] * vector[0] + matrix[1, 1] * vector[1];
            return result;
        }

        static int k = 0;
        static double Epsilon = 0.05;
        static double r_0 = 1;
        static double C = 5;
        static double r_k = r_0;
        static double x_1 = 1.5;
        static double x_2 = 0.5;


        static void Main(string[] args)
        {
            Console.WriteLine("");
            Console.WriteLine($"Начальные параметры:\nk = {k}\nEpsilon = {Epsilon}\nr_0 = {r_0}\nC = {C}\nx_k = ({x_1} ; {x_2}) (задаётся пользователем)\n\n\n");

            while (true)
            {

                Console.WriteLine("Найдем x*(r_k), минимизируя вспомогательную функцию f(x, r_k) с помощью метода Ньютона:");
                // Определяем функцию, которую мы хотим минимизировать
                Tuple<double, double> NewtonMethod(Func<double, double, double> f,
                Func<double, double, double[]> gradF,
                Func<double, double, double[,]> hessianF,
                 double x0, double y0, double E2 = 0.2, int maxIter = 10, double E1 = 0.15)
                {
                    double x = x0;
                    double y = y0;

                    bool lastYes = false;
                    Console.WriteLine("---------------------START NEWTON------------");
                    for (int i = 0; i < maxIter; i++)
                    {
                        Console.WriteLine($"ITERATION {i}\nX = [{x}, {y}]");
                        double[] gradient = gradF(x, y);
                        Console.WriteLine($"gradient = [{gradient[0]}, {gradient[1]}]");
                        if (Math.Sqrt(gradient[0] * gradient[0] + gradient[1] * gradient[1]) < E1)
                        {
                            Console.WriteLine($"ModGrad = {Math.Sqrt(gradient[0] * gradient[0] + gradient[1] * gradient[1])} < {E1}");
                            break;
                        }
                        else
                        {
                            Console.WriteLine($"ModGrad = {Math.Sqrt(gradient[0] * gradient[0] + gradient[1] * gradient[1])} > {E1}");
                        }
                        double[,] hessian = hessianF(x, y);

                        printMatrix(hessian, "Матрица гесса\n");

                        double[,] invHessian = InverseMatrix(hessian);

                        printMatrix(invHessian, "\nОбратная матрица гесса\n");

                        if ((invHessian[0, 0] < 0) && (invHessian[0, 0] * invHessian[1, 1] - invHessian[0, 1] * invHessian[1, 0]) < 0)
                        {
                            Console.WriteLine($"{invHessian[0, 0]} <><><> {invHessian[0, 0] * invHessian[1, 1] - invHessian[0, 1] * invHessian[1, 0]} ");
                            Console.WriteLine("matrix < 0!!");
                            break;
                        }
                        else
                        {
                            Console.WriteLine("matrix > 0");

                        }
                        double[] update = MatrixVectorMultiplication(invHessian, gradient);


                        if (Math.Sqrt(Math.Pow((x - (x + update[0])), 2) + Math.Pow((y - (y + update[1])), 2)) < 0.2 &&
                            Math.Abs(Assist_Function(x + update[0], y + update[1]) - Assist_Function(x, y)) < 0.2)
                        {
                            Console.WriteLine($"{Math.Sqrt(Math.Pow((x - (x + update[0])), 2) + Math.Pow((y - (y + update[1])), 2))} < 0.2 && " +
                                $"{Math.Abs(Assist_Function(x + update[0], y + update[1]) - Assist_Function(x, y))} < 0.2");
                            if (lastYes)
                            {
                                lastYes = false;
                                x -= update[0];
                                y -= update[1];
                                Console.WriteLine($"\nd0 = [{update[0]}, {update[1]}]");
                                Console.WriteLine($"\nX = [{x}, {y}]");
                                break;
                            }
                            else
                                lastYes = true;
                        }
                        else
                        {
                            lastYes = false;
                            Console.WriteLine($"X_NEXT - X3 = {Math.Sqrt(Math.Pow((x - (x + update[0])), 2) + Math.Pow((y - (y + update[1])), 2))} > 0.2 && " +
                                $"Fnext - f = {Math.Abs(Assist_Function(x + update[0], y + update[1]) - Assist_Function(x, y))} > 0.2");

                        }
                        x -= update[0];
                        y -= update[1];

                        Console.WriteLine($"\nd0 = [{update[0]}, {update[1]}]");
                        Console.WriteLine($"\nX = [{x}, {y}]");
                    }
                    Console.WriteLine("---------------------END NEWTON------------");
                    return new Tuple<double, double>(x, y);

                   
                }
                // Начальное приближение
                double x_0 = x_1;
                double y_0 = x_2;

                // Запускаем метод Ньютона
                var result = NewtonMethod(Assist_Function, GradF, HessianF, x_0, y_0);
                double x_1Min = result.Item1;
                double x_2Min = result.Item2;
                double minValue = Assist_Function(x_1Min, x_2Min);



                double Check_Penalty_Function = Penalty_Function(x_1Min, x_2Min);
                Console.WriteLine($"x* из минимизированной вспомогательной функции = ({x_1Min} ; {x_2Min})");
                Console.WriteLine($"Значение штрафной функции с аргументами x*(r_k) и r_k: {Check_Penalty_Function}");

                Console.WriteLine($"Проверка: {Check_Penalty_Function.ToString("0.#########################")} <= {Epsilon}");
                if (Check_Penalty_Function <= Epsilon)
                {

                    Console.WriteLine($"Процесс поиска завершился на итерации {k}. x* = x*(r_k) и f(x*) = f(x*(r_k)).");
                    Console.WriteLine($"Точка минимума: x_1 = {x_1Min} и x_2 = {x_2Min}");
                    Console.WriteLine($"Значение функции в точке минимума: f(x*(r_k)) = {Original_Function(x_1Min, x_2Min)}");
                    break;
                }
                else
                {
                    x_1 = x_1Min;
                    x_2 = x_2Min;
                    r_k = C * r_k;
                    k = k + 1;
                    Console.WriteLine("Условие не выполнилось: ");
                    Console.WriteLine($"x^k+1 = ({x_1Min};{x_2Min})\nr_k+1 = {r_k}\n\nk = {k}");
                    Console.WriteLine("Итерация завершилась.\n\n\n");

                }
            }
            Console.ReadKey();
        }
    }
}

