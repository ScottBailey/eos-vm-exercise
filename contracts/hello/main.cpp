#include <cstdint>

extern "C" {
   __attribute__((eosio_wasm_import))
   void print_hello();

   void apply(uint64_t, uint64_t, uint64_t) {
      print_hello();
   }
}
