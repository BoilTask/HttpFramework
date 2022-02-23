# -*- coding: UTF-8 -*-

import os
import sys
import yaml

from netpacket import common


def write_net_packet_name():
    write_content = "#pragma once\n"
    write_content += "\n"
    write_content += "//Exported by Tool, please don't edit this file directly.\n"
    write_content += "\n"

    for net_packet_name in net_packet_name_list:
        write_content += "#include \"NetResponse"+net_packet_name+".h\"\n"

    common.overwrite_file_content(
        config_yaml_data["NetResponseFile"], write_content)
    print("Write NetResponse Name Success!")


def get_data_type_empty(data_type, data_name):
    content_prefix = "	"
    content = ""

    if data_type == "bool":
        content += content_prefix + data_name+"_ = false;\n"
    elif data_type == "int32":
        content += content_prefix + data_name+"_ = 0;\n"
    elif data_type == "int64":
        content += content_prefix + data_name+"_ = 0;\n"
    elif data_type == "float":
        content += content_prefix + data_name+"_ = 0.f;\n"
    elif data_type == "string":
        content += content_prefix + data_name+"_.Empty();\n"

    elif data_type == "listint32":
        content += content_prefix + data_name+"_.Empty();\n"

    elif data_type[-2:] == "[]":
        content += content_prefix + data_name+"_.Empty();\n"

    else:
        content += content_prefix + data_name+"_.Reset();\n"

    return content


def get_data_type_parse(data_type, data_name):
    content_prefix = "	"
    content = "\n"

    if data_type == "bool":
        content += content_prefix + \
            "(*Data)->TryGetBoolField(\""+data_name+"\", "+data_name+"_);\n"
    elif data_type == "int32":
        content += content_prefix + \
            "(*Data)->TryGetNumberField(\""+data_name+"\", "+data_name+"_);\n"
    elif data_type == "int64":
        content += content_prefix + \
            "(*Data)->TryGetNumberField(\""+data_name+"\", "+data_name+"_);\n"
    elif data_type == "float":
        content += content_prefix + \
            "(*Data)->TryGetNumberField(\""+data_name+"\", "+data_name+"_);\n"
    elif data_type == "string":
        content += content_prefix + \
            "(*Data)->TryGetStringField(\""+data_name+"\", "+data_name+"_);\n"

    elif data_type == "listint32":
        content += content_prefix + "FString " + data_name + "_str_;\n"
        content += content_prefix + \
            "(*Data)->TryGetStringField(\"" + \
            data_name + "\", " + data_name + "_str_);\n"
        content += content_prefix + \
            "GameParser::ParseListInt32(" + data_name + \
            "_str_, " + data_name + "_);\n"

    elif data_type[-2:] == "[]":

        data_type = data_type.rstrip("[]")

        content += content_prefix + \
            "const TArray<TSharedPtr<FJsonValue>>* "+data_name+"_Data;\n"
        content += content_prefix + \
            "if ((*Data)->TryGetArrayField(\""+data_name + \
            "\", "+data_name+"_Data) && "+data_name+"_Data)\n"
        content += content_prefix + "{\n"
        content += content_prefix + \
            "	for (auto const & "+data_name+"_Item: *"+data_name+"_Data)\n"
        content += content_prefix + "	{\n"

        if data_type == "bool":
            content += content_prefix + "		bool _Temp;\n"
            content += content_prefix + \
                "		(*"+data_name+"_Item).TryGetBool(_Temp);\n"
            content += content_prefix + "		"+data_name+"_.Emplace(_Temp);\n"
        elif data_type == "int32":
            content += content_prefix + "		int32 _Temp;\n"
            content += content_prefix + \
                "		(*"+data_name+"_Item).TryGetNumber(_Temp);\n"
            content += content_prefix + "		"+data_name+"_.Emplace(_Temp);\n"
        elif data_type == "int64":
            content += content_prefix + "		int64 _Temp;\n"
            content += content_prefix + \
                "		(*"+data_name+"_Item).TryGetNumber(_Temp);\n"
            content += content_prefix + "		"+data_name+"_.Emplace(_Temp);\n"
        elif data_type == "float":
            content += content_prefix + "		double _Temp;\n"
            content += content_prefix + \
                "		(*"+data_name+"_Item).TryGetNumber(_Temp);\n"
            content += content_prefix + "		"+data_name+"_.Emplace(_Temp);\n"
        elif data_type == "string":
            content += content_prefix + "		FString _Temp;\n"
            content += content_prefix + \
                "		(*"+data_name+"_Item).TryGetString(_Temp);\n"
            content += content_prefix + "		"+data_name+"_.Emplace(_Temp);\n"

        else:
            content += content_prefix + "		const TSharedPtr<FJsonObject>* _Temp;\n"
            content += content_prefix + \
                "		(*"+data_name+"_Item).TryGetObject(_Temp);\n"
            content += content_prefix + "		TSharedPtr<NetResponse"+data_type+"> " + \
                data_name + \
                "_Ptr = MakeShareable(new NetResponse"+data_type+"());\n"
            content += content_prefix + "		" + \
                data_name+"_Ptr->ParseData(_Temp);\n"
            content += content_prefix + "		"+data_name + \
                "_.Emplace("+data_name+"_Ptr);\n"

        content += content_prefix + "	}\n"
        content += content_prefix + "}\n"

    else:
        content += content_prefix + "const TSharedPtr<FJsonObject>* "+data_name+"_Data;\n"
        content += content_prefix + \
            "if ((*Data)->TryGetObjectField(\"" + \
            data_name+"\", "+data_name+"_Data))\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   if (!"+data_name+"_)\n"
        content += content_prefix + "   {\n"
        content += content_prefix + "      "+data_name + \
            "_ = MakeShareable(new NetResponse"+data_type+"());\n"
        content += content_prefix + "   }\n"
        content += content_prefix + "   " + data_name + \
            "_->ParseData("+data_name+"_Data);\n"
        content += content_prefix + "}\n"

    return content


