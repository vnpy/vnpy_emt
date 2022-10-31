import platform

from setuptools import Extension, setup


def get_ext_modules() -> list:
    """
    获取三方模块
    Linux和Windows需要编译封装接口
    Mac由于缺乏二进制库支持无法使用
    """
    if platform.system() == "Linux":
        extra_compile_flags = [
            "-std=c++17",
            "-O3",
            "-Wno-delete-incomplete",
            "-Wno-sign-compare",
        ]
        extra_link_args = ["-lstdc++"]
        runtime_library_dirs = ["$ORIGIN"]

    elif platform.system() == "Windows":
        extra_compile_flags = ["-O2", "-MT"]
        extra_link_args = []
        runtime_library_dirs = []

    else:
        return []

    vnemtmd = Extension(
        "vnpy_emt.api.vnemtmd",
        [
            "vnpy_emt/api/vnemt/vnemtmd/vnemtmd.cpp",
        ],
        include_dirs=["vnpy_emt/api/include",
                      "vnpy_emt/api/vnemt"],
        define_macros=[("NOMINMAX", None)],
        undef_macros=[],
        library_dirs=["vnpy_emt/api/libs", "vnpy_emt/api"],
        libraries=["emt_quote_api", "emt_trader_api_c", "emt_api"],
        extra_compile_args=extra_compile_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        depends=[],
        language="cpp",
    )

    vnemttd = Extension(
        "vnpy_emt.api.vnemttd",
        [
            "vnpy_emt/api/vnemt/vnemttd/vnemttd.cpp",
        ],
        include_dirs=["vnpy_emt/api/include",
                      "vnpy_emt/api/vnemt"],
        define_macros=[("NOMINMAX", None)],
        undef_macros=[],
        library_dirs=["vnpy_emt/api/libs", "vnpy_emt/api"],
        libraries=["emt_quote_api", "emt_trader_api_c", "emt_api"],
        extra_compile_args=extra_compile_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        depends=[],
        language="cpp",
    )

    return [vnemttd, vnemtmd]


setup(
    ext_modules=get_ext_modules(),
)
