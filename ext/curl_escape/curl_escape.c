#include <string.h>
#include <curl/curl.h>
#include <ruby.h>
#include <ruby/encoding.h>

#define EXPAND_SIZE 40

static VALUE ruby_curl_escape(VALUE self, VALUE str) {
  int n, pos, len;
  char c;
  char *cStr, *cOutput;
  char escaped_tilde[3] = "%7E";
  VALUE output;
  rb_encoding *enc;

  static CURL *curl;
  if (!curl) {
    curl = curl_easy_init();
  }

  cStr = StringValueCStr(str);
  cOutput = curl_easy_escape(curl, cStr, strlen(cStr));

  pos = 0;
  if (cOutput) {
    for (n = 0; (c = *(cOutput + n)) != '\0'; n++) {
      if (c == '~') {
        if (n - pos >= 2) {
          memcpy(cOutput + pos, escaped_tilde, 3);
          pos += 2;
        } else {
          cOutput = realloc(cOutput, strlen(cOutput) + EXPAND_SIZE);
          len = strlen(cOutput + n);
          memmove(cOutput + n + EXPAND_SIZE, cOutput + n, len + 1);
          n += EXPAND_SIZE;
          memcpy(cOutput + pos, escaped_tilde, 3);
          pos += 2;
        }
      } else if (c != '%') {
        if (pos != n) {
          *(cOutput + pos) = c;
        }
      } else if (strncmp(cOutput + n, "%20", 3) == 0) {
        *(cOutput + pos) = '+';
        n += 2;
      } else {
        if (pos != n) {
          *(cOutput + pos) = c;
        }
      }
      pos++;
    }
    *(cOutput + pos) = '\0';

    enc = rb_enc_get(str);
    output = rb_enc_str_new_cstr(cOutput, enc);
    curl_free(cOutput);
    return output;
  } else {
    return Qnil;
  }
}

void Init_curl_escape(void) {
  VALUE module = rb_define_module("CurlEscape");
  rb_define_singleton_method(module, "escape", ruby_curl_escape, 1);
}
