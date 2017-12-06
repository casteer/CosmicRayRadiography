#ifndef PDGSAMPLER_HH
#define PDGSAMPLER_HH


class PDGSampler
{
public:
    PDGSampler();


private:
    angular_energy_joint_PDF();

    // Constants radius of earth and muon production height
    double Re;
    double production_height;

    // Spectral shape parameters
    double n;
    double I0;
    double E1;//GeV
    double E0;//GeV

};

#endif // PDGSAMPLER_HH
