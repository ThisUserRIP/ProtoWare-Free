#include "pch.h"
#include "globals.h"
#include "il2cpp.h"
#include "monostring.h"

void il2cpp::initialize_unity_class(uintptr uclass) {
	((void(__fastcall*)(uintptr))(gameassembly + initialize_unity_class_method_offset))(uclass);
}
void il2cpp::try_init_class(uintptr uclass) {
	if (!*(DWORD*)(uclass + 224))
		((void(__fastcall*)(uintptr))(gameassembly + initialize_il2cpp_runtime_class_method_offset))(uclass);
}
void il2cpp::rescue_string(uintptr uclass) {
	((void(__fastcall*)(uintptr))(gameassembly + rescue_string_method_offset))(uclass);
}
void il2cpp::write_str(const wchar_t* str, monostring* monostr) {
	monostr->klass = *(il2cpp_class**)(gameassembly + string_class_offset);
	monostr->length = wcslen(str);
	memcpy(&monostr->wstring, str, monostr->length * sizeof(wchar_t));
}