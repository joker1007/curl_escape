require 'spec_helper'
require 'cgi'

require 'curl_escape/core_ext/cgi'

describe CurlEscape do
  describe '.escape' do
    it 'returns URL escaped string.' do
      str = 'Test String~あいうえお%foo_bar.html'
      expect(CurlEscape.escape(str)).to eq(CGI.origin_escape(str))
      expect(CGI.escape(str)).to eq(CGI.origin_escape(str))
    end

    describe 'examples from ruby/spec spec/library/cgi/escape_spec.rb' do
      describe "CGI.escape" do
        it "url-encodes the passed argument" do
          input    = " !\"\#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
          expected = "+%21%22%23%24%25%26%27%28%29%2A%2B%2C-.%2F0123456789%3A%3B%3C%3D%3E%3F%40ABCDEFGHIJKLMNOPQRSTUVWXYZ%5B%5C%5D%5E_%60abcdefghijklmnopqrstuvwxyz%7B%7C%7D%7E"
          expect(CurlEscape.escape(input)).to eq expected

          input    = "http://ja.wikipedia.org/wiki/\343\203\255\343\203\240\343\202\271\343\202\253\343\203\273\343\203\221\343\203\255\343\203\273\343\202\246\343\203\253\343\203\273\343\203\251\343\203\224\343\203\245\343\202\277"
          expected = 'http%3A%2F%2Fja.wikipedia.org%2Fwiki%2F%E3%83%AD%E3%83%A0%E3%82%B9%E3%82%AB%E3%83%BB%E3%83%91%E3%83%AD%E3%83%BB%E3%82%A6%E3%83%AB%E3%83%BB%E3%83%A9%E3%83%94%E3%83%A5%E3%82%BF'
          expect(CurlEscape.escape(input)).to eq expected
        end
      end
    end

    describe 'examples from ruby/ruby test/cgi/test_cgi_util.rb' do
      specify 'test_cgi_escape' do
        str="&<>\" \xE3\x82\x86\xE3\x82\x93\xE3\x82\x86\xE3\x82\x93"
        str.force_encoding("UTF-8") if defined?(::Encoding)
        expect(CurlEscape.escape(str)).to eq '%26%3C%3E%22+%E3%82%86%E3%82%93%E3%82%86%E3%82%93'
        expect(CurlEscape.escape(str).ascii_only?).to eq '%26%3C%3E%22+%E3%82%86%E3%82%93%E3%82%86%E3%82%93'.ascii_only?
      end

      specify 'test_cgi_escape_with_invalid_byte_sequence' do
        expect {
          expect(CurlEscape.escape("\xC0\<\<".force_encoding("UTF-8"))).to eq '%C0%3C%3C'
        }.to_not raise_error
      end

      pending 'test_cgi_escape_preserve_encoding' do
        expect(CurlEscape.escape("\xC0\<\<".force_encoding("US-ASCII")).encoding).to eq Encoding::US_ASCII
        expect(CurlEscape.escape("\xC0\<\<".force_encoding("ASCII-8BIT")).encoding).to eq Encoding::ASCII_8BIT
        expect(CurlEscape.escape("\xC0\<\<".force_encoding("UTF-8")).encoding).to eq Encoding::UTF_8
      end
    end
  end
end
