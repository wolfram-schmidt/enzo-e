#define CHARM_ENZO

#include "enzo.hpp"

//----------------------------------------------------------------------

CkReduction::reducerType r_method_turbulence_type;

extern CkReductionMsg * r_method_turbulence(int n, CkReductionMsg ** msgs);

//--------------------------------------------------

void register_method_turbulence(void)
{
  r_method_turbulence_type = CkReduction::addReducer(r_method_turbulence); 
}

//--------------------------------------------------

// SEE enzo_EnzoMethodTurbulence.cpp for context
CkReductionMsg * r_method_turbulence(int n, CkReductionMsg ** msgs)
{
  double accum[MAX_TURBULENCE_ARRAY] = { 0.0 };
  accum[INDEX_TURBULENCE_minD] = std::numeric_limits<double>::max();
  accum[INDEX_TURBULENCE_maxD] = std::numeric_limits<double>::min();

  for (int i=0; i<n; i++) {
    double * values = (double *) msgs[i]->getData();
    for (int ig=0; ig<MAX_TURBULENCE_ARRAY-2; ig++) {
      accum [ig] += values[ig];
    }
    accum [INDEX_TURBULENCE_minD] = 
      std::min(accum[INDEX_TURBULENCE_minD],values[INDEX_TURBULENCE_minD]);
    accum [INDEX_TURBULENCE_maxD] = 
      std::max(accum[INDEX_TURBULENCE_maxD],values[INDEX_TURBULENCE_maxD]);
  }
  return CkReductionMsg::buildNew(MAX_TURBULENCE_ARRAY*sizeof(double),accum);
}

//======================================================================

CkReduction::reducerType sum_long_double_type;

extern CkReductionMsg * sum_long_double(int n, CkReductionMsg ** msgs);

void register_sum_long_double(void)
{ sum_long_double_type = CkReduction::addReducer(sum_long_double); }

CkReductionMsg * sum_long_double(int n, CkReductionMsg ** msgs)
{
  long double accum = 0.0;

  for (int i=0; i<n; i++) {
    long double * values = (long double *) msgs[i]->getData();
    accum += values[0];
  }
  return CkReductionMsg::buildNew(sizeof(long double),&accum);
}

//------------------------------------------------------------------------


CkReduction::reducerType sum_long_double_2_type;

extern CkReductionMsg * sum_long_double_2(int n, CkReductionMsg ** msgs);

void register_sum_long_double_2(void)
{ sum_long_double_2_type = CkReduction::addReducer(sum_long_double_2); }

CkReductionMsg * sum_long_double_2(int n, CkReductionMsg ** msgs)
{
  long double accum[2] = { 0.0, 0.0 };

  for (int i=0; i<n; i++) {
    long double * values = (long double *) msgs[i]->getData();
    accum [0] += values[0];
    accum [1] += values[1];
  }
  return CkReductionMsg::buildNew(2*sizeof(long double),accum);
}

//------------------------------------------------------------------------


CkReduction::reducerType sum_long_double_3_type;

extern CkReductionMsg * sum_long_double_3(int n, CkReductionMsg ** msgs);

void register_sum_long_double_3(void)
{ sum_long_double_3_type = CkReduction::addReducer(sum_long_double_3); }

CkReductionMsg * sum_long_double_3(int n, CkReductionMsg ** msgs)
{
  long double accum[3] = { 0.0, 0.0, 0.0 };

  for (int i=0; i<n; i++) {
    long double * values = (long double *) msgs[i]->getData();
    accum [0] += values[0];
    accum [1] += values[1];
    accum [2] += values[2];
  }
  return CkReductionMsg::buildNew(3*sizeof(long double),accum);
}

//======================================================================

CkReduction::reducerType sum_long_double_4_type;

extern CkReductionMsg * sum_long_double_4(int n, CkReductionMsg ** msgs);

void register_sum_long_double_4(void)
{ sum_long_double_4_type = CkReduction::addReducer(sum_long_double_4); }

CkReductionMsg * sum_long_double_4(int n, CkReductionMsg ** msgs)
{
  long double accum[4] = { 0.0, 0.0, 0.0, 0.0 };

  for (int i=0; i<n; i++) {
    long double * values = (long double *) msgs[i]->getData();
    accum [0] += values[0];
    accum [1] += values[1];
    accum [2] += values[2];
    accum [3] += values[3];
  }
  return CkReductionMsg::buildNew(4*sizeof(long double),accum);
}

//======================================================================

#include "main.cpp"
