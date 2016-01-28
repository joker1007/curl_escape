require 'spec_helper'
require 'cgi'

describe CurlEscape do
  describe '.escape' do
    it 'returns URL escaped string.' do
      str = 'Test String~あいうえお%foo_bar.html'
      expect(CurlEscape.escape(str)).to eq(CGI.escape(str))
    end
  end
end
