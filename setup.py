import platform

from setuptools import Extension, setup


def get_ext_modules() -> list:
    """
    获取三方模块
    Linux和Windows需要编译封装接口
    Mac由于缺乏二进制库支持无法使用
    """
    if platform.system() != "Windows":
        return []

    extra_compile_flags = ["-O2", "-MT"]
    extra_link_args = []
    runtime_library_dirs = []

    vnemtmd = Extension(
        name="vnpy_emt.api.vnemtmd",
        sources=["vnpy_emt/api/vnemt/vnemtmd/vnemtmd.cpp"],
        define_macros=[("NOMINMAX", None)],
        include_dirs=["vnpy_emt/api/include", "vnpy_emt/api/vnemt"],
        library_dirs=["vnpy_emt/api/libs", "vnpy_emt/api"],
        libraries=["emt_quote_api", "emt_trader_api_c", "emt_api"],
        extra_compile_args=extra_compile_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        language="cpp",
    )

    vnemttd = Extension(
        name="vnpy_emt.api.vnemttd",
        sources=["vnpy_emt/api/vnemt/vnemttd/vnemttd.cpp"],
        define_macros=[("NOMINMAX", None)],
        include_dirs=["vnpy_emt/api/include", "vnpy_emt/api/vnemt"],
        library_dirs=["vnpy_emt/api/libs", "vnpy_emt/api"],
        libraries=["emt_quote_api", "emt_trader_api_c", "emt_api"],
        extra_compile_args=extra_compile_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        language="cpp",
    )

    return [vnemttd, vnemtmd]


setup(ext_modules=get_ext_modules())
