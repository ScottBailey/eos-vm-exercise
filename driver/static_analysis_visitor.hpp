#pragma once

#include <eosio/vm/config.hpp>
#include <eosio/vm/base_visitor.hpp>

struct static_analysis : eosio::vm::base_visitor {

   using parent = eosio::vm::base_visitor;

   using parent::operator();


   std::size_t count() const { return m_count; }

   void operator()(const eosio::vm::i32_add_t& ) { ++m_count; }
   void operator()(const eosio::vm::i64_add_t& ) { ++m_count; }
   void operator()(const eosio::vm::f32_add_t& ) { ++m_count; }
   void operator()(const eosio::vm::f64_add_t& ) { ++m_count; }

   void operator()(const eosio::vm::i32_sub_t& ) { ++m_count; }
   void operator()(const eosio::vm::i64_sub_t& ) { ++m_count; }
   void operator()(const eosio::vm::f32_sub_t& ) { ++m_count; }
   void operator()(const eosio::vm::f64_sub_t& ) { ++m_count; }

   void operator()(const eosio::vm::i32_const_t& ) { ++m_count; }
   void operator()(const eosio::vm::i64_const_t& ) { ++m_count; }

private:
   std::size_t m_count = 0;
};
