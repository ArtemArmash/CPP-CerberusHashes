#include "md5.h"
#include <sstream>
#include <iomanip>
const uint32_t k_f[16] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };       
const uint32_t k_g[16] = { 1,6,11,0,5,10,15,4,9,14,3,8,13,2,7,12 };      
const uint32_t k_h[16] = { 5,8,11,14,1,4,7,10,13,0,3,6,9,12,15,2 };     
const uint32_t k_i[16] = { 0,7,14,5,12,3,10,1,8,15,6,13,4,11,2,9 };

const uint32_t MD5::T[64] =
{
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

const uint32_t MD5::S[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

MD5::MD5()
{
	_a = 0x67452301;
	_b = 0xefcdab89;
	_c = 0x98badcfe;
	_d = 0x10325476;

	_buffer_len = 0;
	_bit_count = 0;
}

void MD5::update(const unsigned char* data, size_t length)
{
    _bit_count += length * 8;
    uint32_t bytes_to_fill = 64 - _buffer_len;
    if (length > bytes_to_fill || length == bytes_to_fill) {
        memcpy(_buffer + _buffer_len, data, bytes_to_fill);
        _transform(_buffer);
        data += bytes_to_fill;
        length -= bytes_to_fill;
        _buffer_len = 0;
    }
    while (length >= 64) {
        _transform(data);
        data += 64;
        length -= 64;
    }
    if (length > 0) {
        memcpy(_buffer + _buffer_len, data, length);
        _buffer_len += length;
    }
}

std::string MD5::finalize()
{
    uint64_t original_bit_count = _bit_count;
    update((const unsigned char*)"\x80", 1);

    if (_buffer_len > 56) {
        memset(_buffer + _buffer_len, 0, 64 - _buffer_len);
        _transform(_buffer);
        memset(_buffer, 0, 56);
    }
    else {
        memset(_buffer + _buffer_len, 0, 56 - _buffer_len);
    }
    for (int i = 0; i < 8; i++) {
        _buffer[56 + i] = (original_bit_count >> (i * 8)) & 0xFF;
    }

    _transform(_buffer);
    std::stringstream ss;
    uint32_t hash_parts[] = { _a, _b, _c, _d };

    for (const auto& part : hash_parts) {
        for (int i = 0; i < 4; ++i) {
            ss << std::hex << std::setw(2) << std::setfill('0')
                << (int)((part >> (i * 8)) & 0xFF);
        }
    }

    return ss.str();
}
void MD5::_transform(const unsigned char* block)
{
    uint32_t M[16];
    for (size_t t = 0; t < 16; t++)
    {
        M[t] = uint32_t(block[t * 4]) | (uint32_t(block[t * 4 + 1]) << 8)
            | (uint32_t(block[t * 4 + 2]) << 16) | (uint32_t(block[t * 4 + 3]) << 24);
    }

    uint32_t A = _a;
    uint32_t B = _b;
    uint32_t C = _c;
    uint32_t D = _d;
    
    for (size_t i = 0; i < 16; i++)
    {   
        uint32_t F_val = F(B, C, D);
        uint32_t temp = B + ROTL(A + F_val + M[k_f[i]] + T[i], S[i]);
        A = D;
        D = C;
        C = B;
        B = temp;
    }
    for (size_t i = 0; i < 16; i++)
    {
        uint32_t G_val = G(B, C, D);
        uint32_t temp = B + ROTL(A + G_val + M[k_g[i]] + T[i+16], S[i+16]);
        A = D;
        D = C;
        C = B;
        B = temp;
    }
    for (size_t i = 0; i < 16; i++)
    {
        uint32_t H_val = H(B, C, D);
        uint32_t temp = B + ROTL(A + H_val + M[k_h[i]] + T[i+32], S[i+32]);
        A = D;
        D = C;
        C = B;
        B = temp;
    }
    for (size_t i = 0; i < 16; i++)
    {
        uint32_t I_val = I(B, C, D);
        uint32_t temp = B + ROTL(A + I_val + M[k_i[i]] + T[i+48], S[i+48]);
        A = D;
        D = C;
        C = B;
        B = temp;
    }
    _a += A;
    _b += B;
    _c += C;
    _d += D;

}

    

