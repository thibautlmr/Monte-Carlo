#include "pnl/pnl_vector.h"
#include "pnl/pnl_specfun.h"
#include "pnl/pnl_random.h"

class Brownian
{
public:
    Brownian(double maturity, int N, PnlRng *rng);
    ~Brownian();
    PnlVect *brownian_;
    double maturity_;
    int N_;
    PnlRng *rng_;
    double getTauA(double a);
    void brownianBridge(int s, int t);
    double getTauABrownianBridge(double a);
    void simu();
};