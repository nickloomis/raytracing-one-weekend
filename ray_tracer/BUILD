cc_library(
    name = "tracer",
    srcs = [
        "camera.cc",
        "hitable_list.cc",
        "image_util.cc",
        "material.cc",
        "math_util.cc",
        "sphere.cc",
    ],
    hdrs = [
        "camera.h",
        "hitable.h",
        "hitable_list.h",
        "image_util.h",
        "material.h",
        "math_util.h",
        "memory_util.h",
        "ray.h",
        "sphere.h",
    ],
    deps = ["//third_party/eigen3"],
    copts = ["-O3"],
)

cc_binary(
	name = "trace",
	srcs = ["trace.cc"],
	deps = [
	  ":tracer",
	  "//third_party/eigen3"
	 ],
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
