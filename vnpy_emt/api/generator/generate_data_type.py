class DataTypeGenerator:
    """DataType生成器"""

    def __init__(self, filename: str, prefix: str):
        """Constructor"""
        self.filename: str = filename
        self.prefix: str = prefix
        self.count: int = 0

        self.in_enum: bool = False
        self.enum_value: int = 0

    def run(self):
        """主函数"""
        self.f_cpp = open(self.filename, "r", encoding="UTF-8")
        self.f_define = open(f"{self.prefix}_constant.py", "w", encoding="UTF-8")
        self.f_typedef = open(f"{self.prefix}_typedef.py", "w", encoding="UTF-8")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()
        self.f_define.close()
        self.f_typedef.close()

        print("DataType生成完毕")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace("\n", "")
        line = line.replace(";", "")
        line = line.replace("\t", "    ")

        # 注释行
        if line[:3] == "///":
            return
        # 常量定义
        elif line.startswith("#define"):
            self.process_define(line)
        # 枚举定义
        elif "enum" in line:
            self.process_enum(line)
        # 枚举结束
        elif "}" in line:
            self.in_enum = False
        # 枚举内容
        elif self.in_enum and "XTP_" in line:
            self.process_content(line)
        # 类型定义
        elif line.startswith("typedef"):
            self.process_typedef(line)
        # # 枚举值内容
        # elif "//<" in line:
        #     if "=" in line:
        #         name = line.split("=")[0].strip()
        #     elif "," in line:
        #         name = line.split(",")[0].strip()
        #     else:
        #         name = line.split("///")[0].strip()

        #     py_type = "int"
        #     new_line = f"    \"{name}\": \"{py_type}\",\n"
        #     self.f_struct.write(new_line)

    def process_enum(self, line: str):
        """处理枚举值定义"""
        line = line.replace("\n", " ")
        line = line.replace("\r", " ")
        line = line.replace("typedef", "")
        line = line.replace("{", "")
        content = line.split(" ")
        content = [c for c in content if c]

        name = content[-1]
        type_ = content[0]
        new_line = f"{name} = \"{type_}\"\n"
        self.f_typedef.write(new_line)

        self.in_enum = True

    def process_define(self, line: str):
        """处理常量定义"""
        words = line.split(" ")
        words = [word for word in words if word]
        if len(words) < 3:
            return

        name = words[1]
        value = words[2]

        new_line = f"{name} = {value}\n"
        self.f_define.write(new_line)

    def process_typedef(self, line: str):
        """处理类型定义"""
        word = line.split(" ")[2]
        name = word.split("[")[0]
        typedef = line.split(" ")[1]

        new_line = f"{name} = \"{typedef}\"\n"
        self.f_typedef.write(new_line)

    def process_content(self, line: str):
        """处理枚举值内容"""
        if "," in line:
            line = line[:line.index(",")]

        if "///" in line:
            line = line[:line.index("///")]

        line = line.replace(" ", "")
        if "=" in line:
            content = line.split("=")
            name = content[0]
            value = content[1]
            self.enum_value = int(value)
        else:
            name = line
            self.enum_value += 1
            value = self.enum_value

        new_line = f"{name} = {value}\n"
        self.f_define.write(new_line)


if __name__ == "__main__":
    generator = DataTypeGenerator("../include/emt/emt_api_data_type.h", "emt")
    generator.run()
