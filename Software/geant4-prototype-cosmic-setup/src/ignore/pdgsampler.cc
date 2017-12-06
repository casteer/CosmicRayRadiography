#include "pdgsampler.hh"
#include <cmath>

PDGSampler::PDGSampler()
{
    Re = 6371000*m;
    production_height = 15000*m;
    n=3;
    I0=88.5;
    E1=854;//GeV
    E0=4.28;//GeV
}

//https://arxiv.org/pdf/1606.06907.pdf
// Ratio of path lengths at angle theta to vertical
PDGSampler::path_length_ratio(cos_theta)
{
    double Rd = Re/production_height;

    return sqrt(Rd*Rd*cos_theta*cos_theta+2*Rd + 1) - Rd*cos_theta;

}

// Returns the joint PDF
double PDGSampler::joint_distribution(E,cos_theta){
    return I0*std::pow((E0+E),-n)*std::pow(1 + E/E1,-1) * std::pow( path_length_ratio(cos_theta), -n+1);
}

double PDGSampler::Normalize(double Elimit,double Estep, double cos_theta_limit, double cos_theta_step){

    //
    for(double e=0;e<Elimit;e+=Estep){
        for(double x=0;x<cos_theta_limit;x+=cos_theta_step){

        }
    }

}

// Returns the CDF
double PDGSampler::cdf(E,cos_theta){

    return cdf_E(E)*cdf_th(cos_theta);

}

// Returns the CDF of the intensity for n=3 only
double PDGSampler::cdf_E(E)
{
    double term1 = (1.0/((E+E0)*std::pow(E0-E1,2.0)));
    double term2 = (1.0/(2.0*std::pow(E+E0,2.0)*(E0-E1)));
    double term3 = -std::log(E+E0]*std::pow(E0-E1,-3.0);
    double term4 = std::log(E+E1)*std::pow(E0-E1,-3.0);

    return E1*(term1 + term2 + term3 + term4);

}

//x = cos theta
double PDGSampler::cdf_th(x){

    double r = Re/production_height;

    double term1 = r*x*(std::pow(1.0 + 2.0*r + std::pow(r*x,2.0),0.5)-(r*x));
    double term2 = (1.0 + 2.0*r)*std::log(r*x + std::pow(1.0 + 2.0*r + std::pow(r*x,2.0),0.5));

    return (term1+term2)/(2.0*r);

}
