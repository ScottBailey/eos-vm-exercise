#include <eosio/vm/backend.hpp>
#include <eosio/vm/error_codes.hpp>
#include <eosio/vm/host_function.hpp>
#include <eosio/vm/watchdog.hpp>

#include <filesystem>



// needed because CDT is stupid
template <typename T, std::size_t Align = alignof(T)>
using legacy_span = eosio::vm::argument_proxy<eosio::vm::span<T>, Align>;

struct base_host_functions {
   void set_blockchain_parameters_packed(legacy_span<const char>) {}
   uint32_t get_blockchain_parameters_packed(legacy_span<char>) { return 0; }
   int64_t set_proposed_producers(legacy_span<const char>) { return 0; }
   int32_t get_active_producers(legacy_span<uint64_t>) { return 0; }
   uint64_t current_time() { return 0; }
   void prints_l(legacy_span<const char> s) { std::cout << std::string(s.data(), s.size()); }
   void eosio_assert(bool test, const char* msg) {
      if (!test) {
         std::cerr << msg << std::endl;
         throw 0;  // Why zero?
      }
   }
};


struct host_functions : public base_host_functions {

   void print_hello() {
      std::cout << "Hello, world!" << std::endl;
   }

   void host_exit(uint32_t return_value) {
      static_assert(sizeof(int) >= sizeof(uint32_t), "int is too small to contain return value.");
      std::exit(return_value);
   }

   void print_string(const char* str, uint32_t sz) {
      static_assert(sizeof(size_t) >= sizeof(uint32_t), "size_t is too small to contain uint32_t sz.");
      fwrite(str, sizeof(char), sz, stdout);
   }

};


struct cnv : eosio::vm::type_converter<host_functions> {
   using type_converter::type_converter;
   using type_converter::from_wasm;
   EOS_VM_FROM_WASM(bool, (uint32_t value)) { return value ? 1 : 0; }
   EOS_VM_FROM_WASM(char*, (void* ptr)) { return static_cast<char*>(ptr); }
   EOS_VM_FROM_WASM(const char*, (void* ptr)) { return static_cast<char*>(ptr); }
};


int main(int argc, char** argv) {
   eosio::vm::wasm_allocator wa;
   using rhf_t = eosio::vm::registered_host_functions<host_functions, eosio::vm::execution_interface, cnv>;
   using backend_t = eosio::vm::backend<rhf_t>;

   rhf_t::add<&host_functions::print_hello>("env", "print_hello");
   rhf_t::add<&host_functions::host_exit>("env", "host_exit");
   rhf_t::add<&host_functions::print_string>("env", "print_string");

   // once again needed because of CDT
   rhf_t::add<&host_functions::eosio_assert>("env", "eosio_assert");
   rhf_t::add<&host_functions::current_time>("env", "current_time");
   rhf_t::add<&host_functions::set_blockchain_parameters_packed>("env", "set_blockchain_parameters_packed");
   rhf_t::add<&host_functions::get_blockchain_parameters_packed>("env", "get_blockchain_parameters_packed");
   rhf_t::add<&host_functions::set_proposed_producers>("env", "set_proposed_producers");
   rhf_t::add<&host_functions::get_active_producers>("env", "get_active_producers");
   rhf_t::add<&host_functions::prints_l>("env", "prints_l");

   if (argc < 2) {
      std::cerr << "Please provide a wasm file." << std::endl;
      return -1;
   }

   std::filesystem::path wasm_path(argv[1]);

   std::error_code sec;
   auto sz = std::filesystem::file_size(wasm_path,sec);
   if(sec) {
      std::cerr << sec << "\n";
      return 1;
   }

   std::vector<uint8_t> wasm_bytes;
   wasm_bytes.resize(sz);

   std::ifstream wasm_file(wasm_path, std::ios::binary);
   if (!wasm_file) {
      std::cerr << "Unable to open wasm file." << std::endl;
      return -1;
   }
   wasm_file.read(reinterpret_cast<char*>(wasm_bytes.data()), sz);

   try {
      host_functions hf;
      backend_t bkend(wasm_bytes, hf, &wa);

      bkend(hf, "env", "apply", (uint64_t)0, (uint64_t)0, (uint64_t)0);
   } catch (const eosio::vm::exception& ex) {
      std::cerr << ex.detail() << std::endl;
      return -1;
   }
   return 0;
}
