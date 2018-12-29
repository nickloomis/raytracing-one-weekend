package(
    default_visibility = ["//visibility:private"],
)

cc_library(
    name = "ppm",
    visibility = [
        "//ray_tracer:__pkg__",
    ],
    srcs = [
        "eigen_rgb_image_wrapper.cc",
        "image_util.cc",
        "ppm_writer.cc",
    ],
    hdrs = [
        "eigen_rgb_image_wrapper.h",
        "image_util.h",
        "ppm_writer.h",
    ],
    deps = [
        "//third_party/eigen3",
    ],
    copts = ["-O3"],
)

cc_binary(
    name = "ppm-hello-world",
    srcs = ["ppm_hello_world.cc"],
    deps = [
      "//third_party/eigen3",
    ],
    copts = ["-O3"],
)

