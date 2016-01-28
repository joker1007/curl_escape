# CurlEscape
[![Build Status](https://travis-ci.org/joker1007/curl_escape.svg?branch=master)](https://travis-ci.org/joker1007/curl_escape)

Fast URL escape by libcurl.

`CurlEscape.escape` is 5x faster or more than `CGI.escape`.

The spec of escaping is `CGI.escape` compatible, and this gem has core extension for `CGI.escape`.

## Motivation
`CGI.escape` is used by `#to_query` method that is defined by activesupport.

And `#to_query` is used by `url_for` helper of Rails.

I want to speed up `url_for`.

## Benchmark

```ruby
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
```

```
Calculating -------------------------------------
          cgi_escape    13.791k i/100ms
         curl_escape    52.251k i/100ms
-------------------------------------------------
          cgi_escape    130.471k (±17.8%) i/s -      1.889M
         curl_escape    832.501k (± 5.6%) i/s -     12.488M

Comparison:
         curl_escape:   832501.4 i/s
          cgi_escape:   130470.6 i/s - 6.38x slower
```

### `url_for` benchmark
```
irb(main):005:0> app.dashboard_app_path("hogehoge", {foo: "bar", hoge: "aa", aaa: "aaa", bbb: "bbb", hogehoge: "%&[12]"})
=> "/apps/hogehoge/dashboard?aaa=aaa&bbb=bbb&foo=bar&hoge=aa&hogehoge=%25%26%5B12%5D"
irb(main):006:0> Benchmark.ips do |x|
irb(main):007:1*   x.config(time: 15, warmup: 5)
irb(main):008:1>   x.report("url_for") { app.dashboard_app_path("hogehoge", {foo: "bar", hoge: "aa", aaa: "aaa", bbb: "bbb", hogehoge: "%&[12]"}) }
irb(main):009:1> end
Calculating -------------------------------------
             url_for   922.000  i/100ms
-------------------------------------------------
             url_for      9.038k (±19.5%) i/s -    129.080k
=> #<Benchmark::IPS::Report:0x007fe017c73a68 @entries=[#<Benchmark::IPS::Report::Entry:0x007fe01b53b9b8 @label="url_for", @microseconds=15008895.1587677, @iterations=129080, @ips=9037.936272156061, @ips_sd=1764, @measurement_cycle=922, @show_total_time=false>], @data=nil>
irb(main):010:0> require 'curl_escape/core_ext/cgi'
=> true
irb(main):011:0> app.dashboard_app_path("hogehoge", {foo: "bar", hoge: "aa", aaa: "aaa", bbb: "bbb", hogehoge: "%&[12]"})
=> "/apps/hogehoge/dashboard?aaa=aaa&bbb=bbb&foo=bar&hoge=aa&hogehoge=%25%26%5B12%5D"
irb(main):012:0>
irb(main):013:0* Benchmark.ips do |x|
irb(main):014:1*   x.config(time: 15, warmup: 5)
irb(main):015:1>   x.report("url_for") { app.dashboard_app_path("hogehoge", {foo: "bar", hoge: "aa", aaa: "aaa", bbb: "bbb", hogehoge: "%&[12]"}) }
irb(main):016:1> end
Calculating -------------------------------------
             url_for     1.192k i/100ms
-------------------------------------------------
             url_for     12.170k (±14.2%) i/s -    177.608k
=> #<Benchmark::IPS::Report:0x007fe01b4c8da0 @entries=[#<Benchmark::IPS::Report::Entry:0x007fe015863560 @label="url_for", @microseconds=15003959.655761719, @iterations=177608, @ips=12170.236970422775, @ips_sd=1723, @measurement_cycle=1192, @show_total_time=false>], @data=nil>
```

about 34% faster.

But the fewer parameters, the less difference.

## Requirements
- curl

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'curl_escape'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install curl_escape

## Usage

```ruby
CurlEscape.escape('Escape target string % あいうえお')
# => "Escape+target+string+%25+%E3%81%82%E3%81%84%E3%81%86%E3%81%88%E3%81%8A"

require 'curl_escape/core_ext/cgi'
CGI.escape('Escape target string % あいうえお') # replace implementation
```

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake spec` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/joker1007/curl_escape.

