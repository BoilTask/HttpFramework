# -*- coding: UTF-8 -*-

import os
import sys
import yaml

from netpacket import common


def write_net_header():
    write_content = "\n"
    write_content += "enum ENetHeader\n"
    write_content += "{\n"
    write_content += "	ENetHeader_None = 0,\n"
    for net_header in net_header_list:
        write_content += "	ENetHeader_" + net_header + ",\n"
    write_content += "	ENetHeader_Max\n"
    write_content += "};\n"
    common.write_file_content(config_yaml_data["NetDefFile"], config_yaml_data["NetDefStart"],
                              config_yaml_data["NetDefEnd"], write_content)
    print("Write NetHeader Success!")


def write_net_packet_name():
    write_content = "#pragma once\n"
    write_content += "\n"
    write_content += "//Exported by Tool, please don't edit this file directly.\n"
    write_content += "\n"

    for net_packet_name in net_packet_name_list:
        write_content += "#include \"NetRequest"+net_packet_name+".h\"\n"

    common.overwrite_file_content(
        config_yaml_data["NetRequestFile"], write_content)
    print("Write NetRequest Name Success!")


def get_data_type(data_type):
    if data_type == "bool":
        return "bool"
    if data_type == "int32":
        return "int32"
    if data_type == "int64":
        return "int64"
    if data_type == "float":
        return "float"
    if data_type == "string":
        return "FString"
    if data_type == "bool[]":
        return "TArray<bool>"
    if data_type == "int32[]":
        return "TArray<int32>"
    if data_type == "int64[]":
        return "TArray<int64>"
    if data_type == "float[]":
        return "TArray<float>"
    if data_type == "string[]":
        return "TArray<FString>"
    return data_type


def get_data_type_empty(data_type):
    if data_type == "bool":
        return " = false"
    if data_type == "int32":
        return " = 0"
    if data_type == "int64":
        return " = 0"
    if data_type == "float":
        return " = 0.f"
    if data_type == "string":
        return ".Empty()"
    if data_type == "bool[]":
        return ".Empty()"
    if data_type == "int32[]":
        return ".Empty()"
    if data_type == "int64[]":
        return ".Empty()"
    if data_type == "float[]":
        return ".Empty()"
    if data_type == "string[]":
        return ".Empty()"
    return ".Clear()"


def get_data_type_parse(data_type, data_name):
    if data_type == "bool":
        return ".AppendInt(" + data_name + "_?1:0)"
    if data_type == "int32":
        return ".AppendInt(" + data_name + "_)"
    if data_type == "int64":
        return ".AppendInt(" + data_name + "_)"
    if data_type == "float":
        return ".Append(FString::SanitizeFloat(" + data_name + "_))"
    if data_type == "string":
        return ".Append(" + data_name + "_)"

    if data_type == "bool[]":
        return ".Append(GameParser::GetConvertListBool(" + data_name + "_))"
    if data_type == "int32[]":
        return ".Append(GameParser::GetConvertListInt32(" + data_name + "_))"
    if data_type == "int64[]":
        return ".Append(GameParser::GetConvertListInt64(" + data_name + "_))"
    if data_type == "float[]":
        return ".Append(GameParser::GetConvertListFloat(" + data_name + "_))"
    if data_type == "string[]":
        return ".Append(GameParser::GetConvertListString(" + data_name + "_))"
    return ""


def is_need_initialization(data_type):
    if data_type == "bool":
        return True
    if data_type == "int32":
        return True
    if data_type == "int64":
        return True
    if data_type == "float":
        return True
    return False


def is_need_has_variable(data_type):
    if data_type == "bool":
        return True
    if data_type == "int32":
        return True
    if data_type == "int64":
        return True
    if data_type == "float":
        return True
    if data_type == "string":
        return True
    return False


def get_need_initialization(data_type):
    if data_type == "bool":
        return "false"
    if data_type == "int32":
        return "0"
    if data_type == "int64":
        return "0"
    if data_type == "float":
        return "0.f"
    return False


