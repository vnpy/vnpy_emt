""""""
import emt_typedef


class StructGenerator:
    """Struct生成器"""

    def __init__(self, filename: str, prefix: str):
        """Constructor"""
        self.filename: str = filename
        self.prefix: str = prefix
        self.typedef: dict = {}

        self.in_struct: bool = False

        self.load_constant()

    def load_constant(self) -> None:
        """"""
        for name in dir(emt_typedef):
            if "__" not in name:
                self.typedef[name] = getattr(emt_typedef, name)

    def run(self) -> None:
        """运行生成"""
        self.f_cpp = open(self.filename, "r", encoding="UTF-8")
        self.f_py = open(f"emt_{self.prefix}_struct.py", "w", encoding="UTF-8")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        self.f_py.close()

        print("Struct生成成功")

    def process_line(self, line: str):
        """处理每行"""
        # 忽略头部注释
        if line.startswith("///") or line.startswith("#") or line.startswith("//"):
            return

        line = line.replace("\t", "    ")
        line = line.replace("\n", "")

        # 过滤嵌套结构体
        if line.startswith("    ") and "};" in line:
            return
        # 结构体typedef
        elif line.startswith("typedef struct") and ";" in line:
            line = line.replace("typedef struct ", "")
            line = line[:line.index(";")]
            content = line.split(" ")
            content = [c for c in content if c]
            a, b = content
            new_line = f"{b} = {a}\n\n"
            self.f_py.write(new_line)
        elif line.startswith("typedef") and ";" in line:
            line = line.replace("typedef ", "")
            line = line[:line.index(";")]
            content = line.split(" ")
            content = [c for c in content if c]
            a, b = content
            new_line = f"{b} = {a}\n\n"
            self.f_py.write(new_line)
        # 结构体定义
        elif "struct" in line and not self.in_struct:
            self.in_struct = True
            line = line.replace("{", "")
            content = line.split(" ")
            content = [c for c in content if c]
            struct_name = content[-1]
            if struct_name[0] == "_":
                struct_name = struct_name[1:]
            new_line = f"{struct_name} = " + "{\n"
            self.f_py.write(new_line)
        # 结构体结束
        elif "}" in line and self.in_struct:
            self.in_struct = False
            self.f_py.write("}\n\n")
        # 过滤注释行和无关行
        elif line.startswith("///"):
            return
        # 结构体内容
        elif ";" in line and "}" not in line:
            if line.startswith("    ///"):
                return

            line = line[:line.index(";")]
            content = line.split(" ")
            content = [c for c in content if c]

            ptype = content[0]
            ptype = self.typedef.get(ptype, ptype)
            pname = content[1]
            if "[" in pname:
                pname = pname[:pname.index("[")]

            new_line = f'\t"{pname}": "{ptype}",\n'
            self.f_py.write(new_line)


if __name__ == "__main__":
    generator = StructGenerator("../include/emt/eoms_api_struct.h", "oms")
    generator.run()

    generator = StructGenerator("../include/emt/emt_quote_struct.h", "quote")
    generator.run()
