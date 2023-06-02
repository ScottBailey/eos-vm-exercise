#include <cstdint>
#include <string_view>

extern "C" {

   __attribute__((eosio_wasm_import))
   void print_string(const char*, uint32_t);
   __attribute__((eosio_wasm_import))
   void host_exit(uint32_t);

   void apply(uint64_t, uint64_t, uint64_t) {

      std::string_view msg = "Help! I'm stuck in the machine!\n";
      print_string(msg.data(), msg.size());
      host_exit(0);
   }
}