def get_data_public_h_function(data_type, data_name):
    content_prefix = "	"
    content = ""

    if data_type == "bool":
        content += content_prefix + "bool "+data_name+"() const;\n"
        content += "\tvoid set_" + data_name + \
            "(bool const& " + data_name + ");\n"
    elif data_type == "int32":
        content += content_prefix + "int32 "+data_name+"() const;\n"
        content += "\tvoid set_" + data_name + \
            "(int32 const& " + data_name + ");\n"
    elif data_type == "int64":
        content += content_prefix + "int64 "+data_name+"() const;\n"
        content += "\tvoid set_" + data_name + \
            "(int64 const& " + data_name + ");\n"
    elif data_type == "float":
        content += content_prefix + "float "+data_name+"() const;\n"
        content += "\tvoid set_" + data_name + \
            "(float const& " + data_name + ");\n"
    elif data_type == "string":
        content += content_prefix + "FString const& "+data_name+"() const;\n"
        content += "\tvoid set_" + data_name + \
            "(FString const& " + data_name + ");\n"

    elif data_type == "bool[]":
        content += content_prefix + "TArray<bool> const& "+data_name+"() const;\n"
        content += content_prefix + "bool "+data_name+"(int32 Index) const;\n"
        content += content_prefix + "int32 "+data_name+"_size() const;\n"
        content += content_prefix + "void add_" + \
            data_name + "(bool const& " + data_name + ");\n"
        content += content_prefix + "void set_" + \
            data_name + "(TArray<bool> const& " + data_name + ");\n"

    elif data_type == "int32[]":
        content += content_prefix + "TArray<int32> const& "+data_name+"() const;\n"
        content += content_prefix + "int32 "+data_name+"(int32 Index) const;\n"
        content += content_prefix + "int32 "+data_name+"_size() const;\n"
        content += content_prefix + "void add_" + \
            data_name + "(int32 const& " + data_name + ");\n"
        content += content_prefix + "void set_" + \
            data_name + "(TArray<int32> const& " + data_name + ");\n"

    elif data_type == "int64[]":
        content += content_prefix + "TArray<int64> const& "+data_name+"() const;\n"
        content += content_prefix + "int64 "+data_name+"(int32 Index) const;\n"
        content += content_prefix + "int32 "+data_name+"_size() const;\n"
        content += content_prefix + "void add_" + \
            data_name + "(int64 const& " + data_name + ");\n"
        content += content_prefix + "void set_" + \
            data_name + "(TArray<int64> const& " + data_name + ");\n"

    elif data_type == "float[]":
        content += content_prefix + "TArray<float> const& "+data_name+"() const;\n"
        content += content_prefix + "float " + \
            data_name+"(int32 Index) const;\n"
        content += content_prefix + "int32 "+data_name+"_size() const;\n"
        content += content_prefix + "void add_" + \
            data_name + "(float const& " + data_name + ");\n"
        content += content_prefix + "void set_" + \
            data_name + "(TArray<float> const& " + data_name + ");\n"

    elif data_type == "string[]":
        content += content_prefix + "TArray<FString> const& "+data_name+"() const;\n"
        content += content_prefix + "FString const& " + \
            data_name+"(int32 Index) const;\n"
        content += content_prefix + "int32 "+data_name+"_size() const;\n"
        content += content_prefix + "void add_" + \
            data_name + "(FString const& " + data_name + ");\n"
        content += content_prefix + "void set_" + \
            data_name + "(TArray<FString> const& " + data_name + ");\n"

    content += "\tbool has_" + data_name + "() const;\n"

    return content


