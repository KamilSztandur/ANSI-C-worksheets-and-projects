#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "calnum.h"

double calnum ( double (*f)( double x ), double min, double max, int n )
{
        double xp = min;
        double xk = max;
        double dx;
        double integral = 0;

        dx = (xk - xp) / n;

        for (int i = 0; i <= n; i++) 
        	integral += f(xp + i * dx);

        return integral;
}
