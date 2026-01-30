#pragma once
struct il2cpp_type
{
    void* data;
    unsigned int bits;
};

struct il2cpp_class;

struct Il2CppRuntimeInterfaceOffsetPair
{
    il2cpp_class* interfaceType;
    int offset;
};

struct il2cpp_class
{
    void* image;
    void* gc_desc;
    const char* name;
    const char* namespaze;
    il2cpp_type byval_arg;
    il2cpp_type this_arg;
    il2cpp_class* element_class;
    il2cpp_class* castClass;
    il2cpp_class* declaringType;
    il2cpp_class* parent;
    void* generic_class;
    void* typeMetadataHandle;
    void* interopData;
    il2cpp_class* klass;
    void* fields;
    void* events;
    void* properties;
    void* methods;
    il2cpp_class** nestedTypes;
    il2cpp_class** implementedInterfaces;
    Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets;
    void* static_fields;
};

