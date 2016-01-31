#include <string.h>
#include <curl/curl.h>
#include <ruby.h>
#include <ruby/encoding.h>

char *alloc_output_buffer(char *cOutput);

VALUE ruby_curl_escape(VALUE self, VALUE str) {
  int cnt;
  char c;
  VALUE output;

  static CURL *curl;
  if (!curl) {
    curl = curl_easy_init();
  }

  char *cStr = StringValueCStr(str);
  char *cOutput = curl_easy_escape(curl, cStr, strlen(cStr));

  int pos = 0;
  char escaped_tilde[3] = "%7E";
  char *buf = alloc_output_buffer(cOutput);
  if (cOutput) {
    for (cnt = 0; (c = *(cOutput + cnt)) != '\0'; cnt++) {
      if (c == '~') {
        memcpy(buf + pos, escaped_tilde, 3);
        pos += 2;
      } else if (c != '%') {
        buf[pos] = c;
      } else if (strncmp(cOutput + cnt, "%20", 3) == 0) {
        buf[pos] = '+';
        cnt += 2;
      } else {
        buf[pos] = c;
      }
      pos++;
    }
    buf[pos] = '\0';

    rb_encoding* enc = rb_enc_get(str);
    output = rb_enc_str_new_cstr(buf, enc);
    curl_free(cOutput);
    free(buf);
    return output;
  } else {
    return Qnil;
  }
}

char *alloc_output_buffer(char *cOutput) {
  int i, tilde_cnt;
  char *buf;
  tilde_cnt = 0;
  for (i = 0; *(cOutput + i) != '\0'; i++) {
    if (*(cOutput + i) == '~') {
      tilde_cnt++;
    }
  }
  buf = (char *)malloc(i + tilde_cnt * 2);
  return buf;
}

void Init_curl_escape(void) {
  VALUE module = rb_define_module("CurlEscape");
  rb_define_singleton_method(module, "escape", ruby_curl_escape, 1);
}
