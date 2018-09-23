cc_library(
    name = "tracer",
    srcs = [
        "camera.cc",
        "hitable_list.cc",
        "math_util.cc",
        "sphere.cc",
    ],
    hdrs = [
        "camera.h",
        "hitable.h",
        "hitable_list.h",
        "math_util.h",
        "memory_util.h",
        "ray.h",
        "sphere.h",
    ],
    deps = ["//third_party/eigen3"],
    copts = ["-O3"],
)

# TODO(nloomis): unit tests for ray.h

cc_binary(
	name = "trace",
	srcs = ["trace.cc"],
	deps = [
	  ":tracer",
	  "//third_party/eigen3"
	 ],
)