# CurlEscape
[![Build Status](https://travis-ci.org/joker1007/curl_escape.svg?branch=master)](https://travis-ci.org/joker1007/curl_escape)

Fast URL escape by libcurl.

`CurlEscape.escape` is 5x faster or more than `CGI.escape`.

The spec of escaping is `CGI.escape` compatible, and this gem has core extension for `CGI.escape`.

## Motivation
`CGI.escape` is used by `#to_query` method that is defined by activesupport.

And `#to_query` is used by `link_to` helper of Rails.

I want to speed up `link_to`.

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

