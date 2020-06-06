// See LICENSE_CELLO file for license and copyright information

/// @file     enzo_EnzoMethodNull.hpp
/// @author   James Bordner (jobordner@ucsd.edu) 
/// @date     Thu Apr  1 16:14:38 PDT 2010
/// @brief    [\ref Enzo] Declaration of EnzoMethodNull "null" solver

#ifndef ENZO_ENZO_METHOD_NULL_HPP
#define ENZO_ENZO_METHOD_NULL_HPP

class EnzoMethodNull : public Method {

  /// @class    EnzoMethodNull
  /// @ingroup  Enzo
  ///
  /// @brief [\ref Enzo] Null placeholder method, used for testing
  /// non-method aspects of Enzo-E and Cello, such as mesh adapting

public: // interface

  /// Create a new EnzoMethodNull object
  EnzoMethodNull ( double dt ) : Method(), dt_(dt) {
    const int ir = add_refresh(4,0,neighbor_leaf,sync_barrier,
			       enzo_sync_id_method_null);
    refresh(ir)->add_all_fields();
}

  EnzoMethodNull() : Method(), dt_ (std::numeric_limits<double>::max()) {}

  /// Charm++ PUP::able declarations
  PUPable_decl(EnzoMethodNull);
  
  /// Charm++ PUP::able migration constructor
  EnzoMethodNull (CkMigrateMessage *m)
    : Method (m), dt_(0.0)
  { }

  /// CHARM++ Pack / Unpack function
  void pup (PUP::er &p) 
  { TRACEPUP; Method::pup(p); p | dt_; }
  
  /// Apply the method to advance a block one timestep 
  virtual void compute( Block * block) throw()
  { block->compute_done(); }

  virtual std::string name () throw () 
  { return "null"; }

  /// Compute maximum timestep for this method
  virtual double timestep ( Block * block) const throw()
  { return dt_; }

protected: // attributes

  /// Time step
  double dt_;
};

#endif /* ENZO_ENZO_METHOD_NULL_HPP */
