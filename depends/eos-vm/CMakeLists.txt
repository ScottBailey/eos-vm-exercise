
# Don't build the tools.
set(ENABLE_TOOLS OFF CACHE BOOL "Enable tools")

FetchContent_Declare(
   eos-vm
   SYSTEM
   GIT_REPOSITORY https://github.com/antelopeio/eos-vm
   GIT_TAG 329db27d888dce32c96b4f209cdea45f1d07e5e7
   PATCH_COMMAND patch -p1 < ${CMAKE_CURRENT_SOURCE_DIR}/cmake-system.patch
)
FetchContent_MakeAvailable(eos-vm)
