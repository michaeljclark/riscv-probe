#pragma once

#define bswap16(x) __builtin_bswap16(x)
#define bswap32(x) __builtin_bswap32(x)
#define bswap64(x) __builtin_bswap64(x)

#if __BYTE_ORDER == __LITTLE_ENDIAN
static inline uint16_t htobe16(uint16_t x) { return bswap16(x); }
static inline uint16_t htole16(uint16_t x) { return x; }
static inline uint16_t be16toh(uint16_t x) { return bswap16(x); }
static inline uint16_t le16toh(uint16_t x) { return x; }

static inline uint32_t htobe32(uint32_t x) { return bswap32(x); }
static inline uint32_t htole32(uint32_t x) { return x; }
static inline uint32_t be32toh(uint32_t x) { return bswap32(x); }
static inline uint32_t le32toh(uint32_t x) { return x; }

static inline uint64_t htobe64(uint64_t x) { return bswap64(x); }
static inline uint64_t htole64(uint64_t x) { return x; }
static inline uint64_t be64toh(uint64_t x) { return bswap64(x); }
static inline uint64_t le64toh(uint64_t x) { return x; }
#elif __BYTE_ORDER == __BIG_ENDIAN
static inline uint16_t htobe16(uint16_t x) { return x; }
static inline uint16_t htole16(uint16_t x) { return bswap16(x); }
static inline uint16_t be16toh(uint16_t x) { return x; }
static inline uint16_t le16toh(uint16_t x) { return bswap16(x); }

static inline uint32_t htobe32(uint32_t x) { return x; }
static inline uint32_t htole32(uint32_t x) { return bswap32(x); }
static inline uint32_t be32toh(uint32_t x) { return x; }
static inline uint32_t le32toh(uint16_t x) { return bswap64(x); }

static inline uint64_t htobe64(uint64_t x) { return x; }
static inline uint64_t htole64(uint64_t x) { return bswap64(x); }
static inline uint64_t be64toh(uint64_t x) { return x; }
static inline uint64_t le64toh(uint64_t x) { return bswap64(x); }
#endif

#if __SIZE_WIDTH__ == 32
#define _htobel htobe32
#define _beltoh be32toh
#define _htolel htole32
#define _leltoh le32toh
#endif

#if __SIZE_WIDTH__ == 64
#define _htobel htobe64
#define _beltoh be64toh
#define _htolel htole64
#define _leltoh le64toh
#endif

#define htobe(X) _Generic((X),                \
                 short: htobe16,              \
                 unsigned short: htobe16,     \
                 int: htobe32,                \
                 unsigned int: htobe32,       \
                 long: _htobel,               \
                 unsigned long: _htobel,      \
                 long long: htobe64,          \
                 unsigned long long: htobe64  \
                 )(X)

#define betoh(X) _Generic((X),                \
                 short: be16toh,              \
                 unsigned short: be16toh,     \
                 int: be32toh,                \
                 unsigned int: be32toh,       \
                 long: _beltoh,               \
                 unsigned long: _beltoh,      \
                 long long: be64toh,          \
                 unsigned long long: be64toh  \
                 )(X)

#define htole(X) _Generic((X),                \
                 short: htole16,              \
                 unsigned short: htole16,     \
                 int: htole32,                \
                 unsigned int: htole32,       \
                 long: _htolel,               \
                 unsigned long: _htolel,      \
                 long long: htole64,          \
                 unsigned long long: htole64  \
                 )(X)

#define letoh(X) _Generic((X),                \
                 short: le16toh,              \
                 unsigned short: le16toh,     \
                 int: le32toh,                \
                 unsigned int: le32toh,       \
                 long: _leltoh,               \
                 unsigned long: _leltoh,      \
                 long long: le64toh,          \
                 unsigned long long: le64toh  \
                 )(X)
