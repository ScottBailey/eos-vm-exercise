#pragma once

// counting_visitor.hpp


#include <eosio/vm/interpret_visitor.hpp>
#include <eosio/vm/opcodes.hpp>
#include <array>

#if !defined(EOS_VM_ALL_OPS)
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
#endif


using namespace eosio::vm;

template<typename ExecutionContext>
struct counting_visitor : public eosio::vm::interpret_visitor<ExecutionContext> {

   using self = counting_visitor<ExecutionContext>;
   using parent = eosio::vm::interpret_visitor<ExecutionContext>;

   using parent::operator();

   /// constructor
   counting_visitor(ExecutionContext& ctx) : parent(ctx) {
      std::cout << "Enter counting_visitor constructor.\n";
      m_count.fill(0);
   }

   auto counts() const { return m_count; }

#define DEBUG_CODE(name, code)                                          \
   void operator()(const eosio::vm::EOS_VM_OPCODE_T(name)& op) { \
      /*std::cout << "Op: " << #name << " (" << std::hex << code << ") addr: " << std::dec << this->get_context().get_pc() << "\n";*/ \
      ++m_count[code];                                                 \
      std::cout << "Op: " << #name << " called " << m_count[code] << " times.\n"; \
      parent::operator()(op);                                           \
      /*this->get_context().print_stack();*/                            \
   } /* end DEBUG_CODE */


   EOS_VM_ALL_OPS(DEBUG_CODE)

#undef DEBUG_CODE

   void dump() const {
      eosio::vm::opcode_utils temp;
      std::cout << "\n=======================\n";
      for(uint16_t i=0; i < m_count.size(); ++i) {
         if(m_count[i] > 0) {
            std::cout << "op: " << temp.opcode_map.at(i) << " (" << std::hex << i << std::hex << ") count: " << m_count[i] << "\n";
         }
      }
      std::cout << "=======================\n";
   }

private:
   std::array<std::size_t,256> m_count;

};
