#include <string.h>
#include <curl/curl.h>
#include <ruby.h>
#include <ruby/encoding.h>

VALUE ruby_curl_escape(VALUE self, VALUE str) {
  int cnt;
  VALUE output;

  static CURL *curl;
  if (!curl) {
    curl = curl_easy_init();
  }

  char *cStr = StringValueCStr(str);
  char *cOutput = curl_easy_escape(curl, cStr, strlen(cStr));

  int pos = 0;
  char buf[strlen(cOutput) * 3];

  if (cOutput) {
    for (cnt = 0; *(cOutput + cnt) != '\0'; cnt++) {
      if (strncmp(cOutput + cnt, "%20", 3) == 0) {
        buf[pos] = '+';
        cnt += 2;
      } else if (*(cOutput + cnt) == '~') {
        buf[pos] = '%';
        buf[pos+1] = '7';
        buf[pos+2] = 'E';
        pos += 2;
      } else {
        buf[pos] = *(cOutput + cnt);
      }
      pos++;
    }
    buf[pos++] = '\0';

    rb_encoding* enc = rb_enc_get(str);
    output = rb_enc_str_new_cstr(buf, enc);
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