def get_data_type_cpp_function(class_name, data_type, data_name):
    content_prefix = ""
    content = "\n"

    if data_type == "bool":
        content += content_prefix + "bool "+class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"
    elif data_type == "int32":
        content += content_prefix + "int32 "+class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"
    elif data_type == "int64":
        content += content_prefix + "int64 "+class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"
    elif data_type == "float":
        content += content_prefix + "double "+class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"
    elif data_type == "string":
        content += content_prefix + "FString const& " + \
            class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"

    elif data_type == "listint32":
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
    elif data_type == "float[]":
        content += content_prefix + "TArray<double> const& " + \
            class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"
        content += content_prefix + "\n"
        content += content_prefix + "double " + \
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

    elif data_type[-2:] == "[]":
        data_type = data_type.rstrip("[]")

        content += content_prefix + "TArray<TSharedPtr<NetResponse"+data_type + \
            ">> const& "+class_name+"::"+data_name+"() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_;\n"
        content += content_prefix + "}\n"
        content += content_prefix + "\n"
        content += content_prefix + "NetResponse" + data_type + \
            " const& " + class_name+"::"+data_name+"(int32 Index) const\n"
        content += content_prefix + "{\n"
        content += content_prefix + \
            "   if (!(Index >= 0 && Index < "+data_name+"_size()))\n"
        content += content_prefix + "   {\n"
        content += content_prefix + \
            "      UE_LOG(LogNetResponse, Error, TEXT(\"" + \
            class_name+"::"+data_name+" Out of Range!\"));\n"
        content += content_prefix + "   }\n"
        content += content_prefix + "   return *"+data_name+"_[Index];\n"
        content += content_prefix + "}\n"
        content += content_prefix + "\n"
        content += content_prefix + "int32 "+class_name+"::"+data_name+"_size() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return "+data_name+"_.Num();\n"
        content += content_prefix + "}\n"
    else:

        content += content_prefix + "bool " + \
            class_name + "::has_" + data_name + "() const\n"
        content += content_prefix + "{\n"
        content += content_prefix + "   return " + data_name+"_.IsValid();\n"
        content += content_prefix + "}\n"

        content += content_prefix + "\n"

        content += content_prefix + "NetResponse" + \
            data_type + "& " + class_name + "::" + data_name + "()\n"
        content += content_prefix + "{\n"
        content += content_prefix + "\tif (!" + data_name+"_.IsValid())\n"
        content += content_prefix + "\t{\n"
        content += content_prefix + "\t\t" + data_name + \
            "_ = MakeShareable(new NetResponse" + data_type+"());\n"
        content += content_prefix + "\t}\n"
        content += content_prefix + "\treturn *" + data_name+"_;\n"
        content += content_prefix + "}\n"

    return content


