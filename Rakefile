require "bundler/gem_tasks"
require "rake/extensiontask"
require "rspec/core/rake_task"

Rake::ExtensionTask.new('curl_escape') do |ext|
  ext.lib_dir = 'lib/curl_escape'
end

RSpec::Core::RakeTask.new(:spec)

task :default => [:compile, :spec]
