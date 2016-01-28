require 'mkmf'

$CFLAGS << ' -Wall'

dir_config('curl').any? || pkg_config('libcurl')

if have_header('curl/curl.h') && have_library('curl', 'curl_easy_init')
  create_makefile 'curl_escape/curl_escape'
else
  abort 'libcurl is not found'
end
