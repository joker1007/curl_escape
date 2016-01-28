#include <string.h>
#include <curl/curl.h>
#include <ruby.h>

VALUE ruby_curl_escape(VALUE self, VALUE str) {
  static CURL *curl;
  if (!curl) {
    curl = curl_easy_init();
  }

  char *cStr = StringValueCStr(str);
  char *cOutput = curl_easy_escape(curl, cStr, strlen(cStr));

  if (cOutput) {
    for (int cnt = 0; *(cOutput + cnt) != '\0'; cnt++) {
      if (strncmp(cOutput + cnt, "%20", 3) == 0) {
        *(cOutput + cnt) = '+';
        int rest = strlen(cOutput + cnt + 3);
        memmove(cOutput + cnt + 1, cOutput + cnt + 3, rest);
        *(cOutput + cnt + 1 + rest) = '\0';
      } else if (*(cOutput + cnt) == '~') {
        cOutput = realloc(cOutput, strlen(cOutput) + 2);
        int rest = strlen(cOutput + cnt + 1);
        memmove(cOutput + cnt + 3, cOutput + cnt + 1, rest);
        *(cOutput + cnt + 3 + rest) = '\0';
        memcpy(cOutput + cnt, "%7E", 3);
      }
    }

    VALUE output = rb_str_new2(cOutput);
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
