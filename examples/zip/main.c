#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <assert.h>

typedef unsigned char byte;

size_t deflate_byte(byte* out, size_t size, byte* in, int* ret);
size_t inflate_byte(byte* out, size_t size, byte* in, int* ret);

int main(void)
{
    byte data[] = {
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a',
      'a', 'a', 'a', 'a', 'a'
    };
    byte deflated[256];
    byte inflated[256];
    size_t dsz;
    size_t isz;
    int ret;
    int i;

    dsz = deflate_byte(deflated, (sizeof(data) / sizeof(byte)), data, &ret);
    if (ret != Z_OK) {
        fprintf(stderr, "Error: %d\n", ret);
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < dsz; i++) {
        printf("%02x ", deflated[i]);
        if (i % 16 == 15) puts("");
    }
    puts("");

    isz = inflate_byte(inflated, dsz, deflated, &ret);
    if (ret != Z_OK) {
        fprintf(stderr, "Error: %d\n", ret);
        exit(EXIT_FAILURE);
    }
    fwrite(inflated, sizeof(byte), isz, stdout);
    puts("");

    return 0;
}

size_t deflate_byte(byte* out, size_t size, byte* in, int* ret)
{
    size_t chunk = 4096;

    size_t s;
    z_stream strm;
    byte* pin;
    byte* pout;
    size_t remaining;

    byte obuf[chunk];

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    *ret = deflateInit(&strm, Z_DEFAULT_COMPRESSION);
    if (*ret != Z_OK) {
        return s;
    }

    s = 0;
    pin = in;
    pout = out;
    remaining = size;
    do {
        strm.avail_in = remaining > chunk ? chunk : remaining;
        strm.next_in = pin;
        remaining -= strm.avail_in;
        pin += strm.avail_in;
        do {
            strm.avail_out = chunk;
            strm.next_out = pout;
            *ret = deflate(&strm, remaining > 0 ? Z_NO_FLUSH : Z_FINISH);
            assert(*ret != Z_STREAM_ERROR);
            pout += chunk - strm.avail_out;
        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);
    } while (remaining > 0);

    fprintf(stderr, "total_in: %d\n", strm.total_in);
    fprintf(stderr, "total_out: %d\n", strm.total_out);

    assert(*ret == Z_STREAM_END);

    s = strm.total_out;
    deflateEnd(&strm);
    *ret = Z_OK;

    return s;
}

size_t inflate_byte(byte* out, size_t size, byte* in, int* ret)
{
    int chunk = 4096;

    size_t s;
    z_stream strm;
    byte* pin;
    byte* pout;
    int remaining;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    *ret = inflateInit(&strm);
    if (*ret != Z_OK) {
        return s;
    }

    s = 0;
    pin = in;
    pout = out;
    remaining = (int) size;
    do {
        strm.avail_in = size > chunk ? chunk : size;
        strm.next_in = pin;
        remaining -= strm.avail_in;
        pin += strm.avail_in;
        do {
            strm.avail_out = chunk;
            strm.next_out = pout;
            *ret = inflate(&strm, Z_NO_FLUSH);
            assert(*ret != Z_STREAM_ERROR);
            switch (*ret) {
                case Z_NEED_DICT:
                    *ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    inflateEnd(&strm);
                    return s;
            }
            pout += chunk - strm.avail_out;
        } while (strm.avail_out == 0);
        assert(strm.avail_in == 0);
    } while (remaining > 0);

    fprintf(stderr, "total_in: %d\n", strm.total_in);
    fprintf(stderr, "total_out: %d\n", strm.total_out);

    assert(*ret == Z_STREAM_END);

    s = strm.total_out;
    inflateEnd(&strm);
    *ret = Z_OK;

    return s;
}
