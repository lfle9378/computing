#include <string.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>


#pragma comment(lib,"libeay32.lib")
#pragma comment(lib,"ssleay32.lib")

char *Base64Encode(char *input, int length);
char *Base64Decode(char *input, int length);


int main(int argc, char **argv)
{

  if ( argc != 2 ) {
        fprintf(stdout,"Usage OpenSSLBase64E text \n");
        return 1;

  }

  char *output = Base64Encode(argv[1],strlen(argv[1]));
  printf("Base64: %s\n", output);



  char new_buffer[512];
  strcpy(new_buffer,output);
  strcat(new_buffer,"\n\0");

  char *temp = Base64Decode(new_buffer,strlen(new_buffer));

  printf("Base64: %s\n", temp); 
  
  free(output);
  free(temp); 
}

/////////////////////////////////////////
//
//
//
//
//

char *Base64Encode( char *input, int length)
{
  BIO *bmem, *b64;
  BUF_MEM *bptr;

  b64 = BIO_new(BIO_f_base64());
  bmem = BIO_new(BIO_s_mem());
  b64 = BIO_push(b64, bmem);
  BIO_write(b64, input, length);
  BIO_flush(b64);
  BIO_get_mem_ptr(b64, &bptr);

  char *buff = (char *)malloc(bptr->length);
  memcpy(buff, bptr->data, bptr->length-1);
  buff[bptr->length-1] = 0;

  BIO_free_all(b64);

  return buff;
}

char *Base64Decode( char *input, int length)
{
  BIO *b64, *bmem;

  char *buffer = (char *)malloc(length);
  memset(buffer, 0, length);

  b64 = BIO_new(BIO_f_base64());
  bmem = BIO_new_mem_buf(input, length);
  bmem = BIO_push(b64, bmem);

  BIO_read(bmem, buffer, length);

  BIO_free_all(bmem);

  return buffer;
}
