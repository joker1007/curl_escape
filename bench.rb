require 'benchmark/ips'
require 'cgi'

$LOAD_PATH.unshift File.expand_path('../lib', __FILE__)
require_relative './lib/curl_escape'

Benchmark.ips do |x|
  x.config(time: 15, warmup: 5)
  x.report("cgi_escape") { CGI.escape("'Stop!' said Fred") }
  x.report("curl_escape") { CurlEscape.escape("'Stop!' said Fred") }
  x.compare!
end

p CGI.escape("'Stop!' said~Fred foo~~hoge")
p CurlEscape.escape("'Stop!' said~Fred foo~~hoge")

p CGI.escape("'日本語あいうえお")
p CurlEscape.escape("'日本語あいうえお")
