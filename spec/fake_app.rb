# require 'rails/all'
require 'action_controller/railtie'
require 'action_view/railtie'

require 'stringio'

app = Class.new(Rails::Application)
# Rais.root
app.config.root = File.dirname(__FILE__)
app.config.eager_load = true
app.config.logger = Logger.new(StringIO.new)
Rails.backtrace_cleaner.remove_silencers!
app.initialize!

app.routes.draw do
  resources :users
end

def dummy_app
  @dummy_app ||= ActionDispatch::Integration::Session.new(Rails.application).tap do |sess|
    sess.host! "www.example.com"
  end
end
