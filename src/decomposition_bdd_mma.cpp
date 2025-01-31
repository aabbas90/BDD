#include "decomposition_bdd_mma_base.h"
#include "decomposition_bdd_mma.h"

namespace LPMP {

    class decomposition_bdd_mma::impl : public decomposition_bdd_base {
        public:
            using decomposition_bdd_base::decomposition_bdd_base; 
    };

    decomposition_bdd_mma::decomposition_bdd_mma(bdd_storage& bdd_storage_, decomposition_mma_options opt)
    {
        MEASURE_FUNCTION_EXECUTION_TIME;
        pimpl = std::make_unique<impl>(bdd_storage_, opt);
    }

    decomposition_bdd_mma::decomposition_bdd_mma(decomposition_bdd_mma&& o)
        : pimpl(std::move(o.pimpl))
    {}

    decomposition_bdd_mma& decomposition_bdd_mma::operator=(decomposition_bdd_mma&& o)
    {
        pimpl = std::move(o.pimpl);
        return *this;
    }

    decomposition_bdd_mma::~decomposition_bdd_mma() {}

    void decomposition_bdd_mma::set_cost(const double c, const size_t var)
    {
        pimpl->set_cost(c, var);
    }

    void decomposition_bdd_mma::backward_run()
    {
        return pimpl->backward_run();
    }

    void decomposition_bdd_mma::iteration()
    {
        pimpl->iteration();
    }

    double decomposition_bdd_mma::lower_bound()
    {
        return pimpl->lower_bound();
    }

    two_dim_variable_array<std::array<double,2>> decomposition_bdd_mma::min_marginals()
    {
        return pimpl->min_marginals();
    }
}
