#include "riskforge/random/normal.hpp"
#include <cmath>
#include <limits>
namespace riskforge::random{
    namespace{
        double evaluate_polynomial(
            const double* coefficients,
            int degree,
            double value
        ){
            double result= coefficients[degree];
            for (int index=degree-1; index>=0; --index){
                result= result*value+coefficients[index];
            }
            return result;
        }
        double evaluate_polynomials_with_one(
            const double* coefficient,
            int degree,
            double value
        ){
            double result= coefficient[degree];
            for (int index= degree-1; index>=1; --index){
                result= result*value+coefficient[index];
            }
            return result*value+1.0;
        }
    }
    double normal_ppf(double probability){
        if (probability<=0.0){
            return -std::numeric_limits<double>::infinity();
        }
        if (probability>=1.0){
            return std::numeric_limits<double>::infinity();
        }
        constexpr double a[]= {
            3.3871328727963666080,
            133.14166789178437745,
            1971.5909503065514427,
            13731.693765509461125,
            45921.953931549871457,
            67265.770927008700853,
            33430.575583588128105,
            2509.0809287301226727
        };
        constexpr double b[]= {
            0.0,
            42.313330701600911252,
            687.18700749205790830,
            5394.1960214247511077,
            21213.794301586595867,
            39307.895800092710610,
            28729.085735721942674,
            5226.4952788528545610
        };
        constexpr double c[]= {
            1.42343711074968357734,
            4.63033784615654529590,
            5.76949722146069140550,
            3.64784832476320460504,
            1.27045825245236838258,
            0.24178072517745061177,
            0.0227238449892691845833,
            0.000774545014278341407640
        };
        constexpr double d[]= {
            0.0,
            2.05319162663775882187,
            1.67638483018380384940,
            0.68976733498510000455,
            0.14810397642748007459,
            0.0151986665636164571966,
            0.00054759380849953449460,
            0.00000000105075007164441684324
        };
        constexpr double e[]= {
            6.65790464350110377720,
            5.46378491116411436990,
            1.78482653991729133580,
            0.29656057182850489123,
            0.0265321895265761230930,
            0.0012426609473880784386,
            0.0000271155556874348757815,
            0.0000002010334399292288132658
        };
        constexpr double f[]= {
            0.0,
            0.59983220655588793769,
            0.13692988092273580531,
            0.0148753612908506148525,
            0.00078686913114561325987,
            0.0000184631831751005468180,
            0.00000014215117583164458891,
            0.00000000000000204426310338993978564
        };
        constexpr double split1= 0.425;
        constexpr double split2= 5.0;
        constexpr double constant1= 0.180625;
        constexpr double constant2= 1.6;
        const double q= probability-0.5;
        if (std::abs(q)<= split1){
            const double r= constant1-(q*q);
            return q*evaluate_polynomial(a, 7, r)/evaluate_polynomials_with_one(b, 7, r);
        }
        double r= q<0.0 ? probability : 1.0- probability;
        r= std::sqrt(-std::log(r));
        double result;
        if (r<=split2){
            r-=constant2;
            result= evaluate_polynomial(c,7,r)/evaluate_polynomials_with_one(d,7,r);
        }
        else{
            r-=split2;
            result= evaluate_polynomial(e, 7, r)/evaluate_polynomials_with_one(f, 7, r);
        }
        return q<0.0 ? -result: result;
    }
}