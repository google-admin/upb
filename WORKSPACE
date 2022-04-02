workspace(name = "upb")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("//bazel:workspace_deps.bzl", "upb_deps")
load("//bazel:workspace_defs.bzl", "system_python")

upb_deps()

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()

http_archive(
    name = "lua",
    build_file = "//bazel:lua.BUILD",
    sha256 = "b9e2e4aad6789b3b63a056d442f7b39f0ecfca3ae0f1fc0ae4e9614401b69f4b",
    strip_prefix = "lua-5.2.4",
    urls = [
        "https://mirror.bazel.build/www.lua.org/ftp/lua-5.2.4.tar.gz",
        "https://www.lua.org/ftp/lua-5.2.4.tar.gz",
    ],
)

http_archive(
     name = "com_google_googletest",
     urls = ["https://github.com/google/googletest/archive/b6cd405286ed8635ece71c72f118e659f4ade3fb.zip"],  # 2019-01-07
     strip_prefix = "googletest-b6cd405286ed8635ece71c72f118e659f4ade3fb",
     sha256 = "ff7a82736e158c077e76188232eac77913a15dac0b22508c390ab3f88e6d6d86",
)

http_archive(
    name = "com_github_google_benchmark",
    urls = ["https://github.com/google/benchmark/archive/0baacde3618ca617da95375e0af13ce1baadea47.zip"],
    strip_prefix = "benchmark-0baacde3618ca617da95375e0af13ce1baadea47",
    sha256 = "62e2f2e6d8a744d67e4bbc212fcfd06647080de4253c97ad5c6749e09faf2cb0",
)

http_archive(
    name = "com_google_googleapis",
    urls = ["https://github.com/googleapis/googleapis/archive/refs/heads/master.zip"],
    build_file = "//benchmarks:BUILD.googleapis",
    strip_prefix = "googleapis-master",
    patch_cmds = ["find google -type f -name BUILD.bazel -delete"],
)

system_python(
    name = "system_python"
)

register_toolchains("@system_python//:python_toolchain")

http_archive(
    name = "rules_fuzzing",
    sha256 = "23bb074064c6f488d12044934ab1b0631e8e6898d5cf2f6bde087adb01111573",
    strip_prefix = "rules_fuzzing-0.3.1",
    urls = ["https://github.com/bazelbuild/rules_fuzzing/archive/v0.3.1.zip"],
)

limited_api_build_file = """
cc_library(
    name = "python_headers",
    hdrs = glob(["**/Include/**/*.h"]),
    strip_include_prefix = "Python-%s/Include",
    visibility = ["//visibility:public"],
)
"""

http_archive(
    name = "python-3.7.0",
    sha256 ="85bb9feb6863e04fb1700b018d9d42d1caac178559ffa453d7e6a436e259fd0d",
    urls = ["https://www.python.org/ftp/python/3.7.0/Python-3.7.0.tgz"],
    build_file_content = limited_api_build_file % "3.7.0",
    patch_cmds = [
      "echo \#define SIZEOF_WCHAR_T 4 > Python-3.7.0/Include/pyconfig.h",
    ],
)

http_archive(
    name = "python-3.10.0",
    sha256 = "c4e0cbad57c90690cb813fb4663ef670b4d0f587d8171e2c42bd4c9245bd2758",
    urls = ["https://www.python.org/ftp/python/3.10.0/Python-3.10.0.tgz"],
    build_file_content = limited_api_build_file % "3.10.0",
    patch_cmds = [
      "echo \#define SIZEOF_WCHAR_T 4 > Python-3.10.0/Include/pyconfig.h",
    ],
)

full_api_build_file = """
cc_import(
    name = "python",
    hdrs = glob(["**/*.h"]),
    shared_library = "python{0}.dll",
    interface_library = "libs/python{0}.lib",
    visibility = ["@upb//python:__pkg__"],
)
"""

http_archive(
    name = "nuget_python_x86-64_3.7.0",
    urls = ["https://www.nuget.org/api/v2/package/python/3.7.0"],
    sha256 = "66eb796a5bdb1e6787b8f655a1237a6b6964af2115b7627cf4f0032cf068b4b2",
    strip_prefix = "tools",
    build_file_content = full_api_build_file.format(37),
    type = "zip",
    patch_cmds = ["cp -r include/* ."],
)

http_archive(
    name = "nuget_python_i686_3.7.0",
    urls = ["https://www.nuget.org/api/v2/package/pythonx86/3.7.0"],
    sha256 = "a8bb49fa1ca62ad55430fcafaca1b58015e22943e66b1a87d5e7cef2556c6a54",
    strip_prefix = "tools",
    build_file_content = full_api_build_file.format(37),
    type = "zip",
    patch_cmds = ["cp -r include/* ."],
)

http_archive(
    name = "nuget_python_x86-64_3.8.0",
    urls = ["https://www.nuget.org/api/v2/package/python/3.8.0"],
    sha256 = "96c61321ce90dd053c8a04f305a5f6cc6d91350b862db34440e4a4f069b708a0",
    strip_prefix = "tools",
    build_file_content = full_api_build_file.format(38),
    type = "zip",
    patch_cmds = ["cp -r include/* ."],
)

http_archive(
    name = "nuget_python_i686_3.8.0",
    urls = ["https://www.nuget.org/api/v2/package/pythonx86/3.8.0"],
    sha256 = "87a6481f5eef30b42ac12c93f06f73bd0b8692f26313b76a6615d1641c4e7bca",
    strip_prefix = "tools",
    build_file_content = full_api_build_file.format(38),
    type = "zip",
    patch_cmds = ["cp -r include/* ."],
)

http_archive(
    name = "nuget_python_x86-64_3.9.0",
    urls = ["https://www.nuget.org/api/v2/package/python/3.9.0"],
    sha256 = "6af58a733e7dfbfcdd50d55788134393d6ffe7ab8270effbf724bdb786558832",
    strip_prefix = "tools",
    build_file_content = full_api_build_file.format(39),
    type = "zip",
    patch_cmds = ["cp -r include/* ."],
)

http_archive(
    name = "nuget_python_i686_3.9.0",
    urls = ["https://www.nuget.org/api/v2/package/pythonx86/3.9.0"],
    sha256 = "229abecbe49dc08fe5709e0b31e70edfb3b88f23335ebfc2904c44f940fd59b6",
    strip_prefix = "tools",
    build_file_content = full_api_build_file.format(39),
    type = "zip",
    patch_cmds = ["cp -r include/* ."],
)

load("@rules_fuzzing//fuzzing:repositories.bzl", "rules_fuzzing_dependencies")

rules_fuzzing_dependencies()

load("@rules_fuzzing//fuzzing:init.bzl", "rules_fuzzing_init")

rules_fuzzing_init()
