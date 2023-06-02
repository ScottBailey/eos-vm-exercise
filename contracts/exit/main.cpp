#include <cstdint>

extern "C" {
   __attribute__((eosio_wasm_import))
   void host_exit(uint32_t);

   void apply(uint64_t, uint64_t, uint64_t) {
      host_exit(19);
   }
}