def get_data_public_h_function(data_type, data_name):
    content_prefix = "	"
    content = ""

    if data_type == "bool":
        content += content_prefix + "bool "+data_name+"() const;\n"
    elif data_type == "int32":
        content += content_prefix + "int32 "+data_name+"() const;\n"
    elif data_type == "int64":
        content += content_prefix + "int64 "+data_name+"() const;\n"
    elif data_type == "float":
        content += content_prefix + "double "+data_name+"() const;\n"
    elif data_type == "string":
        content += content_prefix + "FString const& "+data_name+"() const;\n"

    elif data_type == "listint32":
        content += content_prefix + "TArray<int32> const& "+data_name+"() const;\n"
        content += content_prefix + "int32 "+data_name+"(int32 Index) const;\n"
        content += content_prefix + "int32 "+data_name+"_size() const;\n"

    elif data_type == "bool[]":
        content += content_prefix + "TArray<bool> const& "+data_name+"() const;\n"
        content += content_prefix + "bool "+data_name+"(int32 Index) const;\n"
        content += content_prefix + "int32 "+data_name+"_size() const;\n"
    elif data_type == "int32[]":
        content += content_prefix + "TArray<int32> const& "+data_name+"() const;\n"
        content += content_prefix + "int32 "+data_name+"(int32 Index) const;\n"
        content += content_prefix + "int32 "+data_name+"_size() const;\n"
    elif data_type == "int64[]":
        content += content_prefix + "TArray<int64> const& "+data_name+"() const;\n"
        content += content_prefix + "int64 "+data_name+"(int32 Index) const;\n"
        content += content_prefix + "int32 "+data_name+"_size() const;\n"
    elif data_type == "float[]":
        content += content_prefix + "TArray<double> const& "+data_name+"() const;\n"
        content += content_prefix + "double " + \
            data_name+"(int32 Index) const;\n"
        content += content_prefix + "int32 "+data_name+"_size() const;\n"
    elif data_type == "string[]":
        content += content_prefix + "TArray<FString> const& "+data_name+"() const;\n"
        content += content_prefix + "FString const& " + \
            data_name+"(int32 Index) const;\n"
        content += content_prefix + "int32 "+data_name+"_size() const;\n"

    elif data_type[-2:] == "[]":
        data_type = data_type.rstrip("[]")
        content += content_prefix + "TArray<TSharedPtr<NetResponse" + \
            data_type+">> const& "+data_name+"() const;\n"
        content += content_prefix + "NetResponse" + \
            data_type+" const& "+data_name+"(int32 Index) const;\n"
        content += content_prefix + "int32 "+data_name+"_size() const;\n"
    else:
        content += content_prefix + "bool has_"+data_name+"() const;\n"
        content += content_prefix + "NetResponse" + \
            data_type+"& "+data_name+"();\n"

    return content


def get_data_private_h_definition(data_type, data_name):
    content = "	"

    if data_type == "bool":
        content += "bool "+data_name+"_;\n"
    elif data_type == "int32":
        content += "int32 "+data_name+"_;\n"
    elif data_type == "int64":
        content += "int64 "+data_name+"_;\n"
    elif data_type == "float":
        content += "double "+data_name+"_;\n"
    elif data_type == "string":
        content += "FString "+data_name+"_;\n"

    elif data_type == "listint32":
        content += "TArray<int32> "+data_name+"_;\n"

    elif data_type == "bool[]":
        content += "TArray<bool> "+data_name+"_;\n"
    elif data_type == "int32[]":
        content += "TArray<int32> "+data_name+"_;\n"
    elif data_type == "int64[]":
        content += "TArray<int64> "+data_name+"_;\n"
    elif data_type == "float[]":
        content += "TArray<double> "+data_name+"_;\n"
    elif data_type == "string[]":
        content += "TArray<FString> "+data_name+"_;\n"

    elif data_type[-2:] == "[]":
        data_type = data_type.rstrip("[]")
        content += "TArray<TSharedPtr<NetResponse"+data_type+">> "+data_name+"_;\n"
    else:
        content += "TSharedPtr<NetResponse"+data_type+"> "+data_name+"_;\n"

    return content


def get_class_h_content(file_name, packet_name):

    packet_config_data = response_config_data[packet_name]

    write_content = "\n"

    response_class_name = "NetResponse" + file_name + packet_name
    write_content += "class "+response_class_name+"\n"
    write_content += "{\n"
    write_content += "public:\n"
    write_content += "	"+response_class_name+"() = default;\n"
    write_content += "	~"+response_class_name+"() = default;\n"

    write_content += "	void Clear();\n"
    write_content += "	bool ParseData(TSharedPtr<FJsonObject> const& Data);\n"
    write_content += "	bool ParseData(TSharedPtr<FJsonObject> const* Data);\n"

    if packet_config_data:
        write_content += "\n"
        write_content += "public:\n"
        for net_package_data_key in packet_config_data:
            write_content += get_data_public_h_function(
                packet_config_data[net_package_data_key], net_package_data_key)

    if packet_config_data:
        write_content += "\n"
        write_content += "private:\n"
        for net_package_data_key in packet_config_data:
            write_content += get_data_private_h_definition(
                packet_config_data[net_package_data_key], net_package_data_key)

    write_content += "};\n"

    return write_content


