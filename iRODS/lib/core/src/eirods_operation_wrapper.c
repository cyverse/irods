/* -*- mode: c++; fill-column: 132; c-basic-offset: 4; indent-tabs-mode: nil -*- */

// =-=-=-=-=-=-=-
// My Includes
#include "eirods_operation_wrapper.h"

// =-=-=-=-=-=-=-
// STL Includes
#include <iostream>

// =-=-=-=-=-=-=-
// Boost Includes

namespace eirods {

    // =-=-=-=-=-=-=-
    // public - ctor
    operation_wrapper::operation_wrapper( ) : operation_( 0 ) {
    } // default ctor

    // =-=-=-=-=-=-=-
    // public - ctor with opreation
    operation_wrapper::operation_wrapper( 
        oper_rule_exec_mgr_ptr _rule_exec, 
        const std::string&     _inst_name,
        const std::string&     _op_name,
        plugin_operation _op ) : 
        operation_( _op ),
        rule_exec_mgr_( _rule_exec ),
        instance_name_( _inst_name ),
        operation_name_( _op_name ) {
    } // ctor

    // =-=-=-=-=-=-=-
    // public - cctor
    operation_wrapper::operation_wrapper( 
        const operation_wrapper& _rhs ) {
        rule_exec_mgr_  = _rhs.rule_exec_mgr_;
        operation_      = _rhs.operation_;
        instance_name_  = _rhs.instance_name_;
        operation_name_ = _rhs.operation_name_;
    } // cctor
 
    // =-=-=-=-=-=-=-
    // public - dtor
    operation_wrapper::~operation_wrapper( ) {
    } // dtor
   
    // =-=-=-=-=-=-=-
    // public - assignment for stl container
    operation_wrapper& operation_wrapper::operator=( 
        const operation_wrapper& _rhs ) {
        rule_exec_mgr_  = _rhs.rule_exec_mgr_;
        operation_      = _rhs.operation_;
        instance_name_  = _rhs.instance_name_;
        operation_name_ = _rhs.operation_name_;
        return *this;
    } // operator=
    
    // END operation_wrapper
    // =-=-=-=-=-=-=-

}; // namespace eirods



