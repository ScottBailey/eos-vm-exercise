#pragma once

// debug_visitor.hpp


#include <eosio/vm/interpret_visitor.hpp>
#include <eosio/vm/opcodes.hpp>


#define EOS_VM_ALL_OPS(VISITOR)                                         \
   EOS_VM_CONTROL_FLOW_OPS(VISITOR)                                     \
   EOS_VM_BR_TABLE_OP(VISITOR)                                          \
   EOS_VM_RETURN_OP(VISITOR)                                            \
   EOS_VM_CALL_OPS(VISITOR)                                             \
   EOS_VM_CALL_IMM_OPS(VISITOR)                                         \
   EOS_VM_PARAMETRIC_OPS(VISITOR)                                       \
   EOS_VM_VARIABLE_ACCESS_OPS(VISITOR)                                  \
   EOS_VM_MEMORY_OPS(VISITOR)                                           \
   EOS_VM_I32_CONSTANT_OPS(VISITOR)                                     \
   EOS_VM_I64_CONSTANT_OPS(VISITOR)                                     \
   EOS_VM_F32_CONSTANT_OPS(VISITOR)                                     \
   EOS_VM_F64_CONSTANT_OPS(VISITOR)                                     \
   EOS_VM_COMPARISON_OPS(VISITOR)                                       \
   EOS_VM_NUMERIC_OPS(VISITOR)                                          \
   EOS_VM_CONVERSION_OPS(VISITOR)                                       \
   EOS_VM_EXIT_OP(VISITOR)                                              \
   EOS_VM_ERROR_OPS(VISITOR)                                            \
   /* EOS_VM_ALL_OPS */


using namespace eosio::vm;

template<typename ExecutionContext>
struct debug_interpret_visitor : public eosio::vm::interpret_visitor<ExecutionContext> {

   using self = debug_interpret_visitor<ExecutionContext>;
   using parent = eosio::vm::interpret_visitor<ExecutionContext>;

   using parent::operator();

   /// constructor
   debug_interpret_visitor(ExecutionContext& ctx) : parent(ctx) {}


#define DEBUG_CODE(name, code)                                          \
   void operator()(const eosio::vm::EOS_VM_OPCODE_T(name)& op) { \
      std::cout << "Op: " << #name << " (" << std::hex << code << ") addr: " << std::dec << this->get_context().get_pc() << "\n"; \
      parent::operator()(op);                                           \
      this->get_context().print_stack();                                \
   } /* end DEBUG_CODE */


   EOS_VM_ALL_OPS(DEBUG_CODE)

#undef DEBUG_CODE

};