def get_data_type_cpp_function(class_name, data_type, data_name):
    content_prefix = ""
    content = "\n"

    if data_type == "bool":
        content += content_prefix + "bool "+class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\treturn "+data_name+"_;\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += "void " + class_name + "::set_" + \
            data_name + "(bool const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\thas_"+data_name+"_ = true;\n"
        content += content_prefix + "\t"+data_name+"_ = " + data_name + ";\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "bool "+class_name+"::has_"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\treturn has_"+data_name+"_;\n"
        content += content_prefix + "}\n"

    elif data_type == "int32":
        content += content_prefix + "int32 "+class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += "void " + class_name + "::set_" + \
            data_name + "(int32 const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\thas_"+data_name+"_ = true;\n"
        content += content_prefix + "\t"+data_name+"_ = " + data_name + ";\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "bool "+class_name+"::has_"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return has_"+data_name+"_;\n"
        content += content_prefix + "}\n"

    elif data_type == "int64":
        content += content_prefix + "int64 "+class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += "void " + class_name + "::set_" + \
            data_name + "(int64 const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\thas_"+data_name+"_ = true;\n"
        content += content_prefix + "\t"+data_name+"_ = " + data_name + ";\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "bool "+class_name+"::has_"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return has_"+data_name+"_;\n"
        content += content_prefix + "}\n"

    elif data_type == "float":
        content += content_prefix + "float "+class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\treturn "+data_name+"_;\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += "void " + class_name + "::set_" + \
            data_name + "(float const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\thas_"+data_name+"_ = true;\n"
        content += content_prefix + "\t"+data_name+"_ = " + data_name + ";\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "bool "+class_name+"::has_"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return has_"+data_name+"_;\n"
        content += content_prefix + "}\n"

    elif data_type == "string":
        content += content_prefix + "FString const& " + \
            class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += "void " + class_name + "::set_" + \
            data_name + "(FString const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\thas_"+data_name+"_ = true;\n"
        content += content_prefix + "\t"+data_name+"_ = " + data_name + ";\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "bool "+class_name+"::has_"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return has_"+data_name+"_;\n"
        content += content_prefix + "}\n"

    elif data_type == "bool[]":
        content += content_prefix + "TArray<bool> const& " + \
            class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"
        content += content_prefix + "\n"
        content += content_prefix + "bool " + \
            class_name+"::"+data_name+"(int32 Index) const\n"
        content += content_prefix + "{\n"
        content += content_prefix + \
            "   if (!(Index >= 0 && Index < "+data_name+"_size()))\n"
        content += content_prefix + "   {\n"
        content += content_prefix + \
            "      UE_LOG(LogNetResponse, Error, TEXT(\"" + \
            class_name+"::"+data_name+" Out of Range!\"));\n"
        content += content_prefix + "   }\n"
        content += content_prefix + "   return "+data_name+"_[Index];\n"
        content += content_prefix + "}\n"
        content += content_prefix + "\n"
        content += content_prefix + "int32 "+class_name+"::"+data_name+"_size() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_.Num();\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "void " + class_name + "::set_" + \
            data_name + "(TArray<bool> const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\t"+data_name+"_ = " + data_name + ";\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += "void " + class_name + "::add_" + \
            data_name + "(bool const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\t"+data_name + \
            "_.Emplace(" + data_name + ");\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "bool "+class_name+"::has_"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return " + data_name + "_size() > 0;\n"
        content += content_prefix + "}\n"

    elif data_type == "int32[]":
        content += content_prefix + "TArray<int32> const& " + \
            class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"
        content += content_prefix + "\n"
        content += content_prefix + "int32 " + \
            class_name+"::"+data_name+"(int32 Index) const\n"
        content += content_prefix + "{\n"
        content += content_prefix + \
            "   if (!(Index >= 0 && Index < "+data_name+"_size()))\n"
        content += content_prefix + "   {\n"
        content += content_prefix + \
            "      UE_LOG(LogNetResponse, Error, TEXT(\"" + \
            class_name+"::"+data_name+" Out of Range!\"));\n"
        content += content_prefix + "   }\n"
        content += content_prefix + "   return "+data_name+"_[Index];\n"
        content += content_prefix + "}\n"
        content += content_prefix + "\n"
        content += content_prefix + "int32 "+class_name+"::"+data_name+"_size() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_.Num();\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "void " + class_name + "::set_" + \
            data_name + "(TArray<int32> const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\t"+data_name+"_ = " + data_name + ";\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += "void " + class_name + "::add_" + \
            data_name + "(int32 const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\t"+data_name + \
            "_.Emplace(" + data_name + ");\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "bool "+class_name+"::has_"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return " + data_name + "_size() > 0;\n"
        content += content_prefix + "}\n"

    elif data_type == "int64[]":
        content += content_prefix + "TArray<int64> const& " + \
            class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"
        content += content_prefix + "\n"
        content += content_prefix + "int64 " + \
            class_name+"::"+data_name+"(int32 Index) const\n"
        content += content_prefix + "{\n"
        content += content_prefix + \
            "   if (!(Index >= 0 && Index < "+data_name+"_size()))\n"
        content += content_prefix + "   {\n"
        content += content_prefix + \
            "      UE_LOG(LogNetResponse, Error, TEXT(\"" + \
            class_name+"::"+data_name+" Out of Range!\"));\n"
        content += content_prefix + "   }\n"
        content += content_prefix + "   return "+data_name+"_[Index];\n"
        content += content_prefix + "}\n"
        content += content_prefix + "\n"
        content += content_prefix + "int32 "+class_name+"::"+data_name+"_size() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_.Num();\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "void " + class_name + "::set_" + \
            data_name + "(TArray<int64> const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\t"+data_name+"_ = " + data_name + ";\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += "void " + class_name + "::add_" + \
            data_name + "(int64 const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\t"+data_name + \
            "_.Emplace(" + data_name + ");\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "bool "+class_name+"::has_"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return " + data_name + "_size() > 0;\n"
        content += content_prefix + "}\n"

    elif data_type == "float[]":
        content += content_prefix + "TArray<float> const& " + \
            class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"
        content += content_prefix + "\n"
        content += content_prefix + "float " + \
            class_name+"::"+data_name+"(int32 Index) const\n"
        content += content_prefix + "{\n"
        content += content_prefix + \
            "   if (!(Index >= 0 && Index < "+data_name+"_size()))\n"
        content += content_prefix + "   {\n"
        content += content_prefix + \
            "      UE_LOG(LogNetResponse, Error, TEXT(\"" + \
            class_name+"::"+data_name+" Out of Range!\"));\n"
        content += content_prefix + "   }\n"
        content += content_prefix + "   return "+data_name+"_[Index];\n"
        content += content_prefix + "}\n"
        content += content_prefix + "\n"
        content += content_prefix + "int32 "+class_name+"::"+data_name+"_size() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_.Num();\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "void " + class_name + "::set_" + \
            data_name + "(TArray<float> const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\t"+data_name+"_ = " + data_name + ";\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += "void " + class_name + "::add_" + \
            data_name + "(float const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\t"+data_name + \
            "_.Emplace(" + data_name + ");\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "bool "+class_name+"::has_"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return " + data_name + "_size() > 0;\n"
        content += content_prefix + "}\n"

    elif data_type == "string[]":
        content += content_prefix + "TArray<FString> const& " + \
            class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"
        content += content_prefix + "\n"
        content += content_prefix + "FString const& " + \
            class_name+"::"+data_name+"(int32 Index) const\n"
        content += content_prefix + "{\n"
        content += content_prefix + \
            "   if (!(Index >= 0 && Index < "+data_name+"_size()))\n"
        content += content_prefix + "   {\n"
        content += content_prefix + \
            "      UE_LOG(LogNetResponse, Error, TEXT(\"" + \
            class_name+"::"+data_name+" Out of Range!\"));\n"
        content += content_prefix + "   }\n"
        content += content_prefix + "   return "+data_name+"_[Index];\n"
        content += content_prefix + "}\n"
        content += content_prefix + "\n"
        content += content_prefix + "int32 "+class_name+"::"+data_name+"_size() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_.Num();\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "void " + class_name + "::set_" + \
            data_name + "(TArray<FString> const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\t"+data_name+"_ = " + data_name + ";\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += "void " + class_name + "::add_" + \
            data_name + "(FString const& " + data_name + ")\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\t"+data_name + \
            "_.Emplace(" + data_name + ");\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "bool "+class_name+"::has_"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return " + data_name + "_size() > 0;\n"
        content += content_prefix + "}\n"

    return content


def write_net_packet(net_packet_name):

    for net_packet_key in packet_config_data:
        net_header_list.append(net_packet_name + net_packet_key)

    write_h_content = "#pragma once\n"
    write_h_content += "\n"
    write_h_content += "//Exported by Tool, please don't edit this file directly.\n"
    write_h_content += "\n"
    write_h_content += "#include \"NetRequestBase.h\"\n"

    for net_packet_key in packet_config_data:
        net_packet_data = packet_config_data[net_packet_key]

        write_h_content += "\n"

        packet_class_name = "NetRequest" + net_packet_name + net_packet_key

        write_h_content += "class "+packet_class_name+" : public NetRequestBase\n"
        write_h_content += "{\n"
        write_h_content += "public:\n"

        write_h_content += "\t" + packet_class_name + "();\n"

        write_h_content += "\n"

        write_h_content += "\tstatic " + packet_class_name + \
            "* Cast(NetRequestBase& Data);\n"
        write_h_content += "\n"

        write_h_content += "\tvirtual NetRequestBase* Create() const override;\n"

        write_h_content += "\n"

        write_h_content += "\tvirtual void Clear() override;\n"

        write_h_content += "\n"

        write_h_content += "\tvirtual FString ParseStr() override;\n"

        if "Data" in net_packet_data:
            write_h_content += "\n"
            write_h_content += "public:\n"
            for net_package_data_key in net_packet_data["Data"]:
                write_h_content += get_data_public_h_function(
                    net_packet_data["Data"][net_package_data_key], net_package_data_key)

        if "Data" in net_packet_data:
            write_h_content += "\n"
            write_h_content += "private:\n"
            for net_package_data_key in net_packet_data["Data"]:

                write_h_content += "\t"

                write_h_content += get_data_type(
                    net_packet_data["Data"][net_package_data_key])
                write_h_content += " " + net_package_data_key + "_;\n"

                if is_need_has_variable(net_packet_data["Data"][net_package_data_key]):
                    write_h_content += "\tbool has_" + net_package_data_key + "_;\n"

        write_h_content += "};\n"

    write_cpp_content = "//Exported by Tool, please don't edit this file directly.\n"
    write_cpp_content += "\n"
    write_cpp_content += "#include \"NetRequest"+net_packet_name+".h\"\n"
    write_cpp_content += "#include \"GameParser.h\"\n"

    for net_packet_key in packet_config_data:
        net_packet_data = packet_config_data[net_packet_key]

        write_cpp_content += "\n"

        packet_class_name = "NetRequest" + net_packet_name + net_packet_key

        write_cpp_content += packet_class_name + "::" + packet_class_name + "()\n"

        if "Data" in net_packet_data:
            is_first = True
            for net_package_data_key in net_packet_data["Data"]:
                data_type = get_data_type(
                    net_packet_data["Data"][net_package_data_key])
                if is_need_initialization(data_type):
                    write_cpp_content += "\t"
                    if is_first:
                        is_first = False
                        write_cpp_content += ":"
                    else:
                        write_cpp_content += ","

                    write_cpp_content += " " + net_package_data_key + "_(" + \
                        get_need_initialization(data_type)+")\n"

                if is_need_has_variable(net_packet_data["Data"][net_package_data_key]):
                    write_cpp_content += "\t"
                    if is_first:
                        is_first = False
                        write_cpp_content += ":"
                    else:
                        write_cpp_content += ","
                    write_cpp_content += " has_" + \
                        net_package_data_key + "_(false)\n"

        write_cpp_content += "{\n"
        write_cpp_content += "\tHeader = ENetHeader_" + \
            net_packet_name + net_packet_key + ";\n"
        write_cpp_content += "\tMethod = ENetMethod_" + \
            net_packet_data["Method"]+";\n"
        if "Server" in net_packet_data:
            write_cpp_content += "\tServer = \"" + \
                net_packet_data["Server"]+"\";\n"
        else:
            write_cpp_content += "\tServer = \"\";\n"
        write_cpp_content += "\tUrl = \""+net_packet_data["Url"]+"\";\n"
        write_cpp_content += "}\n"

        write_cpp_content += "\n"

        write_cpp_content += packet_class_name + "* " + \
            packet_class_name + "::Cast(NetRequestBase& Data)\n"
        write_cpp_content += "{\n"
        write_cpp_content += "\tif (Data.Header != ENetHeader_" + \
            net_packet_name + net_packet_key + ")\n"
        write_cpp_content += "\t{\n"
        write_cpp_content += "\t\treturn nullptr;\n"
        write_cpp_content += "\t}\n"
        write_cpp_content += "\treturn static_cast<" + \
            packet_class_name + "*>(&Data);\n"
        write_cpp_content += "}\n"

        write_cpp_content += "\n"

        write_cpp_content += "NetRequestBase* " + \
            packet_class_name + "::Create() const\n"
        write_cpp_content += "{\n"
        write_cpp_content += "\tconst auto Data = new " + packet_class_name + "();\n"
        write_cpp_content += "\t*Data = *this;\n"
        write_cpp_content += "\treturn Data;\n"
        write_cpp_content += "}\n"

        write_cpp_content += "\n"

        write_cpp_content += "void " + packet_class_name + "::Clear()\n"
        write_cpp_content += "{\n"

        if "Data" in net_packet_data:
            for net_package_data_key in net_packet_data["Data"]:
                write_cpp_content += "\t"
                write_cpp_content += net_package_data_key + "_"
                write_cpp_content += get_data_type_empty(
                    net_packet_data["Data"][net_package_data_key])
                write_cpp_content += ";\n"

                if is_need_has_variable(net_packet_data["Data"][net_package_data_key]):
                    write_cpp_content += "\thas_" + net_package_data_key + "_ = false;\n"

        write_cpp_content += "}\n"

        write_cpp_content += "\n"

        write_cpp_content += "FString " + packet_class_name + "::ParseStr()\n"
        write_cpp_content += "{\n"
        write_cpp_content += "\tDataString.Empty();\n"

        if "Data" in net_packet_data:
            data_count = len(net_packet_data["Data"])

            if data_count > 1:
                write_cpp_content += "\tbool IsFirst = true;\n"

            index = 0
            for net_package_data_key in net_packet_data["Data"]:
                index += 1

                write_cpp_content += "\tif (has_" + \
                    net_package_data_key + "())\n"
                write_cpp_content += "\t{\n"

                if data_count > 1:
                    write_cpp_content += "\t\tif (!IsFirst)\n"
                    write_cpp_content += "\t\t{\n"
                    write_cpp_content += "\t\t\tDataString.Append(\"&\");\n"
                    write_cpp_content += "\t\t}\n"
                    if index < data_count:
                        write_cpp_content += "\t\telse\n"
                        write_cpp_content += "\t\t{\n"
                        write_cpp_content += "\t\t\tIsFirst = false;\n"
                        write_cpp_content += "\t\t}\n"

                write_cpp_content += "\t\tDataString.Append(\"" + \
                    net_package_data_key+"=\");\n"
                write_cpp_content += "\t\tDataString"
                write_cpp_content += get_data_type_parse(
                    net_packet_data["Data"][net_package_data_key], net_package_data_key)
                write_cpp_content += ";\n"

                write_cpp_content += "\t}\n"

        write_cpp_content += "\treturn DataString;\n"
        write_cpp_content += "}\n"

        if "Data" in net_packet_data:
            for net_package_data_key in net_packet_data["Data"]:
                write_cpp_content += get_data_type_cpp_function(
                    packet_class_name, net_packet_data["Data"][net_package_data_key], net_package_data_key)

    common.overwrite_file_content(
        config_yaml_data["RequestExportPath"]+"/NetRequest"+net_packet_name+".h", write_h_content)

    common.overwrite_file_content(
        config_yaml_data["RequestExportPath"]+"/NetRequest"+net_packet_name+".cpp", write_cpp_content)

    print("Write NetRequest "+net_packet_name + " Success!")


if __name__ == "__main__":

    # 设置环境变量
    file_path = os.path.dirname(os.path.abspath(sys.argv[0]))
    os.chdir(file_path)
    cwd = os.getcwd()

    # 取数据配置
    with open('../Config.yaml', 'r', encoding='utf-8') as config_yaml_file:
        config_yaml_data = yaml.load(config_yaml_file, Loader=yaml.FullLoader)
        config_yaml_file.close()

    # print(config_yaml_data)

    net_header_list = []
    net_packet_name_list = []

    common.clean_file_path(config_yaml_data["RequestExportPath"])

    config_files = os.listdir(config_yaml_data["RequestConfigPath"])

    for file_name in config_files:
        with open(config_yaml_data["RequestConfigPath"]+"/"+file_name, 'r', encoding='utf-8') as packet_config_file:
            packet_config_data = yaml.load(
                packet_config_file, Loader=yaml.FullLoader)
            packet_config_file.close()
            packet_file_name = os.path.splitext(file_name)[0]
            net_packet_name_list.append(packet_file_name)
            write_net_packet(packet_file_name)

    write_net_header()
    write_net_packet_name()
