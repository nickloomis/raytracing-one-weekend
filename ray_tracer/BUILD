cc_library(
    name = "tracer",
    srcs = [
        "camera.cc",
        "hitable_list.cc",
        "material.cc",
        "math_util.cc",
        "sphere.cc",
    ],
    hdrs = [
        "camera.h",
        "hitable.h",
        "hitable_list.h",
        "material.h",
        "math_util.h",
        "memory_util.h",
        "ray.h",
        "sphere.h",
    ],
    deps = [
        "//third_party/eigen3",
    ],
    copts = ["-O3"],
)

cc_library(
    name = "progress_bar",
    srcs = ["progress_bar.cc"],
    hdrs = ["progress_bar.h"],
    copts = ["-O3"],
)

cc_binary(
	name = "trace",
	srcs = ["trace.cc"],
	deps = [
      ":progress_bar",
	  ":tracer",
      "@com_github_gflags_gflags//:gflags",
      "//ppm:ppm",
	  "//third_party/eigen3",
	],
    copts = ["-O3", "-fopenmp"],
    linkopts = ["-fopenmp"],
)

# Template for unit tests:
cc_test(
	name = "unit_test",
	srcs = ["unit_test.cc"],
	copts = ["-Iexternal/gtest/include"],
	deps = [
      "@gtest//:main",
	],
)
