#pragma once
template <typename T>
class unmanaged_list
{
public:
	const static int DEFAULT_RESERVE_COUNT = 128;
	const static int DEFAULT_RESERVE_ADDICT_COUNT = 128;

	unsigned int count;
	unsigned int reservedCount;
	char* listPTR;

	T& operator[](unsigned int index) {
		return *(T*)(listPTR + (sizeof(T) * index));
	}

	unmanaged_list() {
		reservedCount = 0;
		listPTR = 0;
		//reservedCount = DEFAULT_RESERVE_COUNT;
		//listPTR = (char*)malloc(sizeof(T) * reservedCount);
		//ZeroMemory(listPTR, sizeof(T) * reservedCount);
		count = 0;
	}
	unmanaged_list(int reservceCount) {
		reservedCount = reservceCount;
		listPTR = (char*)malloc(sizeof(T) * reservedCount);
		ZeroMemory(listPTR, sizeof(T) * reservedCount);
		count = 0;
	}

	void check_buffer(int increment = 1) {
		if (listPTR == 0) {
			reservedCount = DEFAULT_RESERVE_COUNT + (increment > DEFAULT_RESERVE_COUNT ? increment - DEFAULT_RESERVE_COUNT + DEFAULT_RESERVE_COUNT / 4 : 0);
			listPTR = (char*)malloc(sizeof(T) * reservedCount);
			ZeroMemory(listPTR, sizeof(T) * reservedCount);
			count = 0;
		}
		if (reservedCount < count + increment) {
			void* newListPTR = malloc((reservedCount + (DEFAULT_RESERVE_ADDICT_COUNT + increment)) * sizeof(T));
			memcpy(newListPTR, listPTR, reservedCount * sizeof(T));
			free(listPTR);
			reservedCount += DEFAULT_RESERVE_ADDICT_COUNT + increment;
			listPTR = (char*)newListPTR;
		}
	}

	void copy(unmanaged_list<T> list) {
		if (list.count > reservedCount) {
			check_buffer(list.count - reservedCount);
			count = list.count;
			memcpy(listPTR, list.listPTR, count * sizeof(T));
		}
		else {
			count = list.count;
			memcpy(listPTR, list.listPTR, count * sizeof(T));
		}
	}

	void push(T val) {
		check_buffer();
		*(T*)(listPTR + (count * sizeof(T))) = val;
		count++;
	}

	void push_uncheckable(T val) {
		*(T*)(listPTR + (count * sizeof(T))) = val;
		count++;
	}

	/*T LastValue() {
		return (T)listPTR + (count - 1);
	}
	*/
	void set_reserve_space(int reserveSpace) {
		void* newListPTR = malloc(reserveSpace * sizeof(T));
		//ZeroMemory(newListPTR, reserveSpace * sizeof(T));
		if ((unsigned __int64)listPTR > 0x1000) {
			memcpy(newListPTR, listPTR, min(reservedCount * sizeof(T), reserveSpace * sizeof(T)));
			free(listPTR);
		}
		reservedCount = reserveSpace;
		listPTR = (char*)newListPTR;
	}

	bool set_reserve_space_checked(int reserveSpace) {
		if (reservedCount >= reserveSpace) return true;
		void* newListPTR = malloc(reserveSpace * sizeof(T));
		if ((unsigned __int64)newListPTR < 0x1000) return false;
		//ZeroMemory(newListPTR, reserveSpace * sizeof(T));
		if ((unsigned __int64)listPTR > 0x1000) {
			memcpy(newListPTR, listPTR, reservedCount * sizeof(T));
			free(listPTR);
		}
		reservedCount = reserveSpace;
		listPTR = (char*)newListPTR;
		return true;
	}

	void clear() {
		ZeroMemory(listPTR, count * sizeof(T));
		count = 0;
	}

	void delete_at(int index) {
		if (index >= count)
			return;
		if (index == count - 1) {
			ZeroMemory(listPTR + (index * sizeof(T)), sizeof(T));
			count--;
			return;
		}

		memcpy(listPTR + (index * sizeof(T)), listPTR + ((index + 1) * sizeof(T)), (count - index - 1) * sizeof(T));
		ZeroMemory(listPTR + ((count - 1) * sizeof(T)), sizeof(T));
		count--;
	}
	
	void delete_at_fast(int index) {
		if (index >= count)
			return;
		if (index == count - 1) {
			count--;
			return;
		}

		memcpy(listPTR + (index * sizeof(T)), listPTR + ((index + 1) * sizeof(T)), (count - index - 1) * sizeof(T));
		count--;
	}

	void clear_fast() {
		count = 0;
	}

	void clearfast() {
		count = 0;
	}

	void freelist() {
		free(listPTR);
	}

	void dispose() {
		free(listPTR);
		listPTR = 0;
		count = 0;
		reservedCount = 0;
	}

	T* begin() {
		return (T*)listPTR;
	}

	T* end() {
		return (T*)listPTR + count;
	}

	const T* begin() const {
		return (T*)listPTR;
	}

	const T* end() const {
		return (T*)listPTR + count;
	}
};

