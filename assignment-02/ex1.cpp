#include <iostream>
#include <ctime>
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

#define MATRIX_SIZE 100

int main(int argc, char** argv) {
  MatrixXd matrix_NN = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
  matrix_NN = matrix_NN * matrix_NN.transpose(); // 保证实对称矩阵
  SelfAdjointEigenSolver<Matrix3d> eigen_solver(matrix_NN); // 实对称矩阵可以保证正定成功
  cout << "Eigen values = \n" << eigen_solver.eigenvalues() << endl;
  cout << "Eigen vectors = \n" << eigen_solver.eigenvectors() << endl;
  MatrixXd v_Nd = MatrixXd::Random(MATRIX_SIZE, 1);

  clock_t time_stt = clock();
  Matrix<double, MATRIX_SIZE, 1> x;

  // QR
  x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
  cout << "time of Qr decomposition is "
       << 1000 * (clock() - time_stt) / (double) CLOCKS_PER_SEC << "ms" << endl;
  cout << "x = " << x.transpose() << endl;
  
  // Cholesky
  time_stt = clock();
  x = matrix_NN.ldlt().solve(v_Nd);
  cout << "time of ldlt decomposition is "
       << 1000 * (clock() - time_stt) / (double) CLOCKS_PER_SEC << "ms" << endl;
  cout << "x = " << x.transpose() << endl;
  
  return 0;
}