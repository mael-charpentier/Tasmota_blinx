def generate_cpp_functions(prefix_dict):
    cpp_code = ""

    # Helper function to generate the function name based on the prefix
    def get_function_name(prefix):
        return "blinxFindSensor" + "".join([c.upper() for c in prefix])

    # Function to generate C++ code for a given prefix
    def generate_function(prefix, remaining_dict):
        func_name = get_function_name(prefix)
        cpp_code = f"int {func_name}(String input, size_t l, uint32_t function, uint32_t index_csv){{\n"
        cpp_code += f"    if (l == {len(prefix)}) {{ return -1; }}\n"

        first_chars = set(key[len(prefix)] for key in remaining_dict.keys() if len(key) > len(prefix))

        for char in sorted(first_chars):
            matching_keys = [key for key in remaining_dict.keys() if key.startswith(prefix + char)]
            cpp_code += f"    else if (input[{len(prefix)}] == '{char}'){{\n"
            match = False
            for key in matching_keys:
                if len(key) == len(prefix) + 1:
                    remaining_dict = {k: v for k, v in prefix_dict.items() if k.startswith(prefix + char)}
                    cpp_code += f"        if (l == {len(key)}){{\n"
                    cpp_code += f"            return Xsns{remaining_dict[key][0]}(function, index_csv, {remaining_dict[key][1]});\n" # TODO phantom
                    cpp_code += f"        }} else {{\n"
                    if len(remaining_dict) > 1:
                        next_func_name = get_function_name(prefix + char)
                        cpp_code += f"            return {next_func_name}(input, l, function, index_csv);\n"
                    else:
                        cpp_code += f"            return -1;\n"
                    cpp_code += "        }\n"
                    match = True
                
            if not match:
                next_func_name = get_function_name(prefix + char)
                cpp_code += f"        return {next_func_name}(input, l, function, index_csv);\n"
            cpp_code += "    }\n"
        cpp_code += f"    return -1;\n"
        cpp_code += "}\n\n"
        return cpp_code

    def all_sensor():
        cpp_code = "\n\n\n"
        cpp_code += "int blinxFindSensorAll(uint32_t function, uint32_t index_csv){\n"
        cpp_code += "   int sum = 0;\n"
        for id in prefix_dict.values():
            cpp_code += f"   sum += Xsns{id[0]}(function, index_csv, {id[1]}) + 1;\n" # TODO phantom
        cpp_code += "   return sum;\n"
        cpp_code += "}\n\n"
        return cpp_code
            
        
    

    # Generate functions starting from the root prefix
    prefixes = set()
    for key in prefix_dict.keys():
        for i in range(len(key) + 1):
            prefixes.add(key[:i])

    for prefix in sorted(prefixes):
        remaining_dict = {k: v for k, v in prefix_dict.items() if k.startswith(prefix)}
        if prefix not in remaining_dict.keys():
            cpp_code += generate_function(prefix, remaining_dict)
        elif len(remaining_dict) > 1:
            cpp_code += generate_function(prefix, remaining_dict)


    return cpp_code + all_sensor()

# Example usage
prefix_dict = {"sht3c_temp": ["14",1], "sht3c_humi": ["14",2]}
cpp_code = generate_cpp_functions(prefix_dict)
print(cpp_code)