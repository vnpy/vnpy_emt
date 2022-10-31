""""""
import importlib
from typing import Dict


class ApiGenerator:
    """API生成器"""""

    def __init__(self, filename: str, prefix: str, name: str, class_name: str):
        """Constructor"""
        self.filename = filename
        self.prefix = prefix
        self.name = name
        self.class_name = class_name

        self.callbacks: Dict[str, dict] = {}
        self.functions: Dict[str, dict] = {}
        self.lines: Dict[str, str] = {}

        self.structs: Dict[str, dict] = {}
        self.load_struct()

    def load_struct(self):
        """加载Struct"""
        module_names = ["emt_oms_struct", "emt_quote_struct"]

        for module_name in module_names:
            module = importlib.import_module(module_name)

            for name in dir(module):
                if "__" not in name:
                    self.structs[name] = getattr(module, name)

        # self.structs["EMTST"] = self.structs["EMTSpecificTickerStruct"]
        # self.structs["EMTMD"] = self.structs["EMTMarketDataStruct"]
        # self.structs["EMTQSI"] = self.structs["EMTQuoteStaticInfo"]
        # self.structs["EMTOB"] = self.structs["EMTOrderBookStruct"]
        # self.structs["EMTTBT"] = self.structs["EMTTickByTickStruct"]
        # self.structs["EMTTPI"] = self.structs["EMTTickerPriceInfo"]
        # self.structs["EMTQFI"] = self.structs["EMTQuoteFullInfo"]
        self.structs["EMTRI"] = {
            "error_id": "int32_t",
            "error_msg": "char"
        }

    def run(self):
        """运行生成"""
        self.f_cpp = open(self.filename, "r", encoding="UTF-8")

        for line in self.f_cpp:
            self.process_line(line)

        self.f_cpp.close()

        self.generate_header_on()
        self.generate_header_function()

        self.generate_source_callback()
        self.generate_source_function()
        self.generate_source_on()
        self.generate_source_module()

        print("API生成成功")

    def process_line(self, line: str):
        """处理每行"""
        line = line.replace(";", "")
        line = line.replace("\n", "")
        line = line.replace("\t", "")
        line = line.replace("{}", "")

        if "virtual void On" in line:
            self.process_callback(line)
        elif "virtual int Query" in line:
            self.process_function(line)

    def process_callback(self, line: str):
        """处理回掉函数"""
        name = line[line.index("On"):line.index("(")]
        self.lines[name] = line

        d = self.generate_arg_dict(line)
        self.callbacks[name] = d

    def process_function(self, line: str):
        """处理主动函数"""
        name = line[line.index("Query"):line.index("(")]

        d = self.generate_arg_dict(line)
        self.functions[name] = d

    def generate_arg_dict(self, line: str):
        """生成参数字典"""
        args_str = line[line.index("(") + 1:line.index(")")]
        if not args_str:
            return {}
        args = args_str.split(",")

        d = {}
        for arg in args:

            words = arg.split(" ")
            words = [word for word in words if word]

            ptype = words[-2]

            if "=" in words[-2]:
                ptype = words[-4].replace("*", "")
                name = words[-3].replace("*", "")
            elif "*" in words[-2]:
                ptype = words[-2].replace("*", "")
                name = words[-1].replace("*", "")
            else:
                name = words[-1].replace("*", "")

            if "[" in name:
                name = name.split("[")[0]

            d[name] = ptype
        return d

    def generate_header_on(self):
        """"""
        filename = f"{self.prefix}_{self.name}_header_on.h"
        with open(filename, "w") as f:
            for name, d in self.callbacks.items():
                name = name.replace("On", "on")
                args_list = []

                for pname, ptype in d.items():
                    print(pname, ptype)
                    if ptype == "EMTRI":
                        args_list.append("const dict &error")
                    elif ptype in self.structs:
                        args_list.append("const dict &data")
                    elif ptype.startswith("EMT_"):
                        args_list.append(f"int {pname}")
                    else:
                        args_list.append(f"{ptype} {pname}")

                args_str = ", ".join(args_list)
                line = f"virtual void {name}({args_str}) {{}};\n\n"

                f.write(line)

    def generate_header_function(self):
        """"""
        filename = f"{self.prefix}_{self.name}_header_function.h"
        with open(filename, "w") as f:
            for key, d in self.functions.items():

                args_list = []
                for pname, ptype in d.items():
                    if ptype in self.structs:
                        args_list.append("const dict &req")
                    elif ptype.startswith("EMT_"):
                        args_list.append(f"int {pname}")
                    else:
                        args_list.append(f"{ptype} {pname}")

                content = ", ".join(args_list)

                name = key.replace("Query", "query")
                line = f"int {name}({content});\n\n"
                f.write(line)

    def generate_source_callback(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_callback.cpp"
        with open(filename, "w") as f:
            for name, d in self.callbacks.items():
                on_name = name.replace("On", "on")

                line = self.lines[name]
                f.write(line.replace("virtual void ",
                                     f"void {self.class_name}::") + "\n")
                f.write("{\n")
                f.write("\tgil_scoped_acquire acquire;\n")

                args = []

                for pname, ptype in d.items():
                    if ptype == "EMTRI":
                        args.append("error")

                        f.write("\tdict error;\n")
                        f.write(f"\tif ({pname})\n")
                        f.write("\t{\n")

                        struct_fields = self.structs[ptype]
                        for struct_field, struct_type in struct_fields.items():
                            f.write(
                                f"\t\terror[\"{struct_field}\"] = {pname}->{struct_field};\n")

                        f.write("\t}\n")
                    elif ptype in self.structs:
                        args.append("data")

                        f.write("\tdict data;\n")
                        f.write(f"\tif ({pname})\n")
                        f.write("\t{\n")

                        struct_fields = self.structs[ptype]
                        for struct_field, struct_type in struct_fields.items():
                            if struct_type == "enum":
                                f.write(
                                    f"\t\tdata[\"{struct_field}\"] = (int) {pname}->{struct_field};\n")
                            else:
                                f.write(
                                    f"\t\tdata[\"{struct_field}\"] = {pname}->{struct_field};\n")

                        f.write("\t}\n")
                    else:
                        args.append(pname)

                args_str = ", ".join(args)
                f.write(f"\tthis->{on_name}({args_str});\n")

                f.write("};\n\n")

    def generate_source_function(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_function.cpp"
        with open(filename, "w") as f:
            for name, d in self.functions.items():
                req_name = name.replace("Query", "query")

                args_list = []
                call_args = []
                for pname, ptype in d.items():
                    if ptype == "int" or ptype.startswith("EMT_"):
                        args_list.append(f"int {pname}")
                        call_args.append(pname)
                    elif ptype in self.structs:
                        args_list.append("const dict &req")
                        call_args.append("&myreq")
                    else:
                        args_list.append(f"{ptype} {pname}")
                        call_args.append(pname)

                content = ", ".join(args_list)

                f.write(f"int {self.class_name}::{req_name}({content})\n")
                f.write("{\n")

                for pname, ptype in d.items():
                    if ptype == "int" or ptype.startswith("EMT_"):
                        args_list.append(f"int {pname}")
                    elif ptype in self.structs:
                        f.write(f"\t{ptype} myreq;\n")
                        f.write("\tmemset(&myreq, 0, sizeof(myreq));\n")

                        struct_fields = self.structs[ptype]

                        for struct_field, struct_type in struct_fields.items():
                            func_name = f"get{struct_type.capitalize()}"
                            if struct_type == "char":
                                func_name = "getString"
                                line = f'\t{func_name}(req, "{struct_field}", myreq.{struct_field});\n'
                            else:
                                line = f'\t{func_name}(req, "{struct_field}", &myreq.{struct_field});\n'
                            f.write(line)
                    else:
                        args_list.append(f"{ptype} {pname}")

                f.write(f"\tint i = this->api->{name}({', '.join(call_args)});\n")
                f.write("\treturn i;\n")
                f.write("};\n\n")

    def generate_source_on(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_on.cpp"
        with open(filename, "w") as f:
            for name, d in self.callbacks.items():
                on_name = name.replace("On", "on")

                args = []
                bind_args = ["void", self.class_name, on_name]

                for pname, ptype in d.items():
                    if ptype == "EMTRI":
                        args.append("const dict &error")
                        bind_args.append("error")
                    elif ptype in self.structs:
                        args.append("const dict &data")
                        bind_args.append("data")
                    elif ptype.startswith("EMT_"):
                        args.append(f"int {pname}")
                        bind_args.append(pname)
                    else:
                        args.append(f"{ptype} {pname}")
                        bind_args.append(pname)

                args_str = ", ".join(args)
                bind_args_str = ", ".join(bind_args)

                f.write(f"void {on_name}({args_str}) override\n")
                f.write("{\n")
                f.write("\ttry\n")
                f.write("\t{\n")
                f.write(f"\t\tPYBIND11_OVERLOAD({bind_args_str});\n")
                f.write("\t}\n")
                f.write("\tcatch (const error_already_set &e)\n")
                f.write("\t{\n")
                f.write("\t\tcout << e.what() << endl;\n")
                f.write("\t}\n")
                f.write("};\n\n")

    def generate_source_module(self):
        """"""
        filename = f"{self.prefix}_{self.name}_source_module.cpp"
        with open(filename, "w") as f:
            for name in self.functions.keys():
                name = name.replace("Query", "query")
                f.write(f".def(\"{name}\", &{self.class_name}::{name})\n")

            f.write("\n")

            for name in self.callbacks.keys():
                name = name.replace("On", "on")
                f.write(f".def(\"{name}\", &{self.class_name}::{name})\n")

            f.write(";\n")


if __name__ == "__main__":
    md_generator = ApiGenerator("../include/emt/emt_quote_api.h", "emt", "md", "MdApi")
    md_generator.run()

    td_generator = ApiGenerator("../include/emt/emt_trader_api.h", "emt", "td", "TdApi")
    td_generator.run()
