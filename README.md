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

see. https://github.com/joker1007/curl_escape/blob/master/spec/curl_escape_spec.rb

```
Calculating -------------------------------------
          cgi_escape     4.825k i/100ms
         curl_escape    16.006k i/100ms
-------------------------------------------------
          cgi_escape     81.631k (± 1.1%) i/s -      1.226M
         curl_escape    897.087k (± 6.8%) i/s -     13.349M

Comparison:
         curl_escape:   897087.1 i/s
          cgi_escape:    81631.5 i/s - 10.99x slower

Calculating -------------------------------------
normal rails_url_helper
                       797.000  i/100ms
-------------------------------------------------
normal rails_url_helper
                          8.512k (±12.7%) i/s -    125.129k
-------------------------------------------------
core_ext rails_url_helper
                       940.000  i/100ms
-------------------------------------------------
core_ext rails_url_helper
                         13.129k (± 2.0%) i/s -    197.400k

Comparison:
core_ext rails_url_helper:    13128.7 i/s
normal rails_url_helper:     8512.5 i/s - 1.54x slower
```

URL escaping is 7x - 10x faster
Rails url helper is 30% - 50% faster.

But the fewer query parameters, the less difference.

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

