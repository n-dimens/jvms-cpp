#include "ConstantPool.h"

const char *getTagLabel(ConstantPoolTag value) {
    switch (value) {
        case CONSTANT_Class:
            return "class";
        case CONSTANT_Fieldref:
            return "field_ref";
        case CONSTANT_Methodref:
            return "method_ref";
        case CONSTANT_InterfaceMethodref:
            return "interface_method_ref";
        case CONSTANT_String:
            return "string";
        case CONSTANT_Integer:
            return "integer";
        case CONSTANT_Float:
            return "float";
        case CONSTANT_Long:
            return "long";
        case CONSTANT_Double:
            return "double";
        case CONSTANT_NameAndType:
            return "name_and_type";
        case CONSTANT_Utf8:
            return "utf8";
        case CONSTANT_MethodHandle:
            return "method_handle";
        case CONSTANT_MethodType:
            return "method_type";
        case CONSTANT_InvokeDynamic:
            return "invoke_dynamic";
        default:
            return "<not expected>";
    }
}

