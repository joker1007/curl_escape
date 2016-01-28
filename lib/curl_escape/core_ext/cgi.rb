require 'cgi'
require 'curl_escape/curl_escape'

module CGI::Util
  alias :origin_escape :escape

  def escape(string)
    CurlEscape.escape(string)
  end
end
