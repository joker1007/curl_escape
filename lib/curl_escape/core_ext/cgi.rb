require 'cgi'

module CGI::Util
  alias :origin_escape :escape

  def escape(string)
    CurlEscape.escape(string)
  end
end
