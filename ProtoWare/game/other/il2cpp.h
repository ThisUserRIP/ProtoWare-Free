#pragma once
class monostring;

namespace il2cpp {
	void initialize_unity_class(uintptr uclass);
	void try_init_class(uintptr uclass);
	void rescue_string(uintptr _string);
	void write_str(const wchar_t* str, monostring* monostr);
};

constexpr inline uintptr initialize_unity_class_method_offset = 0x398DC0;
constexpr inline uintptr initialize_il2cpp_runtime_class_method_offset = 0x378B60;
constexpr inline uintptr rescue_string_method_offset = 0x3987C0;
constexpr inline uintptr string_class_offset = 0x3594ED0; // class "String", method "public override Boolean Equals(Object obj)"