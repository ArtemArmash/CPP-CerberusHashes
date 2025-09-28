#include <vector>
#include <string>
#include <cstdint>

class SHA256 {
private:
	static const uint32_t K[64];
	uint32_t _state[8];
	unsigned char _buffer[64];
	size_t _buffer_len;
	uint64_t _bit_count;
	void _transform(const unsigned char* block);
public:
	SHA256();
	void update(const unsigned char* data, size_t length);
	std::string finalize();



	static inline uint32_t ROTR(uint32_t x, uint32_t n) {
		return (x >> n) | (x << (32 - n));
	}
	static inline uint32_t CH(uint32_t e, uint32_t f, uint32_t g) {
		return (e & f) ^ (~e & g);
	}
	static inline uint32_t MAJ(uint32_t a, uint32_t b, uint32_t c) {
		return (a & b) ^ (a & c) ^ (b & c);
	}
	static inline uint32_t BSIG0(uint32_t x) {
		return ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22);
	}
	static inline uint32_t BSIG1(uint32_t x) {
		return ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25);
	}
	static inline uint32_t SSIG0(uint32_t x) {
		return ROTR(x, 7) ^ ROTR(x, 18) ^ (x >> 3);
	}
	static inline uint32_t SSIG1(uint32_t x) {
		return ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10);
	}
};