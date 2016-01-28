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
  end
end
