#include "sha256.h"
#include <sstream>
#include <iomanip>
const uint32_t SHA256::K[64] = {
    0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
    0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
    0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
    0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
    0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
    0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
    0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
    0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
};


SHA256::SHA256()
{
    _state[0] = 0x6a09e667;
    _state[1] = 0xbb67ae85;
    _state[2] = 0x3c6ef372;
    _state[3] = 0xa54ff53a;
    _state[4] = 0x510e527f;
    _state[5] = 0x9b05688c;
    _state[6] = 0x1f83d9ab;
    _state[7] = 0x5be0cd19;

    _buffer_len = 0;  
    _bit_count = 0;
}

void SHA256::update(const unsigned char* data, size_t length)
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
        memcpy(_buffer+_buffer_len, data, length);
        _buffer_len += length;
    }
}

std::string SHA256::finalize()
{
    _buffer[_buffer_len++] = 0x80;;
    if (_buffer_len > 56) {
        while (_buffer_len < 64) {
            _buffer[_buffer_len++] = 0x00;
        }
        _transform(_buffer);
        _buffer_len = 0;
    }
    memset(_buffer + _buffer_len, 0, 56 - _buffer_len);

    _buffer[56] = (_bit_count >> 56);
    _buffer[57] = (_bit_count >> 48);
    _buffer[58] = (_bit_count >> 40);
    _buffer[59] = (_bit_count >> 32);
    _buffer[60] = (_bit_count >> 24);
    _buffer[61] = (_bit_count >> 16);
    _buffer[62] = (_bit_count >> 8);
    _buffer[63] = (_bit_count);

    _transform(_buffer);

    std::stringstream ss;
    for (size_t i = 0; i < 8; i++)
    {
        ss << std::hex << std::setw(8) << std::setfill('0') << _state[i];
    }

    return ss.str();
}


void SHA256::_transform(const unsigned char* block)
{
    uint32_t W[64];
    for (size_t i = 0; i < 16; i++)
    {
        W[i] = (uint32_t(block[i*4]) << 24) | (uint32_t(block[i*4+1]) << 16) 
            | (uint32_t(block[i*4+2]) << 8) | uint32_t(block[i*4+3]);
    }
    for (size_t i = 16; i < 64; i++)
    {
        W[i] = SSIG1(W[i - 2]) + W[i - 7] + SSIG0(W[i - 15]) + W[i - 16];
    }

    uint32_t a = _state[0];
    uint32_t b = _state[1];
    uint32_t c = _state[2];
    uint32_t d = _state[3];
    uint32_t e = _state[4];
    uint32_t f = _state[5];
    uint32_t g = _state[6];
    uint32_t h = _state[7];
    for (size_t t = 0; t < 64; t++)
    {
        uint32_t T1 = h + BSIG1(e) + CH(e, f, g) + K[t] + W[t];
        uint32_t T2 = BSIG0(a) + MAJ(a, b, c);

        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    _state[0] += a;
    _state[1] += b;
    _state[2] += c;
    _state[3] += d;
    _state[4] += e;
    _state[5] += f;
    _state[6] += g;
    _state[7] += h;
}
