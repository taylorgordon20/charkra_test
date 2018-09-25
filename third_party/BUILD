package(default_visibility = ["//visibility:public"])

cc_library(
  name = "lib",
  hdrs = glob(["include/**"]),
  includes = ["include/"],
  deps = [
    ":chakracore",
  ],
)

cc_import(
  name = "chakracore",
  interface_library = "lib/Chakracore.lib",
  shared_library = "bin/ChakraCore.dll",
)
