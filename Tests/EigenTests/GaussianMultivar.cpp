#include <iostream>
#include <fstream>
#include <../../Libraries/EigenLib/Eigen/Dense>
//#include <Eigen/Dense>
double foo(const Eigen::VectorXd &x, const Eigen::VectorXd &meanVec, const Eigen::MatrixXd &covMat)
;

int main(){
    double result;
    int NX = 120, NY = 120, n=7;
    Eigen::MatrixXd sigma(2, 2); // creamos una matriz 2x2 y le metemos los valores
    sigma <<20, 0.1,
            0.1, 20;
    Eigen::VectorXd mean(2);
    mean << 40, 55; //ESTE VA A SER EL PIXEL QUE SE ELIJA ALEATORIAMENTE
    Eigen::VectorXd coordinate(2);
    std::ofstream File; 
    File.open("Plot/GaussianMat1.txt");
    int node=0;
    for(int i=0;i<NX;i++){
        for(int j=0;j<NY;j++){
            coordinate << i,j;
            n = 0.3*0.5/foo(mean,mean,sigma);
            File << 0.5 - (n)*foo(coordinate,mean,sigma) << std::endl;
            node++;
        }
    }
    File.close();
    return 0;
};

double foo(const Eigen::VectorXd &x, const Eigen::VectorXd &meanVec, const Eigen::MatrixXd &covMat)
{
    // avoid magic numbers in your code. Compilers will be able to compute this at compile time:
    const double logSqrt2Pi = 0.5*std::log(2*M_PI);
    typedef Eigen::LLT<Eigen::MatrixXd> Chol;
    Chol chol(covMat);
    // Handle non positive definite covariance somehow:
    if(chol.info()!=Eigen::Success) throw "decomposition failed!";
    const Chol::Traits::MatrixL& L = chol.matrixL();
    double quadform = (L.solve(x - meanVec)).squaredNorm();
    return std::exp(-x.rows()*logSqrt2Pi - 0.5*quadform) / L.determinant();
};