def get_class_cpp_content(file_name, packet_name):

    net_response_data = response_config_data[packet_name]

    write_content = "\n"

    response_class_name = "NetResponse" + file_name + packet_name
    write_content += "void "+response_class_name+"::Clear()\n"
    write_content += "{\n"

    if net_response_data:
        for net_package_data_key in net_response_data:
            write_content += get_data_type_empty(
                net_response_data[net_package_data_key], net_package_data_key)

    write_content += "}\n"

    write_content += "\n"

    write_content += "bool "+response_class_name + \
        "::ParseData(TSharedPtr<FJsonObject> const& Data)\n"
    write_content += "{\n"
    write_content += "	return ParseData(&Data);\n"
    write_content += "}\n"

    write_content += "\n"

    write_content += "bool "+response_class_name + \
        "::ParseData(TSharedPtr<FJsonObject> const* Data)\n"
    write_content += "{\n"
    write_content += "	Clear();\n"
    write_content += "\n"
    write_content += "	if (nullptr == Data || !(*Data).IsValid())\n"
    write_content += "	{\n"
    write_content += "		return false;\n"
    write_content += "	}\n"

    if net_response_data:
        for net_package_data_key in net_response_data:
            write_content += get_data_type_parse(
                net_response_data[net_package_data_key], net_package_data_key)

    write_content += "\n"

    write_content += "	return true;\n"

    write_content += "}\n"

    if net_response_data:
        for net_package_data_key in net_response_data:
            write_content += get_data_type_cpp_function(
                response_class_name, net_response_data[net_package_data_key], net_package_data_key)

    return write_content


def write_net_response(net_response_name):
    write_h_content = "//Exported by Tool, please don't edit this file directly.\n"
    write_h_content += "\n"
    write_h_content += "#pragma once\n"
    write_h_content += "\n"
    write_h_content += "#include \"NetDef.h\"\n"

    if "_" in response_config_data:
        if "Import" in response_config_data["_"]:
            write_h_content += "\n"
            import_file_list = response_config_data["_"]["Import"]
            for import_file in import_file_list:
                write_h_content += "#include \"NetResponse"+import_file+".h\"\n"

    write_h_content += "\n"

    for net_response_key in response_config_data:
        if net_response_key == "_":
            continue
        write_h_content += "class NetResponse"+net_response_name+net_response_key+";\n"

    for net_response_key in response_config_data:
        if net_response_key == "_":
            continue

        write_h_content += get_class_h_content(
            net_response_name, net_response_key)

    write_cpp_content = "//Exported by Tool, please don't edit this file directly.\n"
    write_cpp_content += "\n"
    write_cpp_content += "#include \"NetResponse"+net_response_name+".h\"\n"
    write_cpp_content += "#include \"GameParser.h\"\n"

    for net_response_key in response_config_data:
        if net_response_key == "_":
            continue
        write_cpp_content += get_class_cpp_content(
            net_response_name, net_response_key)

    common.overwrite_file_content(
        config_yaml_data["ResponseExportPath"]+"/NetResponse"+net_response_name+".h", write_h_content)

    common.overwrite_file_content(
        config_yaml_data["ResponseExportPath"]+"/NetResponse"+net_response_name+".cpp", write_cpp_content)

    print("Write NetResponse "+net_response_name + " Success!")


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

    net_packet_name_list = []

    common.clean_file_path(config_yaml_data["ResponseExportPath"])

    config_files = os.listdir(config_yaml_data["ResponseConfigPath"])

    for file_name in config_files:
        with open(config_yaml_data["ResponseConfigPath"]+"/"+file_name, 'r', encoding='utf-8') as response_config_file:
            response_config_data = yaml.load(
                response_config_file, Loader=yaml.FullLoader)
            response_config_file.close()

            response_file_name = os.path.splitext(file_name)[0]
            net_packet_name_list.append(response_file_name)
            write_net_response(response_file_name)

    write_net_packet_name()
