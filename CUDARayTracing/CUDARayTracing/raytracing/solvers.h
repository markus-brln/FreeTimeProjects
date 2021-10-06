#ifndef SOLVERS_H_
#define SOLVERS_H_

#include <cmath>
#include <utility>

class Solvers
{
public:
    // Solve quadratic function
    // return false if no solution
    // x0 <= x1
    // uses pass by reference (hence the &)
    static bool quadratic(double a, double b, double c,
        double& x0, double& x1)
    {
        double discr = b * b - 4.0 * a * c;

        if (discr < 0.0)
            return false;   // no solution

        if (discr == 0.0)
        {
            x0 = x1 = -0.5 * b / a;
        }
        else
        {
            double q = (b > 0.0) ?
                -0.5 * (b + sqrt(discr)) :
                -0.5 * (b - sqrt(discr));
            x0 = q / a;
            x1 = c / q;
        }

        if (x0 > x1)
            std::swap(x0, x1);

        return true;
    }
};



#endif
