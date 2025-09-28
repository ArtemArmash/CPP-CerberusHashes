#include <cstdint>
#include <string>

class MD5 {
private:
	uint32_t _a, _b, _c, _d;
	unsigned char _buffer[64];
	size_t _buffer_len;
	uint64_t _bit_count;
	static const uint32_t T[64];
	static const uint32_t S[64];

	static inline uint32_t F(uint32_t B, uint32_t C, uint32_t D){
		return (B & C) | (~B & D);
	}
	static inline uint32_t G(uint32_t B, uint32_t C, uint32_t D) {
		return (B & D) | (C & ~D);
	}
	static inline uint32_t H(uint32_t B, uint32_t C, uint32_t D) {
		return B ^ C ^ D;
	}
	static inline uint32_t I(uint32_t B, uint32_t C, uint32_t D) {
		return C ^ (B | ~D);
	}
	static inline uint32_t ROTL(uint32_t x, uint32_t n) {
		return (x << n) | (x >> (32 - n));
	}
public:
	MD5();
	void update(const unsigned char* data, size_t length);
	void _transform(const unsigned char* block);
	std::string finalize();
};